/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/02/28
 *
 * @Description:
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
    bool OnMouseEnter(const UIEvent& v_event) override;
    bool OnMouseLeave(const UIEvent& v_event) override;
    bool OnLButtonDown(const UIEvent& v_event) override;
    bool OnLButtonUp(const UIEvent& v_event) override;
    bool OnDisable(const UIEvent& v_event) override;
    bool OnActive(const UIEvent& v_event) override;
    bool OnInvisible(const UIEvent& v_event) override;

protected:
    ButtonState state_ = kBS_Normal;
};
}   // namespace DuiMini
