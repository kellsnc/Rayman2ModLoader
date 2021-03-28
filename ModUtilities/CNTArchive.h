#pragma once

#include <vector>
#include <string>
#include <fstream>

/*
	Based on:
		szymski's work: https://github.com/szymski
		reversing the game's code

	File Structure:
		0x4 folderCount
		0x4 fileCount
		0x1 names are encrypted using encryptionKey
		0x1 use security check (will check if each byte of each folder name add up to "securityKey")
		0x1 encryptionKey (each byte in names ^ (XOR) encryptionKey)
		[Folders]
		0x1 securityKey (null if no folder or if security check disabled)
		[Files]

	Folders:
		0x4 amount of bytes for the name (string isn't null-terminated)
		(0x1 * amount of bytes) name string

	Files:
		0x4 folder index (Folders[x])
		0x4 amount of bytes for the name (string isn't null-terminated)
		(0x1 * amount of bytes) name string
		0x4 encryptionKey
		0x4 ???
		0x4 pointer to raw file data
		0x4 byte count of raw data
*/

struct CNTFile {
	std::string name;
	unsigned int folderID;
	char* filePointer;
	unsigned int fileSize;
	unsigned int encryptionKey;
	unsigned int unknown;
};

struct CNTFolder {
	std::string name;
};

class CNTArchive
{
private:
	unsigned int folderCount = 0;
	unsigned int fileCount = 0;
	unsigned __int8 encryptedNames = 0;
	unsigned __int8 securityCheck = 0;
	unsigned __int8 encryptionKey = 0;
	unsigned __int8 securityKey = 0;
	std::vector<CNTFolder> folders;
	std::vector<CNTFile> files;

	int GetDirectoryIndex(std::string path);
	int GetFileIndex(std::string name, int folderid);

	void AddOrReplaceFile(const std::string& fileName, char* buffer, const int length);
	void AddOrReplaceFile(const std::string& fileName);

	void ReadStream(std::istream& stream);
	void SaveToStream(std::ostream& output);

	void DecodeName(std::string* name);
	void UpdateCounts();
public:
	explicit CNTArchive(const char* fileName);
	explicit CNTArchive(const std::string& fileName);
	explicit CNTArchive(std::istream& fileName);
	explicit CNTArchive();

	void Merge(const CNTArchive& archive);

	void SaveToFile(const char* path);
	void SaveToFile(const std::string& path);

	CNTFile* FindFile(const char* fileName);
	CNTFile* FindFile(std::string fileName);
	
	void AddFile(const char* fileName);
	void AddFile(const std::string& fileName);
	void AddFile(const std::string& fileName, const std::vector<char>& bytes);
};