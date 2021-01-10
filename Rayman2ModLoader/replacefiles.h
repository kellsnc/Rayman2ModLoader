#pragma once

extern FileMap rayman2_fileMap;

void HookFileFunctions();
void ScanModFolder(const std::wstring str, int loadorder);