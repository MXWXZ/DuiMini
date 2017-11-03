/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "DuiMini.h"
#include "UIRecLog.h"

namespace DuiMini {
Reclevel UIRecLog::reclevel_ = kReclevel_Debug;
UStr UIRecLog::fullpath_ = UIUtils::GetCurrentDir()
            + UIUtils::GetTimeStr(_T("\\logfile_%Y-%m-%d_%H-%M-%S.txt"));

bool UIRecLog::RecordLog(LPCTSTR text) {
    if (fullpath_.IsEmpty())
        return false;

    FILE* file;
    _tfopen_s(&file, fullpath_, _T("w"));
    if (!file)
        return false;
    _ftprintf(file, text);
    fclose(file);

    return true;
}

bool UIRecLog::RecordLog(Loglevel level, LPCTSTR text, ...) {
    LPTSTR tmpstr = NULL;
    va_list argList;
    int len;
    va_start(argList, text);
    len = _vsntprintf(NULL, 0, text, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, text, argList);
    va_end(argList);

    if (fullpath_.IsEmpty())
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
    TCHAR strtm[64];
    _tcsftime(strtm, sizeof(strtm),
              _T("%Y-%m-%d %H:%M:%S: "), localtime(&tmptm));
    strprefix += strtm;

    FILE* file;
    _tfopen_s(&file, fullpath_, _T("w"));
    if (!file)
        return false;
    _ftprintf(file, strprefix);
    _ftprintf(file, tmpstr);
    _ftprintf(file, _T("\n"));
    fclose(file);
    delete[]tmpstr;

    return true;
}

}   // namespace DuiMini
