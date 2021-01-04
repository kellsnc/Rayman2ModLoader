/*
 * Rayman2 Mod Loader
 * Rayman2 function pointers
 */

#ifndef RAYMAN2MODLOADER_FUNCTIONS_H
#define RAYMAN2MODLOADER_FUNCTIONS_H

StdcallFunctionPointer(LRESULT, WndProc, (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam), 0x4022D0);
FunctionPointer(int, CreateRayman2Window, (HINSTANCE hInstance, int nCmdShow), 0x402020);
FunctionPointer(const char*, GetCurrentLevelName, (), 0x404DA0);
FunctionPointer(const char*, GoToNextLevel, (const char* levelName, bool save), 0x4054D0);
VoidFunc(GameEngine, 0x40ADA0);
VoidFunc(MainRenderer, 0x40B150);
FunctionPointer(void, j_Glide_OnSceneBegin, (Uint32 a1), 0x420B00);
VoidFunc(j_Glide_OnSceneEnd, 0x420B10);
FunctionPointer(__byte, JFFTXT_vAffiche, (Uint32 a1), 0x465C10);
FunctionPointer(__byte, _DrawText, (Uint32 a1, Text2D* text), 0x465C10);
FunctionPointer(void, AGO_vDisplayIcones, (Uint32 a1), 0x460600);
FunctionPointer(void, AGO_vDisplayGAUGES, (Uint32 a1), 0x460670);
FunctionPointer(void, ReadConfig_GraphicsDLLFile, (const char* name), 0x538E60);
FunctionPointer(HMODULE, LoadGraphicsDLL, (), 0x51C850);

#endif