/*
 * Rayman2 Mod Loader
 * Mod metadata structures
 */

#ifndef RAYMAN2MODLOADER_MODINFO_H
#define RAYMAN2MODLOADER_MODINFO_H

// API Version
static const int ModLoaderVer = 1;

struct HelperFunctions {
	// The version of the structure.
	int Version;

	// Print to Mod Loader console / file
	void(__cdecl* PrintDebug)(const char* Format, ...);

	// Sets the title of the main window
	void(__cdecl* SetWindowTitle)(const char* title);

	// Returns the path where main game save files are stored.
	const char* (__cdecl* GetMainSavePath)();

	// If you've created a file that doesn't exist in the game and want other mods
	// to be able to replace it, use this function to always return the real path
	// Example: `GetReplaceablePath("Data\\MyCustomFile.dsb");`
	const char* (__cdecl* GetReplaceablePath)(const char* path);

	// Replace source file with destination file
	// Mods will not be able to replace your file unless they name it like the destination file.
	// Example: `_ReplaceFile("Data\\Game.dsb", "Data\\CustomGame.dsb");`
	void (__cdecl* _ReplaceFile)(const char* src, const char* dst);
};

typedef void(__cdecl* ModInitFunc)(const char* path, const HelperFunctions& helperFunctions);
typedef void(__cdecl* ModEvent)();

struct ModInfo {
	int Version;
};

#endif