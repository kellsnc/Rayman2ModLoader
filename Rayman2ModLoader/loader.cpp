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
std::wstring ModsPath = L"Mods\\";

std::string DLLName = "GliVd1";
std::string APIName = "Glide2";

static void WrongExe() {
    MessageBox(nullptr, L"This copy of Rayman 2 is not the correct version.\n\n"
        L"Please obtain the EXE file from GoG or from the original European release.",
        L"Rayman2 Mod Loader", MB_ICONERROR);

    ExitProcess(1);
}

static void SetRDataWriteProtection(bool protect) {
    // Reference: https://stackoverflow.com/questions/22588151/how-to-find-data-segment-and-code-segment-range-in-program
    
    HMODULE hModule = GetModuleHandle(nullptr);

    // Get the PE header.
    const IMAGE_NT_HEADERS* const pNtHdr = ImageNtHeader(hModule);

    // Section headers are located immediately after the PE header.
    const auto* pSectionHdr = reinterpret_cast<const IMAGE_SECTION_HEADER*>(pNtHdr + 1);

    // Find the .rdata section.
    for (unsigned int i = pNtHdr->FileHeader.NumberOfSections; i > 0; i--, pSectionHdr++) {
        if (strncmp(reinterpret_cast<const char*>(pSectionHdr->Name), ".rdata", sizeof(pSectionHdr->Name)) != 0) {
            continue;
        }

        // Found the .rdata section.
        if (pSectionHdr->VirtualAddress != 0x9C000 || pSectionHdr->Misc.VirtualSize != 0x3000) {
            WrongExe();
        }

        const intptr_t vaddr = reinterpret_cast<intptr_t>(hModule) + pSectionHdr->VirtualAddress;
        DWORD flOldProtect;
        DWORD flNewProtect = (protect ? PAGE_READONLY : PAGE_WRITECOPY);
        VirtualProtect(reinterpret_cast<void*>(vaddr), pSectionHdr->Misc.VirtualSize, flNewProtect, &flOldProtect);

        return;
    }

    // .rdata section not found.
    WrongExe();
}

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
    const IniGroup* loaderconfig = config->getGroup("");

    if (loaderconfig != nullptr) {
        DLLName = loaderconfig->getString("GlideDLL", DLLName);
        APIName = loaderconfig->getString("GlideAPI", APIName);
        ModsPath = loaderconfig->getWString("ModsPath", ModsPath);

        // Init debug output system
        InitOutput(loaderconfig);

        // Mods and cheat codes can edit read-only memory
        SetRDataWriteProtection(false);

        if (IsPathAbsolute(&ModsPath) == false) { ModsPath = ModManagerPath + L"\\" + ModsPath; }

        bool loadmods = loaderconfig->hasKey("Mod1");
        bool loadcodes = loaderconfig->hasKey("Code1");

        // Set up function hooks
        if (loadcodes || loadmods) {
            InitEvents();
        }

        // Load the Mod Manager main codes
        if (loadcodes) {
            InitCodes(&ModsPath);
        }
        else {
            PrintDebug("[ModLoader] Loaded 0 codes\n");
        }

        // Load mods DLL and custom codes
        if (loadmods) {
            InitMods(loaderconfig, &ModsPath);
        }
        else {
            PrintDebug("[ModLoader] Loaded 0 mod\n");
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