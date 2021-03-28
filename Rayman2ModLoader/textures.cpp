/*
 * Rayman2 Mod Loader.
 * Allow for individual texture replacement by creating a folder named exactly like the original cnt file.
 */

#include "pch.h"
#include "CNTArchive.h"
#include <algorithm>

// This currently works by catching the cnt file about to be loaded
// merge it with textures files loaded by the mod loader, save it as a
// different file and redirect it. The new files are deleted on game exit.
// Todo: rewrite the cnt file loading code, it currently crashes even with same output

std::vector<std::pair<std::string, CNTArchive*>> archivesReplacements;
std::vector<std::string> filesToDelete;

int AddCNTArchiveToList(const std::string& path) {
	archivesReplacements.emplace_back(path, new CNTArchive());
	return archivesReplacements.size() - 1;
}

void AddFileToReplacementArchive(const std::string& path, const int index) {
	archivesReplacements[index].second->AddFile(path);
}

void AddFileStreamToReplacementArchive(const std::string& path, const std::vector<char>& bytes, const int index) {
	archivesReplacements[index].second->AddFile(path, bytes);
}

void* __cdecl FIL_fn_vOpenConcatFile_r(const char* Str) {
	std::string inputPath = Str;
	std::transform(inputPath.begin(), inputPath.end(), inputPath.begin(), ::tolower);

	std::string outputPath = GetDirectory(Str) + "\\." + GetBaseName(Str);
	std::transform(outputPath.begin(), outputPath.end(), outputPath.begin(), ::tolower);

	if (FileExists(outputPath)) {
		std::remove(outputPath.c_str());
	}

	// Check if the file has had external modifications
	for (auto& archive : archivesReplacements) {
		std::transform(archive.first.begin(), archive.first.end(), archive.first.begin(), ::tolower);

		if (archive.first.find(inputPath) != std::string::npos) {
			if (FileExists(outputPath)) {
				inputPath = outputPath;
			}
			else {
				filesToDelete.push_back(outputPath);
			}

			CNTArchive* cnt = new CNTArchive(inputPath);

			cnt->Merge(*archive.second); // merge the new textures
			cnt->SaveToFile(outputPath); // save file

			// free allocated archive
			delete archive.second; 
			archive.second = nullptr;
		}
	}

	return FIL_fn_vOpenConcatFile(outputPath.c_str());
}

void TexturesDelete() {
	for (auto& archive : archivesReplacements) {
		if (archive.second) {
			delete archive.second; // free allocated archive
		}
	}

	for (auto& path : filesToDelete) {
		if (FileExists(path)) {
			std::remove(path.c_str());
		}
	}
}

void TexturesInit() {
	if (archivesReplacements.size() > 0) {
		WriteCall((void*)0x4250DF, FIL_fn_vOpenConcatFile_r);
		WriteCall((void*)0x45ECCF, FIL_fn_vOpenConcatFile_r);
	}
}