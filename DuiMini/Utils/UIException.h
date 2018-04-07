/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
/**
 * kEL_Normal: no error occured
 * kEL_Warning: something goes wrong, but program can still running
 * kEL_Error: key function goes wrong, program may still running but will be
 *            affect.
 * kEL_Fatal: Fatal error, program will be exit automatically
 */
enum ErrorLevel {
    kEL_Normal = 0,
    kEL_Warning,
    kEL_Error,
    kEL_Fatal
};

enum ErrorCode {
    kEC_Success=0,
    kEC_FileFail,
    kEC_WindowsFail,
    kEC_ThirdPartFail,
    kEC_IDInvalid,
    kEC_FormatInvalid,
    // Add error code here

    kEC_Codecnt     // do NOT modify this
};

#define ErrorMsg_FileFail(file) _T("File \"%s\" can't access!"), file
#define ErrorMsg_IDInvalid(id) _T("ID %s is invalid!"), id
#define ErrorMsg_ThirdPartFail(func) _T("Thirdpart function %s failed!"), #func

#define UISetError(level, code, v_msg, ...) UIException::SetError(level,code,\
                                                __FUNCTION__,__LINE__,\
                                                v_msg, ##__VA_ARGS__)
#define UIGetLastError UIException::GetLastError
#define UIGetLastErrorMsg UIException::GetLastErrorMsg

typedef bool(*ExtraHandleFun)(ErrorLevel v_level, ErrorCode v_code,
                              UStr v_error_msg);

class DUIMINI_API UIException {
public:
    static void SetError(ErrorLevel v_level, ErrorCode v_code,
                         LPCSTR v_func, int v_line, LPCTSTR v_msg, ...);

    static ErrorCode GetLastError();
    static CUStr GetLastErrorMsg();
    static void SetExtraHandleFun(ExtraHandleFun v_extra_fun);

private:
    static ErrorCode error_code_;
    static UStr error_msg_;
    static ExtraHandleFun extra_fun_;
};
}  // namespace DuiMini
