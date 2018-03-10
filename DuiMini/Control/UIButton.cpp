/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/02/28
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIButton.h"

namespace DuiMini {
UIButton::UIButton() {}

UIButton::~UIButton() {}

void UIButton::SetState(ButtonState v_state) {
    state_ = v_state;
}

ButtonState UIButton::GetState() const {
    return state_;
}

LPVOID UIButton::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_BUTTON))
        return this;
    return UIImage::GetInterface(v_name);
}

void UIButton::Paint(bool v_background/* = false*/) {
    UIRect srcrect;
    srcrect.bottom = img_->GetHeight();
    srcrect.left = img_->GetWidth() / 4 * state_;
    srcrect.right = img_->GetWidth() / 4 * (state_ + 1);
    basewnd_->GetRender()->DrawImage(img_, rect_, srcrect);
}

bool UIButton::OnMouseEnter(const UIEvent& v_event) {
    SetState(kBS_Hover);
    basewnd_->UpdateWindow();
    return true;
}

bool UIButton::OnMouseLeave(const UIEvent& v_event) {
    SetState(kBS_Normal);
    basewnd_->UpdateWindow();
    return true;
}

bool UIButton::OnLButtonDown(const UIEvent& v_event) {
    SetState(kBS_Click);
    basewnd_->UpdateWindow();
    return true;
}

bool UIButton::OnLButtonUp(const UIEvent& v_event) {
    SetState(kBS_Hover);
    basewnd_->UpdateWindow();
    return true;
}

bool UIButton::OnDisable(const UIEvent & v_event) {
    SetState(kBS_Disable);
    return true;
}

bool UIButton::OnActive(const UIEvent & v_event) {
    SetState(kBS_Normal);
    return true;
}

bool UIButton::OnInvisible(const UIEvent & v_event) {
    SetState(kBS_Normal);   // init state
    return true;
}

}   // namespace DuiMini
