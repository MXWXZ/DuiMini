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
ErrorCode UIException::error_code_ = kEC_Success;
UStr      UIException::error_msg_ = _T("");
LogLevel  UIException::log_level_ = kLL_Info;
ExtraHandleFun UIException::extra_fun_ = nullptr;

void UIException::SetError(LogLevel v_log_level, ErrorCode v_error_code,
                           LPCTSTR v_error_msg, ...) {
    LPTSTR tmpstr = nullptr;
    va_list argList;
    int len = 0;

    va_start(argList, v_error_msg);
    len = _vsntprintf(NULL, 0, v_error_msg, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, v_error_msg, argList);
    va_end(argList);

    error_msg_ = tmpstr;
    log_level_ = v_log_level;
    error_code_ = v_error_code;

    delete[]tmpstr;
    tmpstr = nullptr;
}

ErrorCode UIException::GetLastError() {
    return error_code_;
}

void UIException::HandleError() {
    if (error_code_ == kEC_Success)
        return;

    bool ishandled = false;
    if (extra_fun_)
        ishandled = extra_fun_(log_level_, error_code_, error_msg_);
    if (!ishandled) {
        if (!UIRecLog::RecordLog(log_level_,
                                 UStr(_T("Code %d ")) + error_msg_,
                                 error_code_)) {
            MessageBox(NULL, _T("Log record failed!"), _T("ERROR"), MB_OK);
            error_code_ = kEC_LogFileFail;
        }
        if (error_code_ >= kEC_FatalError_)
            UISystem::Exit(error_code_);
    }
    error_code_ = kEC_Success;
    error_msg_.Empty();
}

void UIException::HandleError(LogLevel v_log_level, ErrorCode v_error_code,
                              LPCTSTR v_error_msg, ...) {
    // Oh I dont know how to pass ... to SetError function so that is it.
    LPTSTR tmpstr = nullptr;
    va_list argList;
    int len = 0;

    va_start(argList, v_error_msg);
    len = _vsntprintf(NULL, 0, v_error_msg, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, v_error_msg, argList);
    va_end(argList);

    error_msg_ = tmpstr;
    log_level_ = v_log_level;
    error_code_ = v_error_code;

    delete[]tmpstr;
    tmpstr = nullptr;

    HandleError();
}

void UIException::SetExtraHandleFun(ExtraHandleFun v_extra_fun) {
    extra_fun_ = v_extra_fun;
}

}  // namespace DuiMini

