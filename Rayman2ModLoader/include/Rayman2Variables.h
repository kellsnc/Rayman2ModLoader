/*
 * Rayman2 Mod Loader
 * Rayman2 variables
 */

#define PATH_MAX 256

#ifndef RAYMAN2MODLOADER_VARS_H
#define RAYMAN2MODLOADER_VARS_H

DataPointer(int, OptionTexturesMem, 0x4A077C);
DataPointer(int, OptionParticuleRate, 0x4A1234);
DataArray(char, cmdline, 0x4E0DA0, PATH_MAX);
DataPointer(int, OptionScreenWidth, 0x5047FC);
DataPointer(int, OptionScreenHeight, 0x504800);
DataPointer(int, OptionScreenMode, 0x504804);
DataPointer(int, OptionScreenDepth, 0x504808);
DataPointer(int, OptionLanguage, 0x500FA8);

#endif