#include "pch.h"
#include <io.h>
#include <fcntl.h>

#include "CNTArchive.h"
#include "..\mod-loader-common\ModLoaderCommon\FileSystem.h"

void CNTArchive::DecodeName(std::string* name) {
	if (encryptedNames == (unsigned char)1) {
		for (char& c : *name) {
			c ^= encryptionKey;
		}
	}
}

CNTFile* CNTArchive::FindFile(const char* fileName) {
	return FindFile(std::string(fileName));
}

CNTFile* CNTArchive::FindFile(std::string fileName) {
	size_t folderscount = folders.size();

	// Separate file name and folders
	std::string name = GetBaseName(fileName);
	std::string directories = GetDirectory(fileName);
	
	if (folderscount > 0) {
		for (int i = 0; i < folderscount; ++i) {
			if (folders[i].name.compare(directories) == 0) {
				for (int i = 0; i < files.size(); ++i) {
					if (files[i].name.compare(name) == 0 && folders[files[i].folderID].name.compare(directories) == 0) {
						return &files[i];
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < files.size(); ++i) {
			if (files[i].name.compare(name) == 0) {
				return &files[i];
			}
		}
	}

	return nullptr;
}

int CNTArchive::GetDirectoryIndex(std::string path) {
	for (int i = 0; i < folders.size(); ++i) {
		if (folders[i].name.compare(path) == 0) {
			return i;
		}
	}

	return folders.size();
}

int CNTArchive::GetFileIndex(std::string name) {
	for (int i = 0; i < files.size(); ++i) {
		if (files[i].name.compare(name) == 0) {
			return i;
		}
	}

	return files.size();
}

void CNTArchive::AddOrReplaceFile(const std::string& fileName) {
	std::string truncName = fileName;
	size_t pos = truncName.find(std::string(".cnt"));

	if (pos != std::string::npos) {
		truncName = truncName.substr(pos + 5);
	}

	std::string name = GetBaseName(truncName);
	std::string directories = GetDirectory(truncName);
	
	// Get length of file using this horrible thing
	int file_;
	_sopen_s(&file_, fileName.c_str(), _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD);
	int length = _filelength(file_);
	_close(file_);

	std::ifstream file(fileName, std::ios_base::binary);
	char* buffer = new char[length];
	file.read(buffer, length);
	file.close();

	CNTFile* existingFile = FindFile(truncName);

	if (existingFile) {
		// Replace

		delete[] existingFile->filePointer;
		existingFile->fileSize = length;
		existingFile->filePointer = buffer;
		existingFile->encryptionKey = 0;
		existingFile->unknown = 0;
	}
	else {
		// Add

		int dirid = std::string::npos;

		if (directories.empty() == false) {
			dirid = GetDirectoryIndex(directories);

			if (dirid >= folders.size()) {
				CNTFolder folder;
				folder.name = directories.c_str();
				folders.push_back(folder);
			}
		}

		CNTFile cntfile;
		cntfile.name = name;
		cntfile.folderID = dirid;
		cntfile.fileSize = length;
		cntfile.filePointer = buffer;
		cntfile.encryptionKey = 0;
		cntfile.unknown = 0;
		files.push_back(cntfile);
	}
}

void CNTArchive::AddFile(const char* fileName) {
	AddOrReplaceFile(std::string(fileName));
}

void CNTArchive::AddFile(const std::string& fileName) {
	AddOrReplaceFile(fileName);
}

void CNTArchive::UpdateCounts() {
	folderCount = folders.size();
	fileCount = files.size();
}

void CNTArchive::SaveToStream(std::ostream& output) {
	UpdateCounts();

	encryptedNames = encryptionKey != 0 ? (unsigned char)0x1 : (unsigned char)0x0;
	securityKey = 0;

	output.write((char*)&folderCount, 0x4);
	output.write((char*)&fileCount, 0x4);
	output.write((char*)&encryptedNames, 0x1);
	output.write((char*)&securityCheck, 0x1);
	output.write((char*)&encryptionKey, 0x1);

	for (auto& folder : folders) {
		std::string name = folder.name;
		unsigned int length = name.length();

		for (char& c : name) {
			if (securityCheck == (unsigned char)0x1) {
				securityKey += c;
			}

			if (encryptedNames == (unsigned char)0x1) {
				c ^= encryptionKey;
			}
		}

		output.write((char*)&length, 0x4);
		output.write((char*)&name[0], length);
	}

	output.write((char*)&securityKey, 0x1);

	std::vector<int> pointersLocations;
	std::vector<int> newLocations;

	for (auto& cntfile : files) {
		std::string name = cntfile.name;
		unsigned int length = name.length();

		output.write((char*)&cntfile.folderID, 0x4);

		DecodeName(&name);

		output.write((char*)&length, 0x4);
		output.write((char*)&name[0], length);

		output.write((char*)&cntfile.encryptionKey, 0x4);
		output.write((char*)&cntfile.unknown, 0x4);

		pointersLocations.push_back(output.tellp());

		output.write((char*)&cntfile.filePointer, 0x4);
		output.write((char*)&cntfile.fileSize, 0x4);
	}

	for (auto& cntfile : files) {
		newLocations.push_back(output.tellp());
		output.write(cntfile.filePointer, cntfile.fileSize);
	}

	for (int i = 0; i < pointersLocations.size(); ++i) {
		output.seekp(pointersLocations[i], std::ios_base::beg);
		output.write((char*)&newLocations[i], 0x4);
	}
}

void CNTArchive::SaveToFile(const char* path) {
	std::ofstream output(path, std::ios_base::binary);

	if (output.is_open()) {
		SaveToStream(output);
		output.close();
	}
}

void CNTArchive::SaveToFile(const std::string& path) {
	std::ofstream output(path, std::ios_base::binary);

	if (output.is_open()) {
		SaveToStream(output);
		output.close();
	}
}

void CNTArchive::ReadStream(std::istream& stream) {
	stream.read((char*)&folderCount, 0x4);
	stream.read((char*)&fileCount, 0x4);
	stream.read((char*)&encryptedNames, 0x1);
	stream.read((char*)&securityCheck, 0x1);
	stream.read((char*)&encryptionKey, 0x1);

	unsigned __int8 magicthing = 0;

	if (folderCount) {
		for (int i = 0; i < folderCount; ++i) {
			CNTFolder cntfolder;
			int length;

			stream.read((char*)&length, 0x4);
			cntfolder.name.resize(length);

			stream.read((char*)&cntfolder.name[0], length);

			for (char& c : cntfolder.name) {
				if (encryptedNames == (unsigned char)0x1) {
					c ^= encryptionKey;
				}

				if (securityCheck == (unsigned char)0x1) {
					magicthing += c;
				}
			}

			folders.push_back(cntfolder);
		}
	}

	// some kind of security
	stream.read((char*)&securityKey, 0x1);

	if (securityKey != magicthing) {
		// Invalid
	}

	if (fileCount) {
		for (int i = 0; i < fileCount; ++i) {
			CNTFile cntfile;
			int length;

			stream.read((char*)&cntfile.folderID, 0x4);
			stream.read((char*)&length, 0x4);

			cntfile.name.resize(length);

			stream.read((char*)&cntfile.name[0], length);

			DecodeName(&cntfile.name);

			stream.read((char*)&cntfile.encryptionKey, 0x4);
			stream.read((char*)&cntfile.unknown, 0x4);
			stream.read((char*)&cntfile.filePointer, 0x4);
			stream.read((char*)&cntfile.fileSize, 0x4);

			files.push_back(cntfile);
		}

		for (int i = 0; i < fileCount; ++i) {
			char* file = new char[files[i].fileSize];

			stream.seekg((int)files[i].filePointer, std::ios_base::beg);
			stream.read(file, files[i].fileSize);

			files[i].filePointer = file;
		}
	}
}

void CNTArchive::Merge(const CNTArchive& archive) {
	std::vector<std::pair<unsigned int, unsigned int>> newDirectoriesIndices; // old index -> new index

	for (int i = 0; i < archive.folders.size(); ++i) {
		int index = GetDirectoryIndex(archive.folders[i].name);

		if (index < folders.size()) {
			// folder exists
			newDirectoriesIndices.emplace_back(i, index);
		}
		else {
			// new folder
			CNTFolder newfolder = { archive.folders[i].name };
			folders.push_back(newfolder);
			newDirectoriesIndices.emplace_back(i, folders.size() - 1);
		}
	}
	
	for (auto& impfile : archive.files) {
		int index = GetFileIndex(impfile.name);

		if (index < files.size()) {
			// file exists
			delete[] files[index].filePointer; // remove previous file

			files[index] = impfile;
		}
		else {
			CNTFile file = impfile;
			files.push_back(file);
		}

		for (auto& i : newDirectoriesIndices) {
			if (files[index].folderID == i.first) {
				files[index].folderID = i.second;
			}
		}
	}

	UpdateCounts();
}

CNTArchive::CNTArchive(std::istream& stream) {
	ReadStream(stream);
}

CNTArchive::CNTArchive(const std::string& fileName) {
	std::ifstream stream(fileName, std::ios::binary);
	ReadStream(stream);
	stream.close();
}

CNTArchive::CNTArchive(const char* fileName) {
	std::ifstream stream(fileName, std::ios::binary);
	ReadStream(stream);
	stream.close();
}

CNTArchive::CNTArchive() { }