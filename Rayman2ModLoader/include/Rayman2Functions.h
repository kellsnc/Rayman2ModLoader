/*
 * Rayman2 Mod Loader
 * Rayman2 function pointers
 */

#ifndef RAYMAN2MODLOADER_FUNCTIONS_H
#define RAYMAN2MODLOADER_FUNCTIONS_H

StdcallFunctionPointer(LRESULT, WndProc, (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam), 0x4022D0);
FunctionPointer(int, CreateRayman2Window, (HINSTANCE hInstance, int nCmdShow), 0x402020);
FunctionPointer(void, ReadConfig_GraphicsDLLFile, (const char* name), 0x538E60);
FunctionPointer(HMODULE, LoadGraphicsDLL, (), 0x51C850);

#endif