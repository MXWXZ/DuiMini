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
#include "UIRecLog.h"

namespace DuiMini {
Reclevel UIRecLog::record_level_ = kDebug;
UStr UIRecLog::fullpath_ = UIUtils::GetCurrentDir() + UIUtils::GetTimeStr(_T("\\logfile_%Y-%m-%d_%H-%M-%S.txt"));

Reclevel UIRecLog::SetLogLevel(Reclevel v_record_level) {
    record_level_ = v_record_level;
    return record_level_;
}

Reclevel UIRecLog::GetLogLevel() {
    return record_level_;
}

bool UIRecLog::RecordLog(LPCTSTR v_text) {
    if (fullpath_.IsEmpty())
        return false;

    FILE* file;
    _tfopen_s(&file, fullpath_, _T("w"));
    if (!file)
        return false;
    _ftprintf(file, v_text);
    fclose(file);

    return true;
}

bool UIRecLog::RecordLog(Loglevel v_level, LPCTSTR v_text, ...) {
    LPTSTR tmpstr = nullptr;
    va_list argList;
    int len = 0;

    va_start(argList, v_text);
    len = _vsntprintf(NULL, 0, v_text, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, v_text, argList);
    va_end(argList);

    if (fullpath_.IsEmpty())
        return false;
    if (v_level < record_level_)
        return true;

    UStr strprefix;
    switch (v_level) {
    case kInfo:
        strprefix = _T("[Info]");
        break;
    case kWarning:
        strprefix = _T("[Warning]");
        break;
    case kError:
        strprefix = _T("[Error]");
        break;
    }
    strprefix += UIUtils::GetTimeStr(_T("%Y-%m-%d %H:%M:%S: "));

    FILE* file;
    _tfopen_s(&file, fullpath_, _T("w"));
    if (!file)
        return false;
    _ftprintf(file, strprefix);
    _ftprintf(file, tmpstr);
    _ftprintf(file, _T("\n"));
    fclose(file);
    delete[]tmpstr;
    tmpstr = nullptr;

    return true;
}

LPCTSTR UIRecLog::SetLogFilePath(LPCTSTR v_fullpath) {
    fullpath_ = v_fullpath;
    return fullpath_;
}

LPCTSTR UIRecLog::GetLogFilePath() {
    return fullpath_;
}

void UIRecLog::StopRecordLog() {
    fullpath_.Empty();
}

}   // namespace DuiMini
