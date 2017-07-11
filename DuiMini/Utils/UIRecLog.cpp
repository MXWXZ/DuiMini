/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIRecLog.h"

namespace DuiMini {
/************************************************************************
Initialize static member
************************************************************************/
Reclevel UIRecLog::reclevel_ = kReclevel_Debug;
UStr UIRecLog::logfilepath_ = UStr(UISystem::GetCurrentDir())
                                + _T("\\logfile.txt");

/************************************************************************
Record log(custom)
LPCTSTR text: the message
const int isexit: if is positive number,exit using this number as code
                  otherwise,stay running(default: -1)
ret value: false - access file fail
           true - record succeed
WARNING: this function WILL NOT add '\n' at the end
************************************************************************/
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

/************************************************************************
Record log(according to format)
Loglevel level: log level
                kLoglevel_Info    - information of program
                kLoglevel_Warning - warning(not fatal)
                kLoglevel_Error   - error(fatal,usually exit)
LPCTSTR text: the message
const int isexit: if is positive number,exit using this number as code
                  otherwise,stay running(default: -1)
ret value: false - access file fail
           true - record succeed
WARNING: this function WILL AUTOMATICALLY add '\n' at the end
************************************************************************/
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
    time_t tm;
    time(&tm);
    TCHAR strtmp[64];
    _tcsftime(strtmp, sizeof(strtmp),
              _T("%Y-%m-%d %H:%M:%S: "), localtime(&tm));
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
