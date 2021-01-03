#include "pch.h"
#include "FileMap.hpp"

#include <cassert>
#include <DbgHelp.h>

#pragma comment (lib, "Dbghelp.lib")

// File replacement map.
// NOTE: Do NOT mark this as static.
// MediaFns.cpp needs to access the FileMap.
FileMap rayman2_fileMap;

/**
* CreateFileA() wrapper using _ReplaceFile().
* @param lpFileName
* @param dwDesiredAccess
* @param dwShareMode
* @param lpSecurityAttributes
* @param dwCreationDisposition
* @param dwFlagsAndAttributes
* @param hTemplateFile
* @return
*/
HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	return CreateFileA(rayman2_fileMap.replaceFile(lpFileName), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

/**
* C wrapper to call rayman2_fileMap.replaceFile() from asm.
* @param lpFileName Filename.
* @return Replaced filename, or original filename if not replaced by a mod.
*/
const char* _ReplaceFile(const char* lpFileName) {
	return rayman2_fileMap.replaceFile(lpFileName);
}

/**
 * Hook Rayman2's CreateFileA() import.
 */
void HookCreateFileA() {
	ULONG ulSize = 0;

	// SADX module handle. (main executable)
	HMODULE hModule = GetModuleHandle(nullptr);

	PROC pNewFunction = (PROC)MyCreateFileA;
	// Get the actual CreateFileA() using GetProcAddress().
	PROC pActualFunction = GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "CreateFileA");
	assert(pActualFunction != nullptr);

	auto pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

	if (pImportDesc == nullptr)
	{
		return;
	}

	for (; pImportDesc->Name; pImportDesc++)
	{
		// get the module name
		auto pcszModName = (PCSTR)((PBYTE)hModule + pImportDesc->Name);

		// check if the module is kernel32.dll
		if (pcszModName != nullptr && _stricmp(pcszModName, "Kernel32.dll") == 0)
		{
			// get the module
			auto pThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImportDesc->FirstThunk);

			for (; pThunk->u1.Function; pThunk++)
			{
				PROC* ppfn = (PROC*)&pThunk->u1.Function;
				if (*ppfn == pActualFunction)
				{
					// Found CreateFileA().
					DWORD dwOldProtect = 0;
					VirtualProtect(ppfn, sizeof(pNewFunction), PAGE_WRITECOPY, &dwOldProtect);
					WriteData(ppfn, pNewFunction);
					VirtualProtect(ppfn, sizeof(pNewFunction), dwOldProtect, &dwOldProtect);
					// FIXME: Would it be listed multiple times?
					break;
				} // Function that we are looking for
			}
		}
	}
}

/**
* Scan for file replacement in a folder
* @param wstring path
*/
void ScanModFolder(const std::wstring str, int loadorder) {
	if (DirectoryExists(str)) {
		std::string str2(str.begin(), str.end());
		rayman2_fileMap.scanFolder(str2, loadorder);
	}
}