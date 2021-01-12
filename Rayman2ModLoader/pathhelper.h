#pragma once

static void SplitFilename(std::wstring* str) {
    std::string::size_type slash = str->find_last_of(L"/\\");
    *str = str->substr(0, slash);
}

static bool IsPathAbsolute(std::wstring* str) {
    return &str->at(1) == L":";
}