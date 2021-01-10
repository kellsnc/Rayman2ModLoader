#pragma once

extern FileMap rayman2_fileMap;

const char* _ReplaceFile(const char* lpFileName);
void HookFileFunctions();
void ScanModFolder(const std::wstring str, int loadorder);