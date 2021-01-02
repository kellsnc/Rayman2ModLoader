#pragma once

void __cdecl PrintDebug(const char* Format, ...);
void InitOutput(const IniGroup* loaderconfig);
void DeleteOutput();