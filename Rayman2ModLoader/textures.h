#pragma once

int AddCNTArchiveToList(const std::string& path);
void AddFileToReplacementArchive(const std::string& path, const int index);
void AddFileStreamToReplacementArchive(const std::string& path, const std::vector<char>& bytes, const int index);

void* __cdecl FIL_fn_vOpenConcatFile_r(const char* Str);

void TexturesInit();
void TexturesDelete();