#pragma once

extern FileMap rayman2_fileMap;

void HookFileFunctions();
void ScanModFolder(const std::string& str, int loadorder);
void ScanModDLLFolder(const std::string& str, int loadorder);