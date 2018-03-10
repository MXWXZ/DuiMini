/**
* Copyright (c) 2017-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2017/11/28
*
* @Description:
*/
#include "stdafx.h"
#include "UIContainer.h"

namespace DuiMini {
UIContainer::UIContainer() {}

UIContainer::~UIContainer() {
    RemoveAll();
}

UIControl* UIContainer::GetItem(UINT v_index) const {
    if (v_index >= item_.GetSize())
        return nullptr;
    return reinterpret_cast<UIControl*>(item_[v_index]);
}

UINT UIContainer::GetCount() const {
    return item_.GetSize();
}

bool UIContainer::Add(UIControl* v_ctrl) {
    return item_.Add(v_ctrl);
}

bool UIContainer::Remove(UIControl* v_ctrl) {
    for (UINT it = 0; it < item_.GetSize(); ++it) {
        if (reinterpret_cast<UIControl*>(item_[it]) == v_ctrl) {
            // if parent exist, "delete" will call UIContainer::Remove
            v_ctrl->SetParent(nullptr);     // Prevent dead recursive
            delete v_ctrl;
            return item_.Remove(it);
        }
    }
    return false;
}

void UIContainer::RemoveAll() {
    for (UINT it = 0; it < item_.GetSize(); ++it) {
        UIControl* ctrl = reinterpret_cast<UIControl*>(item_[it]);
        // if parent exist, "delete" will call UIContainer::Remove
        ctrl->SetParent(nullptr);     // Prevent dead recursive
        delete ctrl;
    }
    item_.Empty();
}

void UIContainer::Paint(bool v_background/* = false*/) {
    for (UINT it = 0; it < item_.GetSize(); ++it) {
        UIControl* ctrl = reinterpret_cast<UIControl*>(item_[it]);
        if (ctrl->AttachBackground(STAY) == v_background)
            ctrl->Paint(v_background);
    }
}
UIControl* UIContainer::FindCtrlFromPT(POINT v_pt) {
    if (!PtInRect(v_pt))
        return nullptr;
    UIControl* ret = nullptr;
    for (UINT it = 0; it != item_.GetSize(); ++it) {
        UIControl* ctrl = ((UIControl*)item_[it])->FindCtrlFromPT(v_pt);
        if (ctrl != nullptr)    // last pos match
            ret = ctrl;
    }
    if (ret)
        return ret;
    return UIControl::FindCtrlFromPT(v_pt);
}

void UIContainer::SetBaseWindow(UIWindow* v_basewnd) {
    for (UINT it = 0; it < item_.GetSize(); ++it)
        reinterpret_cast<UIControl*>(item_[it])->SetBaseWindow(v_basewnd);
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
    for (UINT it = 0; it != item_.GetSize(); ++it) {
        UIControl* ctrl = ((UIControl*)item_[it])->FindCtrlFromName(v_name);
        if (ctrl != nullptr)    // first name match
            return ctrl;
    }
    return UIControl::FindCtrlFromName(v_name);
}

UIRect UIContainer::UpdatePos() {
    for (UINT it = 0; it < item_.GetSize(); ++it) {
        UIControl* ctrl = reinterpret_cast<UIControl*>(item_[it]);
        ctrl->UpdatePos();
    }
    return UIControl::UpdatePos();
}
}   // namespace DuiMini
