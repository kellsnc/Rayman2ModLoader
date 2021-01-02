#include "pch.h"

void __cdecl SetWindowTitle(const char* title) {
	if (WindowHandle) {
		SetWindowTextA(WindowHandle, title);
	}
}

const char* __cdecl GetMainSavePath() {
	return "Data\SaveGame";
}

const HelperFunctions helperFunctions = {
	ModLoaderVer,
	&PrintDebug,
	&SetWindowTitle,
	&GetMainSavePath
};