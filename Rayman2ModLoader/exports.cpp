/*
 * Rayman2 Mod Loader.
 * Redirect exported functions to the ones of the original DLL
 */

#include "pch.h"

HMODULE hOrig = NULL;

#define GETEXPORT(name) EXPORT_##name## = (int)GetProcAddress(hOrig, #name##);
#define EXPORT __declspec(dllexport)
#define NAKED __declspec(naked)
#define JUMP(adr) __asm {jmp adr};

BOOL(*EXPORT_GLI_DRV_lGetDllInfo)(const char*, char*) = NULL;

static int EXPORT_GLI_DRV_lSetCommonFct;
static int EXPORT_GLI_DRV_lSetCommonData;
static int EXPORT_GLI_DRV_bBeginScene;
static int EXPORT_GLI_DRV_bEndScene;
static int EXPORT_GLI_DRV_bLockDevice;
static int EXPORT_GLI_DRV_bPrepareForGliWindowed;
static int EXPORT_GLI_DRV_bUnlockDevice;
static int EXPORT_GLI_DRV_bWindowedModeIsOptimized;
static int EXPORT_GLI_DRV_fn_lGetAllDisplayConfig;
static int EXPORT_GLI_DRV_fnl_EnumModes;
static int EXPORT_GLI_DRV_hChangeMode;
static int EXPORT_GLI_DRV_lGetSizeOfTexture;
static int EXPORT_GLI_DRV_vActivateGli;
static int EXPORT_GLI_DRV_vAddBlackPolygon;
static int EXPORT_GLI_DRV_vClearDevice;
static int EXPORT_GLI_DRV_vClearZBufferRegion;
static int EXPORT_GLI_DRV_vCloseDriver;
static int EXPORT_GLI_DRV_vComputeFogEffect;
static int EXPORT_GLI_DRV_vDoOpaqueTextureSelection;
static int EXPORT_GLI_DRV_vDownLoadTextures;
static int EXPORT_GLI_DRV_vFlipDevice;
static int EXPORT_GLI_DRV_vFlipDeviceWithSyncro;
static int EXPORT_GLI_DRV_vGetStats;
static int EXPORT_GLI_DRV_vNoBlackPolygon;
static int EXPORT_GLI_DRV_vNonOptimizedWindowedMode;
static int EXPORT_GLI_DRV_vOptimizedWindowedMode;
static int EXPORT_GLI_DRV_vPrepareForGliFullScreen;
static int EXPORT_GLI_DRV_vSendSingleLineToClip;
static int EXPORT_GLI_DRV_vSendSpriteToClip;
static int EXPORT_GLI_DRV_vSendSpriteToClipWithColors;
static int EXPORT_GLI_DRV_vSendSpriteToClipWithUV;
static int EXPORT_GLI_DRV_vSetClipWindow;
static int EXPORT_GLI_DRV_vSetZClip;
static int EXPORT_GLI_DRV_vUnLoadTextures;
static int EXPORT_GLI_DRV_vWrite16bBitmapToBackBuffer;
static int EXPORT_GLI_DRV_xClearViewingList;
static int EXPORT_GLI_DRV_xInitDriver;
static int EXPORT_GLI_DRV_xSendElementTIToClip_TRIANGLES;
static int EXPORT_GLI_DRV_xSendListToViewport;
static int EXPORT_GLI_DRV_xSendSingleTriangleToClip_TRIANGLES;
static int EXPORT_GLI_DRV_vReadaptDisplay;

static bool DLLReplaced = false;

void CopyAPIString(char* output, const char* str) {
	size_t length = strlen(str);
	memcpy_s(output, length, str, length);
	*(output + length) = *(char*)"\0";
}

// Redirect all the exports to the original DLL

extern "C" {
	EXPORT BOOL GLI_DRV_lGetDllInfo(const char* type, char* output) {
		if (DLLReplaced == false && !strcmp(type, "Name")) {
			CopyAPIString(output, APIName.c_str());
			DLLReplaced = true;
			return true;
		}

		return EXPORT_GLI_DRV_lGetDllInfo(type, output);
	}

	EXPORT NAKED BOOL GLI_DRV_fn_lGetAllDisplayConfig(LPVOID gliSet)
	{
		JUMP(EXPORT_GLI_DRV_fn_lGetAllDisplayConfig);
	}

	EXPORT NAKED BOOL GLI_DRV_lSetCommonData(const char* szName, void* value)
	{
		JUMP(EXPORT_GLI_DRV_lSetCommonData);
	}

	EXPORT NAKED BOOL GLI_DRV_lSetCommonFct(const char* szName, LPVOID)
	{
		JUMP(EXPORT_GLI_DRV_lSetCommonFct);
	}

	EXPORT NAKED BOOL GLI_DRV_fnl_EnumModes(char* szDrvDspName, char* szDevName)
	{
		JUMP(EXPORT_GLI_DRV_fnl_EnumModes)
	}

	EXPORT NAKED DWORD GLI_DRV_xInitDriver(HWND hWnd, BOOL bFullscreen, int xRight, int yBottom, int lBitDepth)
	{
		JUMP(EXPORT_GLI_DRV_xInitDriver);
	}

	EXPORT NAKED void GLI_DRV_vCloseDriver()
	{
		JUMP(EXPORT_GLI_DRV_vCloseDriver);
	}

	EXPORT NAKED BOOL GLI_DRV_bBeginScene()
	{
		JUMP(EXPORT_GLI_DRV_bBeginScene);
	}

	EXPORT NAKED BOOL GLI_DRV_bEndScene()
	{
		JUMP(EXPORT_GLI_DRV_bEndScene);
	}

	EXPORT NAKED BOOL GLI_DRV_bLockDevice(DWORD* a1, DWORD* a2)
	{
		JUMP(EXPORT_GLI_DRV_bLockDevice);
	}

	EXPORT NAKED BOOL GLI_DRV_bUnlockDevice()
	{
		JUMP(EXPORT_GLI_DRV_bUnlockDevice);
	}

	EXPORT NAKED void GLI_DRV_vClearDevice(int a1, int a2, int a3)
	{
		JUMP(EXPORT_GLI_DRV_vClearDevice);
	}

	EXPORT NAKED void GLI_DRV_vFlipDevice(int waitFrames)
	{
		JUMP(EXPORT_GLI_DRV_vFlipDevice);
	}

	EXPORT NAKED void GLI_DRV_vFlipDeviceWithSyncro()
	{
		JUMP(EXPORT_GLI_DRV_vFlipDeviceWithSyncro);
	}

	EXPORT NAKED void GLI_DRV_vGetStats()
	{
		JUMP(EXPORT_GLI_DRV_vGetStats);
	}

	EXPORT NAKED void GLI_DRV_vDownLoadTextures(int a1, int a2, int a3)
	{
		JUMP(EXPORT_GLI_DRV_vDownLoadTextures);
	}

	EXPORT NAKED void GLI_DRV_vUnLoadTextures()
	{
		JUMP(EXPORT_GLI_DRV_vUnLoadTextures);
	}

	EXPORT NAKED int GLI_DRV_lGetSizeOfTexture(void* a1)
	{
		JUMP(EXPORT_GLI_DRV_lGetSizeOfTexture);
	}

	EXPORT NAKED void GLI_DRV_vDoOpaqueTextureSelection(int a1)
	{
		JUMP(EXPORT_GLI_DRV_vDoOpaqueTextureSelection);
	}

	EXPORT NAKED HANDLE GLI_DRV_hChangeMode(BOOL bFullscreen, int xRight, int yBottom, int bitDepth)
	{
		JUMP(EXPORT_GLI_DRV_hChangeMode);
	}

	EXPORT NAKED BOOL GLI_DRV_bWindowedModeIsOptimized()
	{
		JUMP(EXPORT_GLI_DRV_bWindowedModeIsOptimized);
	}

	EXPORT NAKED void GLI_DRV_vOptimizedWindowedMode()
	{
		JUMP(EXPORT_GLI_DRV_vOptimizedWindowedMode);
	}

	EXPORT NAKED void GLI_DRV_vNonOptimizedWindowedMode()
	{
		JUMP(EXPORT_GLI_DRV_vNonOptimizedWindowedMode);
	}

	EXPORT NAKED BOOL GLI_DRV_bPrepareForGliWindowed(HWND hWnd)
	{
		JUMP(EXPORT_GLI_DRV_bPrepareForGliWindowed);
	}

	EXPORT NAKED void GLI_DRV_vPrepareForGliFullScreen(HWND hWnd)
	{
		JUMP(EXPORT_GLI_DRV_vPrepareForGliFullScreen);
	}

	EXPORT NAKED void GLI_DRV_vActivateGli(HWND hWnd, BOOL a2)
	{
		JUMP(EXPORT_GLI_DRV_vActivateGli);
	}

	EXPORT NAKED void GLI_DRV_vReadaptDisplay()
	{
		JUMP(EXPORT_GLI_DRV_vReadaptDisplay);
	}

	EXPORT NAKED void GLI_DRV_vAddBlackPolygon(int a1, int a2, int a3, int a4)
	{
		JUMP(EXPORT_GLI_DRV_vAddBlackPolygon);
	}

	EXPORT NAKED void GLI_DRV_vNoBlackPolygon()
	{
		JUMP(EXPORT_GLI_DRV_vNoBlackPolygon);
	}

	EXPORT NAKED void GLI_DRV_vSetZClip(float a1, int a2)
	{
		JUMP(EXPORT_GLI_DRV_vSetZClip);
	}

	EXPORT NAKED void GLI_DRV_vSetClipWindow(float a1, int a2, int a3, int a4, int a5)
	{
		JUMP(EXPORT_GLI_DRV_vSetClipWindow);
	}

	EXPORT NAKED void GLI_DRV_vSendSingleLineToClip(int a1, int a2, int a3, int a4, int a5)
	{
		JUMP(EXPORT_GLI_DRV_vSendSingleLineToClip);
	}

	EXPORT NAKED void GLI_DRV_vSendSpriteToClip(int a1, int a2, int a3)
	{
		JUMP(EXPORT_GLI_DRV_vSendSpriteToClip);
	}

	EXPORT NAKED void GLI_DRV_vSendSpriteToClipWithColors(int a1, int a2, int a3, int a4)
	{
		JUMP(EXPORT_GLI_DRV_vSendSpriteToClipWithColors);
	}

	EXPORT NAKED void GLI_DRV_vSendSpriteToClipWithUV(int a1, int a2, int a3, int a4)
	{
		JUMP(EXPORT_GLI_DRV_vSendSpriteToClipWithUV);
	}

	EXPORT NAKED int GLI_DRV_xSendElementTIToClip_TRIANGLES(int a1, int a2)
	{
		JUMP(EXPORT_GLI_DRV_xSendElementTIToClip_TRIANGLES);
	}

	EXPORT NAKED int GLI_DRV_xSendSingleTriangleToClip_TRIANGLES(int a1, int a2, int a3)
	{
		JUMP(EXPORT_GLI_DRV_xSendSingleTriangleToClip_TRIANGLES);
	}

	EXPORT NAKED DWORD GLI_DRV_xClearViewingList()
	{
		JUMP(EXPORT_GLI_DRV_xClearViewingList);
	}

	EXPORT NAKED DWORD GLI_DRV_xSendListToViewport()
	{
		JUMP(EXPORT_GLI_DRV_xSendListToViewport);
	}

	EXPORT NAKED void GLI_DRV_vClearZBufferRegion()
	{
		JUMP(EXPORT_GLI_DRV_vClearZBufferRegion);
	}

	EXPORT NAKED void GLI_DRV_vComputeFogEffect(int a1)
	{
		JUMP(EXPORT_GLI_DRV_vComputeFogEffect);
	}

	EXPORT NAKED void GLI_DRV_vWrite16bBitmapToBackBuffer(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
	{
		JUMP(EXPORT_GLI_DRV_vWrite16bBitmapToBackBuffer);
	}
}

void LoadOriginalDLL() {
	ReadConfig_GliDLLFile(DLLName.c_str()); // restore the original dll name
	ReadConfig_GliDLL(APIName.c_str()); // restore the original api name
	
	std::string path = ".\\DLL\\" + DLLName + "Vf.dll";
	hOrig = LoadLibraryA(rayman2_fileMap.replaceFile(path.c_str())); // in case the DLL was replaced by a mod

	if (hOrig == NULL) {
		MessageBoxA(NULL, "Cannot load the original DLL, check the Mod Manager options", "Rayman2 Mod Manager", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}

	// Get pointer to the original functions to call them back

	EXPORT_GLI_DRV_lGetDllInfo = (BOOL(*)(const char*, char*))GetProcAddress(hOrig, "GLI_DRV_lGetDllInfo");

	GETEXPORT(GLI_DRV_lSetCommonFct);
	GETEXPORT(GLI_DRV_lSetCommonData);
	GETEXPORT(GLI_DRV_bBeginScene);
	GETEXPORT(GLI_DRV_bEndScene);
	GETEXPORT(GLI_DRV_bLockDevice);
	GETEXPORT(GLI_DRV_bPrepareForGliWindowed);
	GETEXPORT(GLI_DRV_bUnlockDevice);
	GETEXPORT(GLI_DRV_bWindowedModeIsOptimized);
	GETEXPORT(GLI_DRV_fn_lGetAllDisplayConfig);
	GETEXPORT(GLI_DRV_fnl_EnumModes);
	GETEXPORT(GLI_DRV_hChangeMode);
	GETEXPORT(GLI_DRV_lGetSizeOfTexture);
	GETEXPORT(GLI_DRV_vActivateGli);
	GETEXPORT(GLI_DRV_vAddBlackPolygon);
	GETEXPORT(GLI_DRV_vClearDevice);
	GETEXPORT(GLI_DRV_vClearZBufferRegion);
	GETEXPORT(GLI_DRV_vCloseDriver);
	GETEXPORT(GLI_DRV_vComputeFogEffect);
	GETEXPORT(GLI_DRV_vDoOpaqueTextureSelection);
	GETEXPORT(GLI_DRV_vDownLoadTextures);
	GETEXPORT(GLI_DRV_vFlipDevice);
	GETEXPORT(GLI_DRV_vFlipDeviceWithSyncro);
	GETEXPORT(GLI_DRV_vGetStats);
	GETEXPORT(GLI_DRV_vNoBlackPolygon);
	GETEXPORT(GLI_DRV_vNonOptimizedWindowedMode);
	GETEXPORT(GLI_DRV_vOptimizedWindowedMode);
	GETEXPORT(GLI_DRV_vPrepareForGliFullScreen);
	GETEXPORT(GLI_DRV_vSendSingleLineToClip);
	GETEXPORT(GLI_DRV_vSendSpriteToClip);
	GETEXPORT(GLI_DRV_vSendSpriteToClipWithColors);
	GETEXPORT(GLI_DRV_vSendSpriteToClipWithUV);
	GETEXPORT(GLI_DRV_vSetClipWindow);
	GETEXPORT(GLI_DRV_vSetZClip);
	GETEXPORT(GLI_DRV_vUnLoadTextures);
	GETEXPORT(GLI_DRV_vWrite16bBitmapToBackBuffer);
	GETEXPORT(GLI_DRV_xClearViewingList);
	GETEXPORT(GLI_DRV_xInitDriver);
	GETEXPORT(GLI_DRV_xSendElementTIToClip_TRIANGLES);
	GETEXPORT(GLI_DRV_xSendListToViewport);
	GETEXPORT(GLI_DRV_xSendSingleTriangleToClip_TRIANGLES);
	GETEXPORT(GLI_DRV_vReadaptDisplay);
}