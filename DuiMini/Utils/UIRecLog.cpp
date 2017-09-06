// ****************************************
// Copyright (c) 2017-2050
// All rights reserved.
//
// Author:MXWXZ
// Date:2017/09/05
//
// Description:
// ****************************************
#include "stdafx.h"
#include "DuiMini.h"
#include "UIRecLog.h"

namespace DuiMini {
// Initialize static member
Reclevel UIRecLog::reclevel_ = kReclevel_Debug;
UStr UIRecLog::logfilepath_ = UISystem::GetCurrentDir() + _T("\\logfile.txt");

bool UIRecLog::RecordLog(LPCTSTR text, const int code /*= -1*/) {
    if (logfilepath_.IsEmpty())
        return false;

    FILE* file;
    _tfopen_s(&file, logfilepath_, _T("a+"));
    if (!file)
        return false;
    _ftprintf(file, text);
    fclose(file);

    if (code >= 0)
        UISystem::Exit(code);
    return true;
}

bool UIRecLog::RecordLog(Loglevel level, LPCTSTR text,
                         const int code /*= -1*/) {
    if (logfilepath_.IsEmpty())
        return false;
    if (level < reclevel_)
        return true;

    UStr strprefix;
    switch (level) {
        case kLoglevel_Info:
            strprefix = _T("[Info]");
            break;
        case kLoglevel_Warning:
            strprefix = _T("[Warning]");
            break;
        case kLoglevel_Error:
            strprefix = _T("[Error]");
            break;
    }
    time_t tmptm;
    time(&tmptm);
    TCHAR strtmp[64];
    _tcsftime(strtmp, sizeof(strtmp),
              _T("%Y-%m-%d %H:%M:%S: "), localtime(&tmptm));
    strprefix += strtmp;
    FILE* file;
    _tfopen_s(&file, logfilepath_, _T("a+"));
    if (!file)
        return false;
    _ftprintf(file, strprefix);
    _ftprintf(file, text);
    _ftprintf(file, _T("\n"));
    fclose(file);
    if (code >= 0)
        UISystem::Exit(code);
    return true;
}

}   // namespace DuiMini
