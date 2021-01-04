/*
 * Rayman2 Mod Loader
 */

#ifndef RAYMAN2MODLOADER_H
#define RAYMAN2MODLOADER_H

#if !defined(_M_IX86) && !defined(__i386__)
#error Mods must be built targeting 32-bit x86, change your settings.
#endif

#define Sint32 signed __int32
#define Uint32 unsigned __int32
#define Sint16 signed __int16
#define Uint16 unsigned __int16
#define __byte unsigned __int8

#include "MemAccess.h"
#include "Rayman2ModInfo.h"
#include "Rayman2Enums.h"
#include "Rayman2Structs.h"
#include "Rayman2Variables.h"
#include "Rayman2Functions.h"

#endif /* RAYMAN2MODLOADER_H */