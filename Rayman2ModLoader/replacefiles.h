#pragma once

extern FileMap rayman2_fileMap;

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
const char* _ReplaceFile(const char* lpFileName);
void HookCreateFileA();
void ScanModFolder(const std::wstring str, int loadorder);