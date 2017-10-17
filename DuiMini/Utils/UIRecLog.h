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

/**
 * Log recorder
 */
class DUIMINI_API UIRecLog {
public:
    /**
     * Set wanted log level
     * @param    Reclevel level: log level
     */
    static void SetLogLevel(Reclevel level) { reclevel_ = level; }

    /**
     * Get wanted log level
     * @return   log level
     */
    static Reclevel GetLogLevel() { return reclevel_; }

    /**
     * Record log(custom)
     * @param    LPCTSTR text: the message
     * @param    const int isexit: if is positive number,exit using this number
     *           as code,otherwise, stay running(default: -1)
     * @return   false - access file fail     true - record succeed
     * WARNING: this function WILL NOT add '\n' at the end of log
     */
    static bool RecordLog(LPCTSTR text, const int code = -1);

    /**
     * Record log(according to format)
     * @param    Loglevel level: log level
     * @param    LPCTSTR text: the message
     * @param    const int isexit: if is positive number,exit using this number
     *           as code,otherwise, stay running(default: -1)
     * @return   false - access file fail     true - record succeed
     * WARNING: this function WILL AUTOMATICALLY add '\n' at the end
     */
    static bool RecordLog(Loglevel level, LPCTSTR text, const int code = -1);

    /**
     * Set log file path
     * @param    LPCTSTR path:file path
     * if this function is not called log file will DEFAULT to logfile.txt
     */
    static void SetLogFilePath(LPCTSTR path) { logfilepath_ = path; }

    /**
     * Stop record the log
     */
    static void StopRecordLog() { logfilepath_ = _T(""); }

    /**
     * Get log file path
     * @return   log file path
     */
    static LPCTSTR GetLogFilePath() { return logfilepath_; }

protected:
    static Reclevel reclevel_;
    static UStr logfilepath_;
};

}   // namespace DuiMini
