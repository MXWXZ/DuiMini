/** @file
 * UI event transfered.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_UTILS_UIEVENT_HPP_
#define DUI_UTILS_UIEVENT_HPP_

#include "UIDefine.h"
#include "UIUtils.h"

namespace DuiMini {
enum Event {
    kEVT_START_ = 0,

    kEVT_MouseEnter,
    kEVT_MouseLeave,
    kEVT_MouseMove,
    kEVT_LButtonDown,
    kEVT_LButtonUp,
    kEVT_LButtonClick,
    kEVT_LButtonDBClick,
    kEVT_RButtonDown,
    kEVT_RButtonUp,
    kEVT_RButtonClick,
    kEVT_RButtonDBClick,

    kEVT_Disable,
    kEVT_Active,
    kEVT_Invisible,
    kEVT_Visible,

    kEVT_SkinChange,
    kEVT_LangChange,

    kEVT_Count
};

struct ResChangeEvent {
    uint old_resid;  //!< old id
    uint new_resid;  //!< new id
};

/**
 * Control event.
 * Every control behavior is driven by the message
 * @todo    Add new Msg
 */
class DUIMINI_API UIEvent {
public:
    UIEvent() {}
    UIEvent(Event event) : event_(event) {}
    ~UIEvent() {}

public:
    void SetEvent(Event event) { event_ = event; }
    Event GetEvent() const { return event_; }

    void SetPos(Point pos) { mouse_move_ = pos; }
    Point GetPos() const { return mouse_move_; }

    void SetRes(ResChangeEvent res) { res_change_ = res; }
    ResChangeEvent GetRes() const { return res_change_; }

private:
    Event event_ = kEVT_START_;

    union {
        Point mouse_move_;
        ResChangeEvent res_change_;
    };
};

}  // namespace DuiMini

#endif  // !DUI_UTILS_UIEVENT_HPP_
