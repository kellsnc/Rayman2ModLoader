/*
 * Rayman2 Mod Loader.
 * Entry point of the DLL hook, runs just after the config file is parsed
 */

#include "pch.h"

static const char* DLLName = "GliVd1";
static const char* APIName = "Glide2";

void CopyAPIString(char* output, const char* str) {
    size_t length = strlen(str);
    memcpy_s(output, length, str, length);
    *(output + length) = *(char*)"\0";
}

extern "C" {
    __declspec(dllexport) signed int __cdecl GLI_DRV_lGetDllInfo(const char* type, char* output) {
        if (!strcmp(type, "Name")) {
            CopyAPIString(output, APIName);
        }
        
        return true;
    }

    __declspec(dllexport) signed int GLI_DRV_lSetCommonFct() {
        return true;
    }

    __declspec(dllexport) signed int GLI_DRV_lSetCommonData() {
        return true;
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    ReadConfig_GraphicsDLLFile(DLLName); // Restore the original DLL Name
    LoadGraphicsDLL(); // Call the original DLL

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

