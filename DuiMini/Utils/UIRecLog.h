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
 * Loglevel definition
 * kInfo:some information(will NOT affect the program)
 * kWarning:some warning(NOT fatal error)
 * kError:fatal error(usually cause exit)
 */
enum Loglevel {
    kInfo = 0,
    kWarning = 1,
    kError = 2,
};

/**
 * log level wanted to record
 * kDebug:record all logs
 * kBeta:ignore kLoglevel_Info logs
 * kRelease:record ONLY kLoglevel_Error logs
 */
enum Reclevel {
    kDebug = 0,
    kBeta = 1,
    kRelease = 2,
};

class DUIMINI_API UIRecLog {
public:
    static void SetLogLevel(Reclevel v_record_level);
    static Reclevel GetLogLevel();

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
    static bool RecordLog(Loglevel v_level, LPCTSTR v_text, ...);

private:
    static Reclevel record_level_;
    static UStr fullpath_;
};

}   // namespace DuiMini
