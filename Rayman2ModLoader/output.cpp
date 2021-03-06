/*
 * Rayman2 Mod Loader.
 * Console and file debug output
 * Courtesy of MainMemory
 */

#include "pch.h"

static bool DebugConsole = false;
static FILE* DebugFile = nullptr;
static FILE* ConsoleStream = nullptr;

void __cdecl PrintDebug(const char* Format, ...) {
	va_list ap;
	va_start(ap, Format);
	int result = vsnprintf(nullptr, 0, Format, ap) + 1;
	va_end(ap);
	char* buf = new char[result + 1];
	va_start(ap, Format);
	result = vsnprintf(buf, result + 1, Format, ap);
	va_end(ap);
	
	// todo: codepage conversion
	if (DebugConsole == true) {
		fputs(buf, stdout);
		fflush(stdout);
	}
	
	if (DebugFile) {
		fputs(buf, DebugFile);
		fflush(DebugFile);
	}
	
	delete[] buf;
}

void InitOutput(const IniGroup* loaderconfig) {
	DebugConsole = loaderconfig->getBool("DebugConsole", false);
	
	// Open console
	if (DebugConsole == true) {
		AllocConsole();
		SetConsoleTitle(L"Rayman2 Mod Loader output");
		freopen_s(&ConsoleStream, "CONOUT$", "wb", stdout);
	}
	
	// Open log file (DebugFile stays null if not enabled)
	if (loaderconfig->getBool("DebugFile")) {
		_wfopen_s(&DebugFile, L"Rayman2ModLoader.log", L"a+");
	}
	
	// If console/log enabled, print mod loader information.
	if (DebugConsole == true || DebugFile != nullptr) {
		PrintDebug("[ModLoader] Rayman2 Mod Loader, version %i (" __TIMESTAMP__ ")\n", ModLoaderVer);
	}
}

void DeleteOutput() {
	if (DebugFile) {
		fclose(DebugFile);
		DebugFile = nullptr;
	}
}