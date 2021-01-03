// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <ShellAPI.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "include/Rayman2ModLoader.h"
#include "IniFile.hpp"
#include "CodeParser.hpp"
#include "TextConv.hpp"
#include "FileSystem.h"

#include "Trampoline.h"
#include "FileMap.hpp"

#include "output.h"
#include "loader.h"
#include "events.h"
#include "replacefiles.h"
#include "modhelpers.h"

#endif //PCH_H
