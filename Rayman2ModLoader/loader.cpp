/*
 * Rayman2 Mod Loader.
 * Main Loader, reads config & pass to Mod Loader & CheatCode Loader
 */

#include "pch.h"

std::wstring GamePath;
std::wstring ConfigPath = L"Rayman2ModLoader.ini";
std::wstring CodesPath = L"Mods\\CheatCodes.lst";
std::wstring ModsPath = L"Mods\\";

std::string DLLName = "GliVd1";
std::string APIName = "Glide2";

GameConfig_t GameConfig = {
    /*   ScreenWidth   */ 1920,
    /*   ScreenHeight  */ 1080,
    /*   ScreenDepth   */ 32,
    /*   ParticuleRate */ 3.0f,
    /*   TexturesMem   */ 6,
    /*   SoundHD       */ true,
    /*   Complete      */ false
};

void SplitFilename(std::wstring* str) {
    std::string::size_type slash = str->find_last_of(L"/\\");
    *str = str->substr(0, slash);
}

bool IsPathAbsolute(std::wstring* str) {
    return &str->at(1) == L":";
}

void GetGamePath() {
    wchar_t pathbuf[MAX_PATH];
    GetModuleFileNameW(nullptr, pathbuf, MAX_PATH);

    GamePath = pathbuf;
    SplitFilename(&GamePath);
}

void GetConfigPath() {
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    for (int i = 1; i < argc; i++) {
        if (!wcscmp(argv[i], L"-loaderini")) {
            ConfigPath = argv[++i];
        }
    }

    if (IsPathAbsolute(&ConfigPath) == false) {
        ConfigPath = GamePath + L"\\" + ConfigPath;
    }

    ConfigPath = ConfigPath;
}

void ApplyGameConfigs() {
    OptionScreenWidth = GameConfig.ScreenWidth;
    OptionScreenHeight = GameConfig.ScreenHeight;
    OptionScreenDepth = GameConfig.ScreenDepth;
    OptionParticuleRate = GameConfig.ParticuleRate;
    OptionTexturesMem = GameConfig.TexturesMem;
}

void ReadGameConfig(const IniGroup* gameconfig) {
    if (gameconfig) {
        GameConfig.ScreenWidth = gameconfig->getInt("ScreenWidth", GameConfig.ScreenWidth);
        GameConfig.ScreenHeight = gameconfig->getInt("ScreenHeight", GameConfig.ScreenHeight);
        GameConfig.ScreenDepth = gameconfig->getInt("ScreenDepth", GameConfig.ScreenDepth);
        GameConfig.ParticuleRate = gameconfig->getFloat("ParticuleRate", GameConfig.ParticuleRate);
        GameConfig.TexturesMem = gameconfig->getInt("TexturesMem", GameConfig.TexturesMem);
        GameConfig.SoundHD = gameconfig->getBool("SoundHD", GameConfig.SoundHD);
        GameConfig.Complete = gameconfig->getBool("SoundHD", GameConfig.Complete);
    }
    
    ApplyGameConfigs();
}

void ReadConfig() {
    const IniFile* config = new IniFile(ConfigPath);
    const IniGroup* loaderconfig = config->getGroup("ModLoader");

    if (loaderconfig) {
        DLLName = loaderconfig->getString("GlideDLL", DLLName);
        APIName = loaderconfig->getString("GlideAPI", APIName);
        ModsPath = loaderconfig->getWString("ModsPath", ModsPath);
        CodesPath = loaderconfig->getWString("CodesPath", CodesPath);

        if (loaderconfig->getBool("OverrideConfig", true)) {
            ReadGameConfig(config->getGroup("Rayman2"));
        }

        // Load codes

        if (IsPathAbsolute(&CodesPath) == false) {
            CodesPath = GamePath + L"\\" + CodesPath;
        }

        std::string codeslist = loaderconfig->getString("Codes", "");

        if (codeslist.empty() == false) {
            InitCodes(&codeslist, CodesPath);
        }

        // Load mods

        if (IsPathAbsolute(&ModsPath) == false) {
            ModsPath = GamePath + L"\\" + ModsPath;
        }

        std::string modlist = loaderconfig->getString("Mods", "");

        if (modlist.empty() == false) {
            InitMods(&modlist, ModsPath);
        }
    }
    else {
        const int type = MessageBox(nullptr, L"Cannot find the Mod Loader configuration.\n\n"
            L"Using default configuration with no mod/code enabled.",
            L"Rayman2 Mod Loader", MB_OKCANCEL | MB_ICONERROR);

        if (type == IDOK) {
            ApplyGameConfigs();
        }
        else {
            ExitProcess(1);
        }
    }
    
    delete config;
}

void LoaderInit() {
    GetGamePath();
    GetConfigPath();
    ReadConfig();
}