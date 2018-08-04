/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIContainer.h"

namespace DuiMini {
UIContainer::UIContainer() {}

UIContainer::~UIContainer() {
    RemoveAll();
}

void UIContainer::SetBGColor(LPCTSTR v_color) {
    SetAttribute(_T("bgcolor"), v_color);
}

UIColor UIContainer::GetBGColor() const {
    return UIColor(GetAttribute(_T("bgcolor")));
}

UIControl* UIContainer::GetItem(UINT v_index) const {
    if (v_index >= item_.size())
        return nullptr;
    return (UIControl*)item_[v_index];
}

UINT UIContainer::GetCount() const {
    return item_.size();
}

void UIContainer::Add(UIControl* v_ctrl) {
    item_.push_back(v_ctrl);
}

bool UIContainer::Remove(UIControl* v_ctrl) {
    for (auto i = item_.begin(); i != item_.end(); ++i) {
        if ((UIControl*)(*i) == v_ctrl) {
            // if parent exist, "delete" will call UIContainer::Remove
            v_ctrl->SetParent(nullptr);     // Prevent dead recursive
            delete v_ctrl;
            item_.erase(i);
            return true;
        }
    }
    return false;
}

void UIContainer::RemoveAll() {
    for (auto& i : item_) {
        UIControl* ctrl = (UIControl*)i;
        // if parent exist, "delete" will call UIContainer::Remove
        ctrl->SetParent(nullptr);     // Prevent dead recursive
        delete ctrl;
    }
    item_.clear();
}

void UIContainer::Paint(bool v_background/* = false*/) {
    basewnd_->GetRender()->DrawFillRect(rect_, GetBGColor());
    for (auto& i : item_) {
        UIControl* ctrl = (UIControl*)i;
        if (ctrl->AttachBgPaint(STAY) == v_background
            && ctrl->VisibleCtrl(STAY))
            ctrl->Paint(v_background);
    }
    UIControl::Paint(v_background);
}
UIControl* UIContainer::FindCtrlFromPT(POINT v_pt) {
    if (!PtInRect(v_pt))
        return nullptr;
    UIControl* ret = nullptr;
    for (auto& i : item_) {
        UIControl* ctrl = ((UIControl*)i)->FindCtrlFromPT(v_pt);
        if (ctrl != nullptr)    // last pos match
            ret = ctrl;
    }
    if (ret)
        return ret;
    return UIControl::FindCtrlFromPT(v_pt);
}

void UIContainer::SetBaseWindow(UIWindow* v_basewnd) {
    for (auto& i : item_)
        ((UIControl*)i)->SetBaseWindow(v_basewnd);
    // set all his children nodes' base window first
    // then set his own's
    UIControl::SetBaseWindow(v_basewnd);
}

LPVOID UIContainer::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_CONTAINER))
        return this;
    return UIControl::GetInterface(v_name);
}

UIControl* UIContainer::FindCtrlFromName(LPCTSTR v_name) {
    for (auto& i : item_) {
        UIControl* ctrl = ((UIControl*)i)->FindCtrlFromName(v_name);
        if (ctrl != nullptr)    // first name match
            return ctrl;
    }
    return UIControl::FindCtrlFromName(v_name);
}

UIRect UIContainer::UpdatePos() {
    for (auto& i : item_) {
        UIControl* ctrl = (UIControl*)i;
        ctrl->UpdatePos();
    }
    return UIControl::UpdatePos();
}

bool UIContainer::Event(const UIEvent &v_event) {
    switch (v_event) {
    case kWM_Disable:
    case kWM_Active:
    case kWM_Visible:
    case kWM_Invisible:
    case kWM_SkinChange:
    case kWM_LangChange:
        for (auto& i : item_)
            ((UIControl*)i)->Event(v_event);
        break;
    }
    return UIControl::Event(v_event);
}
}   // namespace DuiMini
