#pragma once

#include <vector>
#include <string>
#include <fstream>

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
	int GetFileIndex(std::string name);
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
};