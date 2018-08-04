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
UStr        UIException::error_msg_ = _T("");
ErrorCode   UIException::error_code_ = kEC_Success;
ExtraFunc   UIException::extra_fun_ = nullptr;

void UIException::SetError(ErrorLevel v_level, ErrorCode v_code,
                           LPCSTR v_func, int v_line, LPCTSTR v_msg, ...) {
    if (v_level == kEL_Normal || v_code == kEC_Success)
        return;
    va_list argList;
    va_start(argList, v_msg);
    int len = _vsntprintf(NULL, 0, v_msg, argList);
    auto tmpstr = UIUtils::SafeTStr(len + 1);
    _vsntprintf(tmpstr.get(), len + 1, v_msg, argList);
    va_end(argList);
    
    error_msg_ = tmpstr.get();
    UStr prefix;
    switch (v_level) {
    case kEL_Warning:
        prefix = _T("Warning!");
        break;
    case kEL_Error:
        prefix = _T("Error!");
        break;
    }
    auto func = UIUtils::Convert2TStr(v_func);
    error_msg_.Format(_T("%s - Code:%d %s\n[In function:\"%s\" line:%d]"),
                      prefix.GetData(), v_code, error_msg_.GetData(),
                      func.get(), v_line);
    error_code_ = v_code;

    OutputDebugString((error_msg_ + _T("\n")).GetData());
#ifdef DEBUG
    __debugbreak();
#endif // DEBUG
    bool ishandled = false;
    if (extra_fun_)
        ishandled = extra_fun_(v_level, v_code, error_msg_);
    if (!ishandled && v_level == kEL_Error)
        UISystem::Exit(v_code);
}

}  // namespace DuiMini

