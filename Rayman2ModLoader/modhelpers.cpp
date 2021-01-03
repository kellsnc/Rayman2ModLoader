#include "pch.h"

const char* __cdecl GetReplaceablePath(const char* path) {
	return rayman2_fileMap.replaceFile(path);
}

void _ReplaceFile(const char* src, const char* dst) {
	rayman2_fileMap.addReplaceFile(src, dst);
}

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