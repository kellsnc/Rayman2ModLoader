/*
 * Rayman2 Mod Loader.
 * Main Loader, reads config & pass to event system
 */

#include "pch.h"

#include "mods.h"
#include "codes.h"

std::wstring GamePath;
std::wstring ModManagerPath;
std::wstring ConfigPath = L"Rayman2ModLoader.ini";
std::wstring CodesPath = L"Mods\\CheatCodes.lst";
std::wstring ModsPath = L"Mods\\";

std::string DLLName = "GliVd1";
std::string APIName = "Glide2";

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

    // Attempt to get an ini location from the command line, otherwise keep default
    for (int i = 1; i < argc; i++) {
        if (!wcscmp(argv[i], L"-loaderini")) {
            ConfigPath = argv[++i];
        }
    }

    // Make path absolute if relative
    if (IsPathAbsolute(&ConfigPath) == false) {
        ConfigPath = GamePath + L"\\" + ConfigPath;
    }

    ConfigPath = ConfigPath;
    ModManagerPath = ConfigPath;
    SplitFilename(&ModManagerPath);
    ModManagerPath = ModManagerPath;
}

void InitModLoader() {
    const IniFile* config = new IniFile(ConfigPath);
    const IniGroup* loaderconfig = config->getGroup("Rayman2ModLoader");

    if (loaderconfig != nullptr) {
        DLLName = loaderconfig->getString("GlideDLL", DLLName);
        APIName = loaderconfig->getString("GlideAPI", APIName);
        ModsPath = loaderconfig->getWString("ModsPath", ModsPath);
        CodesPath = loaderconfig->getWString("CodesPath", CodesPath);

        // Init debug output system
        InitOutput(loaderconfig);

        // Check mods
        if (IsPathAbsolute(&ModsPath) == false) { ModsPath = ModManagerPath + L"\\" + ModsPath; }
        std::wstring modlist = loaderconfig->getWString("Mods", L"");

        bool loadmods = modlist.empty() == false;
        bool loadcodes = loaderconfig->getBool("LoadCodes", true);

        // Set up function hooks
        if (loadcodes || loadmods) {
            InitEvents();
        }

        // Load the Mod Manager main codes
        if (loadcodes) {
            InitCodes(&ModsPath);
        }

        // Load mods DLL and custom codes
        if (loadmods) {
            InitMods(&modlist, &ModsPath);
        }
    }
    else {
        const int type = MessageBox(nullptr, L"Cannot find the Mod Loader configuration.\n\n"
            L"Using default configuration with no mod/code enabled.",
            L"Rayman2 Mod Loader", MB_OKCANCEL | MB_ICONERROR);

        if (type != IDOK) {
            ExitProcess(1);
        }
    }
    
    delete config;
}

void LoaderInit() {
    GetGamePath();
    GetConfigPath();
    InitModLoader();
}