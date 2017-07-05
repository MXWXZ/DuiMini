/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIRecLog.h"

namespace DuiMini {
/************************************************************************
静态成员初始化
************************************************************************/
Reclevel UIRecLog::reclevel_ = kReclevel_Debug;
UStr UIRecLog::logfilepath_ = UStr(UISystem::GetCurrentDir())
                                + _T("\\logfile.txt");

/************************************************************************
记录日志（自定义）
LPCTSTR text：记录信息
const int isexit：非负值则以此为退出值退出程序，否则不退出 默认-1
返回值：false 文件访问失败 true 记录成功
注：函数不在末尾添加回车
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
记录日志（按格式）
Loglevel level：日志级别
                kLoglevel_Info为信息
                kLoglevel_Warning为警告
                kLoglevel_Error为错误
LPCTSTR text：记录信息
const int isexit：非负值则以此为退出值退出程序，否则不退出 默认-1
返回值：false 文件访问失败 true 记录成功
注：函数会自动在末尾添加回车
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
