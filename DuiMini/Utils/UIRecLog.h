/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:Log file recorder class
 */
#pragma once

namespace DuiMini {
/**
 * Loglevel definition
 * kLoglevel_Info:some information(will NOT affect the program)
 * kLoglevel_Warning:some warning(NOT fatal error)
 * kLoglevel_Error:fatal error(usually cause exit)
 */
enum Loglevel {
    kLoglevel_Info = 0,
    kLoglevel_Warning = 1,
    kLoglevel_Error = 2,
};

/**
 * log level wanted to record
 * kReclevel_Debug:record all logs
 * kReclevel_Beta:ignore kLoglevel_Info logs
 * kReclevel_Release:record ONLY kLoglevel_Error logs
 */
enum Reclevel {
    kReclevel_Debug = 0,
    kReclevel_Beta = 1,
    kReclevel_Release = 2,
};

class DUIMINI_API UIRecLog {
public:
    static void SetLogLevel(Reclevel level) { reclevel_ = level; }
    static Reclevel GetLogLevel() { return reclevel_; }

    /**
     * Record log(custom)
     * @param    LPCTSTR text: the message
     * @return   true - record succeed
     * WARNING: this function WILL NOT add '\n' at the end of log
     */
    static bool RecordLog(LPCTSTR text);

    /**
     * Record log(according to format)
     * @param    Loglevel level: log level
     * @param    LPCTSTR text: the message
     * @return   true - record succeed
     * WARNING: this function WILL AUTOMATICALLY add '\n' at the end
     */
    static bool RecordLog(Loglevel level, LPCTSTR text, ...);

    static void SetLogFilePath(LPCTSTR path) { fullpath_ = path; }
    static LPCTSTR GetLogFilePath() { return fullpath_; }
    static void StopRecordLog() { fullpath_ = _T(""); }

private:
    static Reclevel reclevel_;
    static UStr fullpath_;
};

}   // namespace DuiMini
