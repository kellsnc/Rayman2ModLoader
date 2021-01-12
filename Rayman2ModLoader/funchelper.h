#pragma once

static void SplitFilename(std::string* str) {
    std::string::size_type slash = str->find_last_of("/\\");
    *str = str->substr(0, slash);
}

static bool IsPathAbsolute(std::string* str) {
    return &str->at(1) == ":";
}

static LPCSTR* CommandLineToArgvA(LPCSTR CmdLine, int* _argc) {
    LPCSTR* argv;
    PCHAR  _argv;
    ULONG   len;
    ULONG   argc;
    CHAR   a;
    ULONG   i, j;

    BOOLEAN  in_QM;
    BOOLEAN  in_TEXT;
    BOOLEAN  in_SPACE;

    len = strlen(CmdLine);
    i = ((len + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);

    argv = (LPCSTR*)GlobalAlloc(GMEM_FIXED,
        i + (len + 2) * sizeof(CHAR));

    _argv = (PCHAR)(((PUCHAR)argv) + i);

    argc = 0;
    argv[argc] = _argv;
    in_QM = FALSE;
    in_TEXT = FALSE;
    in_SPACE = TRUE;
    i = 0;
    j = 0;

    while (a = CmdLine[i]) {
        if (in_QM) {
            if (a == '\"') {
                in_QM = FALSE;
            }
            else {
                _argv[j] = a;
                j++;
            }
        }
        else {
            switch (a) {
            case '\"':
                in_QM = TRUE;
                in_TEXT = TRUE;
                if (in_SPACE) {
                    argv[argc] = _argv + j;
                    argc++;
                }
                in_SPACE = FALSE;
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                if (in_TEXT) {
                    _argv[j] = '\0';
                    j++;
                }
                in_TEXT = FALSE;
                in_SPACE = TRUE;
                break;
            default:
                in_TEXT = TRUE;
                if (in_SPACE) {
                    argv[argc] = _argv + j;
                    argc++;
                }
                _argv[j] = a;
                j++;
                in_SPACE = FALSE;
                break;
            }
        }
        i++;
    }
    _argv[j] = '\0';
    argv[argc] = NULL;

    (*_argc) = argc;
    return argv;
}