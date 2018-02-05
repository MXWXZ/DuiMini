/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:exception handle
 */
#pragma once

namespace DuiMini {
#define UIHandleError UIException::HandleError
#define UISetError UIException::SetError
#define UIGetLastError UIException::GetLastError

enum ErrorCode {
    kEC_Success = 0,
    kEC_IDInvalid,
    kEC_CtrlKindInvalid,
    kEC_CtrlFormatInvalid,
    kEC_RegWndFailed,
    kEC_ThirdPartFail,

    kEC_FatalError_,      // greater than this will quit the program

    kEC_FileFail,

    kEC_LogFileFail,     // keep this value at the end
};

typedef bool(*ExtraHandleFun)(LogLevel v_log_level,
                              ErrorCode v_error_code,
                              UStr v_error_msg);

class DUIMINI_API UIException {
public:
    static void SetError(LogLevel v_log_level, ErrorCode v_error_code,
                         LPCTSTR v_error_msg, ...);
    static void HandleError();
    static void HandleError(LogLevel v_log_level, ErrorCode v_error_code,
                            LPCTSTR v_error_msg, ...);

    static ErrorCode GetLastError();
    static void SetExtraHandleFun(ExtraHandleFun v_extra_fun);

private:
    static LogLevel log_level_;
    static ErrorCode error_code_;
    static UStr error_msg_;
    static ExtraHandleFun extra_fun_;
};
}  // namespace DuiMini
