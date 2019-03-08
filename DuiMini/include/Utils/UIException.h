/** @file
 * UI exception class.
 * Offer the method to solve exception.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_UTILS_UIEXCEPTION_H_
#define DUI_UTILS_UIEXCEPTION_H_

#include "UIDefine.h"
#include "UIUtils.h"

#include <functional>
#include <vector>

namespace DuiMini {
#define UISetError(level, msg, ...) \
    UIException::SetError(level, __FUNCTION__, __LINE__, msg, ##__VA_ARGS__)
#define UIGetErrorMsgList UIException::GetErrorMsgList

/**
 * Exception level.
 */
enum ErrorLevel {
    kEL_Normal = 0,  //!< no error occured
    kEL_Warning,     //!< something goes wrong, but program can still running
    kEL_Error  //!< key function goes wrong, no safe guarantee, program will
               //!< exit
};

/**
 * Extra exception handle function format.
 * @param   level: error level
 * @param   msg: error msg
 * @return	true for ignoring default handle
 */
typedef std::function<bool(int level, const char* msg)> ExtraFunc;

class DUIMINI_API UIException {
public:
    /**
     * Set last error.
     * @param	level: error level
     * @param   func: error function name
     * @param   line: error line
     * @param   msg: error msg (format support)
     */
    static void SetError(ErrorLevel level, const char* func, int line,
                         const char* msg, ...);

    static std::vector<UIStr> GetErrorMsgList() { return std::move(msg_list_); }
    static void SetExtraFunc(ExtraFunc extra_fun) { extra_fun_ = extra_fun; }

private:
    static std::vector<UIStr> msg_list_;
    static ExtraFunc extra_fun_;
};
}  // namespace DuiMini

#endif  // !DUI_UTILS_UIEXCEPTION_H_
