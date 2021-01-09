/*
 * Rayman2 Mod Loader.
 * Initialize mods
 */

#include "pch.h"

static std::vector<std::pair<std::wstring, std::wstring>> loadErrors;
static std::unordered_map<std::string, std::string> filereplaces;
static std::vector<std::pair<std::string, std::string>> fileswaps;

void ShowErrors() {
	if (!loadErrors.empty()) {
		std::wstringstream message;
		message << L"The following mods didn't load correctly:" << std::endl;

		for (auto& i : loadErrors) {
			message << std::endl << i.first << ": " << i.second;
		}

		MessageBox(nullptr, message.str().c_str(), L"Mods failed to load", MB_OK | MB_ICONERROR);

		// Clear the errors vector to free memory.
		loadErrors.clear();
		loadErrors.shrink_to_fit();
	}
}

void InitModDLL(const std::wstring* modpath, const std::wstring dll_filename, const std::wstring* modname) {
	HMODULE module = LoadLibrary(dll_filename.c_str());

	if (module != nullptr) {
		const auto info = (const ModInfo*)GetProcAddress(module, "Rayman2ModInfo");

		if (info) {
			const auto init = (const ModInitFunc)GetProcAddress(module, "Init");

			if (init) {
				std::string s(modpath->begin(), modpath->end());
				init(s.c_str(), helperFunctions);
			}

			RegisterEvent(modFrameEvents, module, "OnFrame");
			RegisterEvent(modBeforeRenderEvents, module, "BeforeRender");
			RegisterEvent(modAfterRenderEvents, module, "AfterRender");
		}
	}
	else {
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
		loadErrors.emplace_back(*modname, L"DLL error - " + message);
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

		if (modinfo->hasKeyNonEmpty("DLLFile")) {
			InitModDLL(&modpath, modpath + L'\\' + modinfo->getWString("DLLFile"), &modname);
		}

		if (modinfo->hasKeyNonEmpty("WindowTitle")) {
			helperFunctions.SetWindowTitle(modinfo->getString("WindowTitle", "Rayman II").c_str());
		}

		if (config->hasGroup("IgnoreFiles")) {
			const IniGroup* group = config->getGroup("IgnoreFiles");
			auto data = group->data();

			for (const auto& iter : *data) {
				rayman2_fileMap.addIgnoreFile(iter.first, loadorder);
				PrintDebug("Ignored file: %s\n", iter.first.c_str());
			}
		}

		if (config->hasGroup("ReplaceFiles")) {
			const IniGroup* group = config->getGroup("ReplaceFiles");
			auto data = group->data();

			for (const auto& iter : *data) {
				filereplaces[FileMap::normalizePath(iter.first)] =
					FileMap::normalizePath(iter.second);
			}
		}

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
		
		return 0;
	}
	else {
		std::string s(modpath.begin(), modpath.end());
		std::string s2(foldername->begin(), foldername->end());
		PrintDebug("Failed loading mod \"%s\": could not open file mod.ini in \"%s\".\n", s2.c_str(), s.c_str());
		loadErrors.emplace_back(*foldername, L"mod.ini missing");
		return 1;
	}
}

void InitMods(const IniGroup* loaderconfig, const std::wstring* path) {
	PrintDebug("[ModLoader] Loading mods... \n");
	int failedcount = 0;

	// Parse the list of mod
	int count = 1;

	while (1) {
		char key[8];

		snprintf(key, sizeof(key), "Mod%u", count);

		if (!loaderconfig->hasKey(key)) {
			break;
		}

		std::wstring foldername = loaderconfig->getWString(key);

		failedcount += InitSingleMod(*path + L"\\" + foldername, &foldername, count);

		count += 1;
	}

	// Get the number of mod that loaded succesfully
	count = count - 1 - failedcount;

	// Run all the detected file replacements
	if (count > 0) {
		for (const auto& filereplace : filereplaces) {
			rayman2_fileMap.addReplaceFile(filereplace.first, filereplace.second);
		}

		for (const auto& fileswap : fileswaps) {
			rayman2_fileMap.swapFiles(fileswap.first, fileswap.second);
		}
	}

	PrintDebug("Loaded %d mod%s", count, count <= 1 ? ".\n" : "s.\n");

	ShowErrors();
}