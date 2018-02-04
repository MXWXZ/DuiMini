/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:Log file recorder
 */
#pragma once

namespace DuiMini {
/**
 * LogLevel definition
 * kLL_Info:some information(will NOT affect the program)
 * kLL_Warning:some warning(NOT fatal error)
 * kLL_Error:fatal error(usually cause exit)
 */
enum LogLevel {
    kLL_Info = 0,
    kLL_Warning = 1,
    kLL_Error = 2,
};

/**
 * log level wanted to record
 * kRL_Debug:record all logs
 * kRL_Beta:ignore kLoglevel_Info logs
 * kRL_Release:record ONLY kLoglevel_Error logs
 */
enum RecLevel {
    kRL_Debug = 0,
    kRL_Beta = 1,
    kRL_Release = 2,
};

class DUIMINI_API UIRecLog {
public:
    static void SetLogLevel(RecLevel v_record_level);
    static RecLevel GetLogLevel();

    static void SetLogFilePath(LPCTSTR v_fullpath);
    static CUStr GetLogFilePath();

    static void StopRecordLog();

    /**
     * Record log(custom)
     * WARNING: this function will NOT add '\n' at the end of log
     */
    static bool RecordLog(LPCTSTR v_text);

    /**
     * Record log(according to format)
     * WARNING: this function WILL AUTOMATICALLY add '\n' at the end
     */
    static bool RecordLog(LogLevel v_level, LPCTSTR v_text, ...);

private:
    static RecLevel record_level_;
    static UStr fullpath_;
};

}   // namespace DuiMini
