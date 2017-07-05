/************************************************************************
Copyright (c) 2017 MXWXZ
UI库日志记录类
************************************************************************/
#pragma once
#ifndef E__CODE_DUIMINI_DUIMINI_UTILS_UIRECLOG_H_
#define E__CODE_DUIMINI_DUIMINI_UTILS_UIRECLOG_H_

namespace DuiMini {
enum Loglevel {
    kLoglevel_Info = 0,
    kLoglevel_Warning = 1,
    kLoglevel_Error = 2,
};
enum Reclevel {
    kReclevel_Debug = 0,
    kReclevel_Beta = 1,
    kReclevel_Release = 2,
};

class DUIMINI_API UIRecLog {
 public:
    static void SetLogLevel(Reclevel level) { reclevel_ = level; }
    static Reclevel GetLogLevel() { return reclevel_; }
    static bool RecordLog(LPCTSTR text, const int code = -1);
    static bool RecordLog(Loglevel level, LPCTSTR text, const int code = -1);
    static void SetLogFilePath(LPCTSTR path) { logfilepath_ = path; }
    static void StopRecordLog() { logfilepath_ = _T(""); }
    static LPCTSTR GetLogFilePath() { return logfilepath_; }

 protected:
    static Reclevel reclevel_;        // 日志文件记录级别
    static UStr logfilepath_;         // 日志文件路径
};

}   // namespace DuiMini

#endif  // E__CODE_DUIMINI_DUIMINI_UTILS_UIRECLOG_H_
