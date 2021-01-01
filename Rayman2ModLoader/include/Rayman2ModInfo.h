/*
 * Rayman2 Mod Loader.
 * Mod metadata structures
 */

#ifndef RAYMAN2MODLOADER_MODINFO_H
#define RAYMAN2MODLOADER_MODINFO_H

// API Version
static const int ModLoaderVer = 1;

struct HelperFunctions {
	// The version of the structure.
	int Version;

	// Returns the path where main game save files are stored.
	const char* (__cdecl* GetMainSavePath)();
};

typedef void(__cdecl* ModInitFunc)(const char* path, const HelperFunctions& helperFunctions);

typedef void(__cdecl* ModEvent)();

struct ModInfo
{
	int Version;
	ModInitFunc Init;
};

#endif