/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
enum ButtonState {
    kBS_Normal,
    kBS_Hover,
    kBS_Click,
    kBS_Disable
};

class DUIMINI_API UIButton :public UIImage {
public:
    UIButton();
    virtual ~UIButton();

public:
    void SetState(ButtonState v_state);
    ButtonState GetState() const;

public:
    ATTR_MAP_BEGIN
        PARENT_ATTR(UIImage)
        ATTR_MAP_END

    LPVOID GetInterface(LPCTSTR v_name) override;
    void Paint(bool v_background = false) override;

protected:
    OVERRIDE_MSGFUNC(OnMouseEnter)
    OVERRIDE_MSGFUNC(OnMouseLeave)
    OVERRIDE_MSGFUNC(OnLButtonDown)
    OVERRIDE_MSGFUNC(OnLButtonUp)
    OVERRIDE_MSGFUNC(OnDisable)
    OVERRIDE_MSGFUNC(OnActive)
    OVERRIDE_MSGFUNC(OnInvisible)

protected:
    ButtonState state_ = kBS_Normal;
};
}   // namespace DuiMini
