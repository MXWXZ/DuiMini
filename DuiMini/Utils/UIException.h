/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
enum ErrorLevel {
    kEL_Normal = 0,     // no error occured
    kEL_Warning,        // something goes wrong, but program can still running
    kEL_Error           // key function goes wrong, program will exit
};

enum ErrorCode {
    kEC_Success = 0,    // No error
    kEC_FileFail,       // file access error
    kEC_ThirdPartFail,  // third-part error
    kEC_IDInvalid,      // id invalid
    kEC_FormatInvalid,  // format invalid
    // Add error code here

    kEC_Codecnt     // do NOT modify this
};

#define ErrorMsg_FileFail(file)         UISetError(kEL_Error, kEC_FileFail, _T("File \"%s\" can't access!"), file)
#define ErrorMsg_ThirdPartFail(func)    UISetError(kEL_Error, kEC_ThirdPartFail, _T("Thirdpart function \"%s\" failed!"), #func)
#define ErrorMsg_IDInvalid(id)          UISetError(kEL_Warning, kEC_IDInvalid, _T("ID \"%s\" is invalid!"), id)
#define ErrorMsg_FormatInvalid(txt)     UISetError(kEL_Warning, kEC_FormatInvalid, _T("Format error when parsing \"%s\"!"), txt)

#define UISetError(level, code, msg, ...) UIException::SetError(level,code,\
                                                __FUNCTION__,__LINE__,\
                                                msg, ##__VA_ARGS__)
#define UIGetLastError      UIException::GetLastError
#define UIGetLastErrorMsg   UIException::GetLastErrorMsg

/**
 * Extra exception handle function format
 * @param	ErrorLevel v_level: error level
 * @param   ErrorCode v_code: error code
 * @param   UStr v_msg: error msg
 * @return	true for ignoring default handle
 */
typedef std::function<bool(ErrorLevel v_level, ErrorCode v_code, UStr v_msg)> ExtraFunc;

class DUIMINI_API UIException {
public:
    /**
     * Set last error
     * @param	ErrorLevel v_level: error level
     * @param   ErrorCode v_code: error code
     * @param   LPCSTR v_func: error function name
     * @param   int v_line: error line
     * @param   LPCTSTR v_msg: error msg (format support)
     */
    static void SetError(ErrorLevel v_level, ErrorCode v_code,
                         LPCSTR v_func, int v_line, LPCTSTR v_msg, ...);

    static ErrorCode GetLastError() { return error_code_; }
    static CUStr GetLastErrorMsg()  { return error_msg_; }
    static void SetExtraFunc(ExtraFunc v_extra_fun) { extra_fun_ = v_extra_fun; }

private:
    static ErrorCode error_code_;
    static UStr error_msg_;
    static ExtraFunc extra_fun_;
};
}  // namespace DuiMini
