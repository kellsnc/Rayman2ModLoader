/*
 * Rayman2 Mod Loader.
 * Initialize mods
 */

#include "pch.h"

static std::vector<std::pair<std::wstring, std::wstring>> modErrors; // store errors and print them all when mods are finished loading.
static std::unordered_map<std::string, std::string> filereplaces; // store file replacements query and add them all at the end.
static std::vector<std::pair<std::string, std::string>> fileswaps; // store file swaps query and swap them all at the end.

// Print all errors in a single prompt.
void ShowErrors() {
	if (!modErrors.empty()) {
		std::wstringstream message;
		message << L"The following mods didn't load correctly:" << std::endl;

		for (auto& i : modErrors) {
			message << std::endl << i.first << ": " << i.second;
		}

		MessageBox(nullptr, message.str().c_str(), L"Mods failed to load", MB_OK | MB_ICONERROR);

		// Clear the errors vector to free memory.
		modErrors.clear();
		modErrors.shrink_to_fit();
	}
}

// Run all the detected file replacements
void RunAllModFileReplacements() {
	for (const auto& filereplace : filereplaces) {
		rayman2_fileMap.addReplaceFile(filereplace.first, filereplace.second);
	}

	filereplaces.clear(); // Clear filereplaces vector

	for (const auto& fileswap : fileswaps) {
		rayman2_fileMap.swapFiles(fileswap.first, fileswap.second);
	}

	// Clear fileswaps vector
	fileswaps.clear();
	fileswaps.shrink_to_fit();
}

// DLL injection
void InitModDLL(const std::wstring* modpath, const std::wstring dll_filename, const std::wstring* modname) {
	HMODULE module = LoadLibrary(dll_filename.c_str());

	if (module != nullptr) {
		const auto info = (const ModInfo*)GetProcAddress(module, "Rayman2ModInfo"); // check if this is a valid mod dll.

		if (info) {
			const auto init = (const ModInitFunc)GetProcAddress(module, "Init");

			// Run init function as soon as possible if it exists
			if (init) {
				std::string s(modpath->begin(), modpath->end());
				init(s.c_str(), helperFunctions);
			}

			// Register function hook events
			RegisterEvent(modFrameEvents, module, "OnFrame");
			RegisterEvent(modBeforeRenderEvents, module, "BeforeRender");
			RegisterEvent(modAfterRenderEvents, module, "AfterRender");
		}
	}
	else {
		// Parse DLL load error

		DWORD error = GetLastError();
		LPWSTR buffer;
		size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPWSTR)&buffer, 0, nullptr);
		bool allocated = (size != 0);

		if (!allocated) {
			static const wchar_t fmterr[] = L"Unable to format error message.";
			buffer = const_cast<LPWSTR>(fmterr);
			size = LengthOfArray(fmterr) - 1;
		}

		std::wstring message(buffer, size);

		if (allocated) {
			LocalFree(buffer);
		}

		const std::string dll_filenameA = UTF16toMBS(dll_filename, CP_ACP);
		const std::string messageA = UTF16toMBS(message, CP_ACP);
		PrintDebug("Failed loading mod DLL \"%s\": %s\n", dll_filenameA.c_str(), messageA.c_str());
		modErrors.emplace_back(*modname, L"DLL error - " + message);
	}
}

// Load a mod folder, returns 1 if the mod failed to load.
int InitSingleMod(std::wstring modpath, std::wstring* foldername, int loadorder) {
	const std::wstring mod_inifile = modpath + L"\\mod.ini";
	
	const IniFile* config = new IniFile(mod_inifile);
	const IniGroup* modinfo = config->getGroup("");

	if (modinfo != nullptr) {
		modinfo = modinfo;

		const std::wstring modname = modinfo->getWString("Name", *foldername);
		
		// DLL injection
		if (modinfo->hasKeyNonEmpty("DLLFile")) {
			InitModDLL(&modpath, modpath + L'\\' + modinfo->getWString("DLLFile"), &modname);
		}

		// Window Title
		if (modinfo->hasKeyNonEmpty("WindowTitle")) {
			helperFunctions.SetWindowTitle(modinfo->getString("WindowTitle", "Rayman II").c_str());
		}

		// Ignore files (the mod loader won't replace these files)
		if (config->hasGroup("IgnoreFiles")) {
			const IniGroup* group = config->getGroup("IgnoreFiles");
			auto data = group->data();

			for (const auto& iter : *data) {
				rayman2_fileMap.addIgnoreFile(iter.first, loadorder);
				PrintDebug("Ignored file: %s\n", iter.first.c_str());
			}
		}

		// Replace files (replace a file from the game with a file from the mod, allows for a different name/location)
		if (config->hasGroup("ReplaceFiles")) {
			const IniGroup* group = config->getGroup("ReplaceFiles");
			auto data = group->data();

			for (const auto& iter : *data) {
				filereplaces[FileMap::normalizePath(iter.first)] =
					FileMap::normalizePath(iter.second);
			}
		}

		// Swap files
		if (config->hasGroup("SwapFiles")) {
			const IniGroup* group = config->getGroup("SwapFiles");
			auto data = group->data();
			
			for (const auto& iter : *data) {
				fileswaps.emplace_back(FileMap::normalizePath(iter.first),
					FileMap::normalizePath(iter.second));
			}
		}

		// Check for folder file replacements.
		ScanModFolder(modpath + L"\\data", loadorder);
		ScanModFolder(modpath + L"\\dll", loadorder);
		
		return 0;
	}
	else {
		// Could not load this mod.

		std::string s(modpath.begin(), modpath.end());
		std::string s2(foldername->begin(), foldername->end());
		PrintDebug("Failed loading mod \"%s\": could not open file mod.ini in \"%s\".\n", s2.c_str(), s.c_str());
		modErrors.emplace_back(*foldername, L"mod.ini missing");
		return 1;
	}
}

void InitMods(const IniGroup* loaderconfig, const std::wstring* path) {
	PrintDebug("[ModLoader] Loading mods... \n");

	int failedcount = 0;
	int count = 1;

	// Find all mods
	while (true) {
		char key[8];

		snprintf(key, sizeof(key), "Mod%u", count); // "Mod1, Mod2..."

		// If no more mod in the chain, leave this.
		if (!loaderconfig->hasKey(key)) {
			break;
		}

		// Temporary mod name
		std::wstring foldername = loaderconfig->getWString(key);

		// Load this mod
		failedcount += InitSingleMod(*path + L"\\" + foldername, &foldername, count);

		count += 1;
	}

	// Get the number of mod that loaded succesfully
	count = count - 1 - failedcount;

	if (count > 0) {
		RunAllModFileReplacements();
	}

	PrintDebug("Loaded %d mod%s", count, count <= 1 ? ".\n" : "s.\n");

	// Print errors
	ShowErrors();
}