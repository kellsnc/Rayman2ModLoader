/*
 * Rayman2 Mod Loader.
 * Allow for individual texture replacement by creating a folder named exactly like the original cnt file.
 */

#include "pch.h"
#include "CNTArchive.h"
#include <algorithm>

Trampoline* LoadGFFile_t = nullptr;

std::vector<std::string> TextureReplacementMap = {};

void AddToTextureMap(const std::string& path) {
	TextureReplacementMap.push_back(path);
}

bool IsTextureReplaced(std::string optFolder, std::string file, std::string* replacedPath) {
	std::string fullPath = optFolder + "\\" + file;
	transform(fullPath.begin(), fullPath.end(), fullPath.begin(), ::tolower);

	// check if the texture in "optFolder\\file"  is being replaced by a mod
	for (auto& replfile : TextureReplacementMap) {
		std::string replfile_ = replfile;
		std::size_t pos = replfile.find(".cnt");

		// We provide support for folder names that contain ".CNT" (compatibility with older version)
		if (pos != std::string::npos) {
			replfile_.erase(pos, 4);
		}
		
		// Check if the texture path corresponds
		if (!fullPath.compare(replfile_)) {
			std::string relPath = (std::string)rayman2_fileMap.replaceFile(replfile.c_str());
			*replacedPath = relPath.substr(0, relPath.find(file) - 1).c_str();
			return true;
		}
	}
	
	return false;
}

GFInfo* __cdecl LoadGFFile_r(CNTInfo* cnt, const char* optFolder, const char* gfName) {
	std::string replacedPath; // The replaced texture folder path

	// If the texture is being replaced, force LoadGFFile to look for textures in a folder
	if (IsTextureReplaced((std::string)optFolder, (std::string)gfName, &replacedPath)) {
		return T_TARGET_DYNAMIC(LoadGFFile)(nullptr, replacedPath.c_str(), gfName);
	}

	return T_TARGET_DYNAMIC(LoadGFFile)(cnt, optFolder, gfName);
}

void TexturesInit() {
	if (TextureReplacementMap.size() > 0) {

		// Set the fail safe folder to look for textures
		const char* texfolder = "Data\\Textures";
		memcpy(&TexturesPath, texfolder, strlen(texfolder) + 1);

		// Hook LoadGFFile
		LoadGFFile_t = new Trampoline((int)LoadGFFile, (int)LoadGFFile + 0x6, LoadGFFile_r);
	}
}