/*
 * Rayman2 Mod Loader.
 * Entry point of the DLL hook, runs just after the config file is parsed
 */

#include "pch.h"
#include "exports.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        LoaderInit(); // Load codes and mods.
        HookFileFunctions(); // Hook CreateFileA and fopen to allow for file replacement from mods folder.
        LoadOriginalDLL(); // Restore the original dll.
        
        break;
    case DLL_PROCESS_DETACH:
        DeleteOutput(); // Make sure the debug file is deleted before exiting.
        TexturesDelete(); // Make sure textures are freed before exiting.
        break;
    }

    return TRUE;
}

