/**
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include "Utils/UIException.h"
#include "Core/UISystem.h"
#include <SFML/System/Err.hpp>

#include <stdarg.h>
#include <vector>

namespace DuiMini {
std::vector<UIStr> UIException::msg_list_;
ExtraFunc UIException::extra_fun_ = nullptr;

void UIException::SetError(ErrorLevel level, const char* func, int line,
                           const char* msg, ...) {
    if (level == kEL_Normal)
        return;

    // va_list can only be used once in gcc!
    // though reuse is also allowed in MinGW
    va_list args1, args2;
    va_start(args1, msg);
    va_copy(args2, args1);
    int len = vsnprintf(nullptr, 0, msg, args1);
    va_end(args1);
    auto buf = make_shared_array<char>(len + 1);
    vsnprintf(buf.get(), len + 1, msg, args2);
    va_end(args2);

    UIStr tmp;
    switch (level) {
        case kEL_Warning:
            tmp = "Warning!";
            break;
        case kEL_Error:
            tmp = "Error!";
            break;
    }
    tmp.Format("%s - %s\n[In function:\"%s\" line:%d]", tmp.GetData(),
               buf.get(), func, line);
    sf::err() << tmp.GetData() << std::endl;
    msg_list_.push_back(tmp);

    bool ishandled = false;
    if (extra_fun_)
        ishandled = extra_fun_(level, tmp.GetData());
    if (!ishandled && level == kEL_Error)
        UISystem::Exit(EXIT_FAILURE);
}

}  // namespace DuiMini
