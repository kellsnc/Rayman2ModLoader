/**
 * Rayman2 Mod Loader
 * Parse Cheatcode files
 */

#include "pch.h"

void InitCodeFile(const std::wstring path, const char* debug) {
	std::ifstream codes_str(path, std::ifstream::binary);

	if (codes_str.is_open()) {
		static const char codemagic[6] = { 'c', 'o', 'd', 'e', 'v', '5' };
		char buf[sizeof(codemagic)];
		codes_str.read(buf, sizeof(buf));

		if (!memcmp(buf, codemagic, sizeof(codemagic))) {
			int codecount_header;
			codes_str.read((char*)&codecount_header, sizeof(codecount_header));
			PrintDebug("[ModLoader] Loading %d %s...\n", codecount_header, debug);
			codes_str.seekg(0);
			int codecount = codeParser.readCodes(codes_str);

			if (codecount >= 0) {
				PrintDebug("Loaded %d %s.\n", codecount, debug);
				codeParser.processCodeList();
			}
			else {
				PrintDebug("ERROR loading #s: ", debug);
				switch (codecount) {
				case -EINVAL:
					PrintDebug("Code file is not in the correct format.\n");
					break;
				default:
					PrintDebug("\n");
					break;
				}
			}
		}
		else {
			PrintDebug("Code file is not in the correct format.\n");
		}

		codes_str.close();
	}
}

void InitCodes(const std::wstring* path) {
	// Check for patches.
	std::ifstream patches_str(*path + L"Patches.dat", std::ifstream::binary);

	InitCodeFile(*path + L"\\Patches.dat", "patches");
	InitCodeFile(*path + L"\\Codes.dat", "codes");
}