#pragma once

#include <vector>
#include <string>
#include <fstream>

/*
	Based on work from:
		szymski: https://github.com/szymski
		RayCarrot: https://github.com/RayCarrot


	File Structure:
		0x4 magic (888)
		0x4 width
		0x4 height
		0x1 channelCount
		0x1 repeatByte
		Channel B
		Channel G
		Channel R
		(Channel A)

	Channel:
		0x1 color;

		If colortype is repeatByte then we read 2 more bytes:
		0x1 color_to_repeat;
		0x1 repeat_count;
*/

class GraphicFile {
private:
	unsigned int version = 888;
	unsigned int width, height = 0;
	unsigned char channelCount = 3;
	unsigned char repByte = 0x1;
	std::vector<unsigned char> pixels;

	void UpdateRepeatByte();
	void PNGtoGF(const unsigned char* image);
public:
	void GetRawData(std::vector<char>& bytes);
	void ReadPNG(const char* path);
	void ReadPNG(std::string path);

	explicit GraphicFile();
};