/*
 * Rayman2 Mod Loader.
 * Replace file functions to redirect them if needed using FileMap.
 */

#include "pch.h"
#include "FileMap.hpp"

#include <cassert>

FileMap rayman2_fileMap;

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	return CreateFileA(rayman2_fileMap.replaceFile(lpFileName), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI MyLoadLibraryA(LPCSTR lpFileName) {
	return LoadLibraryA(rayman2_fileMap.replaceFile(lpFileName));
}

const char* newName = "";

__declspec(dllexport) __declspec(naked) FILE* Myfopen(const char* Filename, const char* Mode) {
	__asm {
		mov eax, [esp + 4]
		mov newName, eax
	}
	
	newName = rayman2_fileMap.replaceFile(newName);
	
	__asm {
		mov[esp + 4], eax
		jmp cs : [0049C1B8h] // return to original fopen in import table
	}
}

// Hook into an imported function
void HookProcFunction(const char* dll, const char* funcname, void* newfunc) {
	ULONG ulSize = 0;

	// SADX module handle. (main executable)
	HMODULE hModule = GetModuleHandle(nullptr);

	PROC pNewFunction = (PROC)newfunc;
	PROC pActualFunction = GetProcAddress(GetModuleHandleA(dll), funcname);

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

		if (pcszModName != nullptr && _stricmp(pcszModName, dll) == 0)
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

// Hook Rayman2's CreateFileA() & fopen imports.
void HookFileFunctions() {
	HookProcFunction("Kernel32.dll", "CreateFileA", (void*)MyCreateFileA);
	HookProcFunction("Kernel32.dll", "LoadLibraryA", (void*)MyLoadLibraryA);
	WriteJump((void*)0x576CB4, Myfopen);
	WriteJump((void*)0x45FCB4, Myfopen);
}

// Scan for file replacement in a folder
void ScanModFolder(const std::string str, int loadorder) {
	if (DirectoryExists(str)) {
		rayman2_fileMap.scanFolder(str, loadorder);
	}
}