/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIException.h"

namespace DuiMini {
UStr      UIException::error_msg_ = _T("");
ErrorCode  UIException::error_code_ = kEC_Success;
ExtraHandleFun UIException::extra_fun_ = nullptr;

void UIException::SetError(ErrorLevel v_level, ErrorCode v_code,
                           LPCSTR v_func, int v_line, LPCTSTR v_msg, ...) {
    if (v_level == kEL_Normal || v_code == kEC_Success)
        return;
    LPTSTR tmpstr = nullptr;
    va_list argList;
    int len = 0;
    va_start(argList, v_msg);
    len = _vsntprintf(NULL, 0, v_msg, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, v_msg, argList);
    va_end(argList);

    error_msg_ = tmpstr;
    UStr prefix;
    switch (v_level) {
    case kEL_Warning:
        prefix = _T("Warning!");
        break;
    case kEL_Error:
        prefix = _T("Error!");
        break;
    case kEL_Fatal:
        prefix = _T("Fatal Error!");
        break;
    }
#ifdef _UNICODE
    int funclen = GetStr2WStrLen(v_func);
    LPWSTR func = new wchar_t[funclen];
    Str2WStr(v_func, func, funclen);
#else
    LPSTR func = v_func;
#endif // _UNICODE
    error_msg_.Format(_T("%s - Code:%d %s\n[In function:\"%s\" line:%d]"),
                      prefix.GetData(), v_code, error_msg_.GetData(), func, v_line);
    error_code_ = v_code;

    OutputDebugString((error_msg_ + _T("\n")).GetData());
    bool ishandled = false;
    if (extra_fun_)
        ishandled = extra_fun_(v_level, v_code, error_msg_);
    if (!ishandled && v_level == kEL_Fatal)
        UISystem::Exit(v_code);

#ifdef _UNICODE
    delete[]func;
#endif // _UNICODE
    delete[]tmpstr;
    tmpstr = nullptr;
}

ErrorCode UIException::GetLastError() {
    return error_code_;
}

CUStr UIException::GetLastErrorMsg() {
    return error_msg_;
}

void UIException::SetExtraHandleFun(ExtraHandleFun v_extra_fun) {
    extra_fun_ = v_extra_fun;
}

}  // namespace DuiMini

