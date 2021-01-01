/*
 * Rayman2 Mod Loader
 * Rayman2 function pointers
 */

#ifndef RAYMAN2MODLOADER_FUNCTIONS_H
#define RAYMAN2MODLOADER_FUNCTIONS_H

FunctionPointer(void, ReadConfig_GraphicsDLLFile, (const char* name), 0x538E60);
FunctionPointer(HMODULE, LoadGraphicsDLL, (), 0x51C850);

#endif