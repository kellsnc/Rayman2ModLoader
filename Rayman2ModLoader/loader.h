#pragma once

struct GameConfig_t {
	int ScreenWidth;
	int ScreenHeight;
	int ScreenDepth;
	float ParticuleRate;
	int TexturesMem;

	// Unused
	bool SoundHD;
	bool Complete;
};

extern std::string DLLName;
extern std::string APIName;
extern GameConfig_t GameConfig;

void LoaderInit();