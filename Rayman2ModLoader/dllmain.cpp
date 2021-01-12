/*
 * Rayman2 Mod Loader.
 * Entry point of the DLL hook, runs just after the config file is parsed
 */

#include "pch.h"

void LoadOriginalDLL(std::string dllname);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        LoaderInit(); // load codes and mods
        HookFileFunctions(); // hook CreateFileA and fopen to allow for file replacement from mods folder
        LoadOriginalDLL(DLLName); // restore the original dll
        
        break;
    case DLL_PROCESS_DETACH:
        DeleteOutput();
        break;
    }

    return TRUE;
}

