/*
 * Rayman2 Mod Loader.
 * Read the loader's configuration to load codes/modes/events.
 */

#include "pch.h"
#include "funchelper.h"

#include "mods.h"
#include "codes.h"

// Path to the game (where this process is)
std::string GamePath;

// Path to the manager, guessed from the config path.
std::string ModManagerPath; 

// Path to the loader's configuration, can be moved with the "-loaderini" command (not recommended.)
std::string ConfigPath = "Rayman2ModLoader.ini";

// Path to "mods" folder (containing cheat codes and mods.)
// Can be moved in the loader's configuration (not recommended.)
std::string ModsPath = "Mods\\";

std::string DLLName = "GliVd1"; // Original DLL Name, read from the loader's configuration.
std::string APIName = "Glide2"; // Original API Name, read from the loader's configuration.

// Warns the user about the executable being wrong and exits.
static void WrongExe() {
    MessageBoxA(nullptr, "This copy of Rayman 2 is not the correct version.\n\n"
        "Please obtain the EXE file from GoG or from the original European release.",
        "Rayman2 Mod Loader", MB_ICONERROR);

    ExitProcess(1);
}

// This removes the write protection from the rdata section.
// Mods will be able to edit the pure data contained in this section.
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

// Get the game's path.
void GetGamePath() {
    char pathbuf[MAX_PATH];
    GetModuleFileNameA(nullptr, pathbuf, MAX_PATH);

    GamePath = pathbuf;
    SplitFilename(&GamePath);
}

// Get the loader's configuration path and guess the manager's location from that.
void GetConfigPath() {
    int argc;
    LPCSTR* argv = CommandLineToArgvA(GetCommandLineA(), &argc);

    // Attempt to get an ini location from the command line, otherwise keep default
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-loaderini")) {
            ConfigPath = argv[++i];
        }
    }

    // Make path absolute if relative
    if (IsPathAbsolute(&ConfigPath) == false) {
        ConfigPath = GamePath + "\\" + ConfigPath;
    }

    // Guess mod manager path
    ModManagerPath = ConfigPath;
    SplitFilename(&ModManagerPath);
}

// Read the configuration and initialize everything accordingly.
void InitModLoader() {
    const IniFile* config = new IniFile(ConfigPath);
    const IniGroup* loaderconfig = config->getGroup("");

    if (loaderconfig != nullptr) {
        DLLName = loaderconfig->getString("DllName", DLLName); // Original DLL name.
        APIName = loaderconfig->getString("APIName", APIName); // Original API name.
        ModsPath = loaderconfig->getString("ModsPath", ModsPath); // Path to the "mods" folder.

        // Init debug output system
        InitOutput(loaderconfig);

        // Mods and cheat codes can edit read-only memory
        SetRDataWriteProtection(false);

        // If the "mods" folder path is relative, make it absolute
        if (IsPathAbsolute(&ModsPath) == false) { 
            ModsPath = ModManagerPath + "\\" + ModsPath; 
        }

        bool loadmods = loaderconfig->hasKey("Mod1"); // At least one mod is enabled.
        bool loadcodes = loaderconfig->hasKey("Code1"); // At least one code is enabled.

        // If at least one code or one mod is enabled, hook into the game's functions
        if (loadcodes || loadmods) {
            InitEvents();
        }

        // Load cheat codes
        if (loadcodes) {
            InitCodes(&ModsPath);
        }
        else {
            PrintDebug("[ModLoader] Loaded 0 codes\n");
        }

        // Load mods
        if (loadmods) {
            InitMods(loaderconfig, &ModsPath);
        }
        else {
            PrintDebug("[ModLoader] Loaded 0 mod\n");
        }

        // Init the CNT archive replacement
        TexturesInit();
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