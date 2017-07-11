/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UISystem.h"

namespace DuiMini {
/************************************************************************
Initialize static member
************************************************************************/
HINSTANCE UISystem::instance_;

/************************************************************************
Initialize DuiMini library
************************************************************************/
void UISystem::Init(HINSTANCE inst) {
    _tsetlocale(LC_ALL, _T(""));
    SetInstance(inst);
}

/************************************************************************
Clean up(DO NOT EXIT)
************************************************************************/
void UISystem::Cleanup() {
}

/************************************************************************
Safely exit the program
const int code: exit code(default:0)
************************************************************************/
void UISystem::Exit(const int code /*= 0*/) {
    Cleanup();
    exit(code);
}

/************************************************************************
Get the current path,WITHOUT THE \\ AT THE END
e.g:c:\\windows\\system32
************************************************************************/
LPCTSTR UISystem::GetCurrentDir() {
    TCHAR path[MAX_PATH] = { _T('\0') };
    GetCurrentDirectory(MAX_PATH, path);
    UStr ret = path;
    return ret;
}

}   // namespace DuiMini
