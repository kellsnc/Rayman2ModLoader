#pragma once

int __cdecl PrintDebug(const char* Format, ...);
void InitOutput(const IniGroup* loaderconfig);
void DeleteOutput();