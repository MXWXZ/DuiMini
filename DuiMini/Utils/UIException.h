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
    kErrorCode_FileFormat,

    kErrorCode_LogFileFail,
};

typedef bool(*ExtraHandleFun)(Loglevel errorloglevel,
                                          ErrorCode errorcode,
                                          UStr errormsg);

class DUIMINI_API UIException {
public:
    static void SetError(Loglevel level, ErrorCode code, LPCTSTR msg, ...);
    static ErrorCode GetLastError() { return errorcode_; }
    static void SetExtraHandleFun(ExtraHandleFun fun);
    static void HandleError();

private:
    static Loglevel errorloglevel_;
    static ErrorCode errorcode_;
    static UStr errormsg_;
    static ExtraHandleFun fun_;
};
#define HandleError UIException::HandleError
}  // namespace DuiMini
