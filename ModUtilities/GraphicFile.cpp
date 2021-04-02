#include "pch.h"
#include "GraphicFile.h"
#include "lodepng.h"

#include <algorithm>

#define GetPixel(a) (pixel + a) * channelCount + channel
#define CharPtrAndLength(t) (char*)&t, sizeof(t)

void ReadBytes(std::vector<char>& bytes, char* value, int amount) {
	for (int i = 0; i < amount; ++i) {
		bytes.push_back(value[i]);
	}
}

void GraphicFile::GetRawData(std::vector<char>& bytes) {
	bytes.reserve(pixels.size()); // augment capacity to avoid multiple reallocations.

	ReadBytes(bytes, CharPtrAndLength(version));
	ReadBytes(bytes, CharPtrAndLength(width));
	ReadBytes(bytes, CharPtrAndLength(height));
	bytes.push_back(channelCount);
	bytes.push_back(repByte);

	for (int channel = 0; channel < channelCount; ++channel) {
		int pixel = 0;

		while (pixel < pixels.size() / channelCount) {
			unsigned char curPix = pixels[GetPixel(0)];

			if ((GetPixel(2) < pixels.size() &&
				curPix == pixels[GetPixel(1)] &&
				curPix == pixels[GetPixel(2)]) || curPix == repByte) {

				unsigned char repPix = curPix;
				bytes.push_back(repByte);
				bytes.push_back(repPix);

				unsigned int repCount = 0;

				while (pixel < pixels.size() / channelCount) {
					curPix = pixels[GetPixel(0)];

					if (curPix != repPix || repCount >= 0xFF || GetPixel(1) >= pixels.size()) {
						break;
					}

					pixel++;
					repCount++;
				}

				bytes.push_back(repCount);
			}
			else {
				bytes.push_back(curPix);
				pixel++;
			}
		}
	}

	bytes.shrink_to_fit(); // compression might have left a lot of memory, shrink the vector.
}

void GraphicFile::UpdateRepeatByte() {
	std::vector<int> temp;
	temp.resize(0xFF + 1);

	for (auto& p : pixels) {
		temp[p]++;
	}

	int min = *std::min_element(temp.begin(), temp.end());

	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i] == min) {
			repByte = i;
			return;
		}
	}
}

void GraphicFile::PNGtoGF(const unsigned char* image) {
	for (int y = height - 1; y >= 0; y--) { // the rows are stored inversed in GF
		int c = 0; // current color

		for (int x = 0; x < channelCount * width; x++) {
			int inc = c;

			//Convert RGB(A) into BGR(A)
			if (c == 0) {
				inc = 2;
			}
			else if (c == 2) {
				inc = 0;
			}

			pixels.push_back(image[4 * (width * y + x / channelCount) + inc]);

			c++;

			if (c >= channelCount) {
				c = 0;
			}
		}
	}
}

void GraphicFile::ReadPNG(const char* path) {
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;

	lodepng::load_file(png, path);
	lodepng::State state;

	unsigned error = lodepng::decode(image, width, height, state, png);

	if (error) {
		return;
	}

	pixels.clear();

	// lodepng::decode always outputs RGBA, this tells the actual number of channels
	switch (state.info_png.color.colortype) {
	case LodePNGColorType::LCT_RGB:
		channelCount = 3;
		break;
	case LodePNGColorType::LCT_RGBA:
		channelCount = 4;
		break;
	default:
		return;
	}

	// reserve space to avoid multiple reallocation of vector
	pixels.reserve(width * height * channelCount);

	PNGtoGF(&image[0]);
	UpdateRepeatByte();
}

void GraphicFile::ReadPNG(std::string path) {
	ReadPNG(path.c_str());
}

void GraphicFile::ReadBMP(const char* path) {
	std::vector<unsigned char> bmp;

	lodepng::load_file(bmp, path);

	if (bmp.size() < 54 || bmp[0] != 'B' || bmp[1] != 'M' || (bmp[28] != 24 && bmp[28] != 32)) {
		return;
	}

	pixels.clear();

	width = bmp[18] + bmp[19] * 256;
	height = bmp[22] + bmp[23] * 256;
	channelCount = bmp[28] / 8;

	unsigned int pixeloffset = bmp[10] + 256 * bmp[11];

	// reserve space to avoid multiple reallocation of vector
	pixels.resize(width * height * channelCount);

	for (int i = 0; i < width * height * channelCount; i += channelCount) {
		pixels[i + 0] = bmp[pixeloffset + i + 0];
		pixels[i + 1] = bmp[pixeloffset + i + 1];
		pixels[i + 2] = bmp[pixeloffset + i + 2];

		if (channelCount == 4) {
			pixels[i + 3] = bmp[pixeloffset + i + 3];
		}
	}

	UpdateRepeatByte();
}

void GraphicFile::ReadBMP(std::string path) {
	ReadBMP(path.c_str());
}

void GraphicFile::Save(std::string path) {
	std::vector<char> output;

	GetRawData(output);

	std::ofstream file;

	file.open(path, std::ios::out | std::ios::binary);
	file.write(output.data(), output.size());
	file.close();
}

GraphicFile::GraphicFile() { }