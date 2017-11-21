/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:
 */
#include "stdafx.h"
#include "DuiMini.h"
#include "UIException.h"

namespace DuiMini {
ErrorCode UIException::errorcode_ = kErrorCode_Success;
UStr UIException::errormsg_ = _T("");
Loglevel UIException::errorloglevel_ = kLoglevel_Info;
ExtraHandleFun UIException::fun_ = NULL;

void UIException::SetError(Loglevel level, ErrorCode code, LPCTSTR msg, ...) {
    LPTSTR tmpstr = NULL;
    va_list argList;
    int len;
    va_start(argList, msg);
    len = _vsntprintf(NULL, 0, msg, argList);
    tmpstr = new TCHAR[len + 1];
    _vsntprintf(tmpstr, len + 1, msg, argList);
    va_end(argList);

    errormsg_ = tmpstr;
    errorloglevel_ = level;
    errorcode_ = code;

    delete[]tmpstr;
}

void UIException::HandleError() {
    if (errorcode_ == kErrorCode_Success)
        return;
    
    bool ishandled = false;
    if (fun_ != NULL)
        ishandled = fun_(errorloglevel_, errorcode_, errormsg_);
    if (!ishandled) {
        if (!UIRecLog::RecordLog(errorloglevel_,
                                 UStr(_T("Code %d ")) + errormsg_, errorcode_)) {
            MessageBox(NULL, _T("Log record failed!"), _T("ERROR"), MB_OK);
            errorcode_ = kErrorCode_LogFileFail;
        }
        if (errorcode_ >= kErrorCode_Fatal)
            UISystem::Exit(errorcode_);
    }
    errorcode_ = kErrorCode_Success;
    errormsg_.Empty();
}

void UIException::SetExtraHandleFun(ExtraHandleFun fun) {
    fun_ = fun;
}

}  // namespace DuiMini

