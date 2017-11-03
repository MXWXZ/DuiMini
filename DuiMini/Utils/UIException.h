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
    kErrorCode_Success = 0,

    kErrorCode_Fatal,       // greater than this will quit the program

    kErrorCode_FileFail,

    kErrorCode_LogFileFail,
};

class DUIMINI_API UIException {
public:
    static void SetError(Loglevel level, ErrorCode code, LPCTSTR msg, ...);
    static ErrorCode GetLastError() { return errorcode_; }
    static void HandleError();

private:
    static Loglevel errorloglevel_;
    static ErrorCode errorcode_;
    static UStr errormsg_;
};
#define HandleError UIException::HandleError
}  // namespace DuiMini
