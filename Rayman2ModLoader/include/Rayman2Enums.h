/*
 * Rayman2 Mod Loader
 * Rayman2 enums
 */

#ifndef RAYMAN2MODLOADER_ENUMS_H
#define RAYMAN2MODLOADER_ENUMS_H

#include <cstdint>

enum Languages : int32_t
{
	Language_English,
	Language_French,
	Language_Spanish,
	Language_Italian,
	Language_German
};

enum ENGINE_STATE : int8_t
{
	ENGINE_STATE_0 = 0x0,
	ENGINE_STATE_PRELOAD = 0x1,
	ENGINE_STATE_EXIT = 0x2,
	ENGINE_STATE_INITSTUFF = 0x3,
	ENGINE_STATE_INITLEVEL = 0x4,
	ENGINE_STATE_LOADLEVEL = 0x5,
	ENGINE_STATE_6 = 0x6,
	ENGINE_STATE_7 = 0x7,
	ENGINE_STATE_8 = 0x8,
	ENGINE_STATE_INGAME = 0x9,
	ENGINE_STATE_10 = 0xA,
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