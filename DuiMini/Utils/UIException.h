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
enum ErrorCode {
    kSuccess = 0,
    kIDInvalid,
    kCtrlKindInvalid,
    kRegWndFailed,

    kFatalError,       // greater than this will quit the program

    kFileFail,

    kLogFileFail,     // keep this value at the end
};

typedef bool(*ExtraHandleFun)(Loglevel v_log_level,
                              ErrorCode v_error_code,
                              UStr v_error_msg);

class DUIMINI_API UIException {
public:
    static void SetError(Loglevel v_log_level, ErrorCode v_error_code,
                         LPCTSTR v_error_msg, ...);
    static void HandleError();
    static void HandleError(Loglevel v_log_level, ErrorCode v_error_code,
                            LPCTSTR v_error_msg, ...);

    static ErrorCode GetLastError();
    static void SetExtraHandleFun(ExtraHandleFun v_extra_fun);

private:
    static Loglevel log_level_;
    static ErrorCode error_code_;
    static UStr error_msg_;
    static ExtraHandleFun extra_fun_;
};

#define UIHandleError UIException::HandleError
#define UISetError UIException::SetError
#define UIGetLastError UIException::GetLastError
}  // namespace DuiMini
