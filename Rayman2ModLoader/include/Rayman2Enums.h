/*
 * Rayman2 Mod Loader
 * Rayman2 enums
 */

#ifndef RAYMAN2MODLOADER_ENUMS_H
#define RAYMAN2MODLOADER_ENUMS_H

enum Languages : __int32
{
	Language_English,
	Language_French,
	Language_Spanish,
	Language_Italian,
	Language_German
};

enum LEVEL_STATE : __byte
{
	LEVEL_STATE_PRELOAD = 0x1,
	LEVEL_STATE_LOADED_FILES = 0x3,
	LEVEL_STATE_LOADINGSCREEN = 0x5,
	LEVEL_STATE_LOADED = 0x9
};

enum SOUND_BANK_STATE
{
	SOUND_BANK_STATE_LOADED = 0x1,
	SOUND_BANK_STATE_LOADING = 0x4
};

enum SuperObjectType
{
	SuperObjectType_0 = 0x0,
	SuperObjectType_1 = 0x1,
	SuperObjectType_2_DYN = 0x2
};

#endif