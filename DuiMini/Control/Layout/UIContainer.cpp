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
            delete v_ctrl;
            return item_.Remove(it);
        }
    }
    return false;
}

void UIContainer::RemoveAll() {
    for (UINT it = 0; it < item_.GetSize(); ++it)
        delete reinterpret_cast<UIControl*>(item_[it]);
    item_.Empty();
}

void UIContainer::DoPaint(HWND v_hwnd, IUIRender* v_render) {
    for (UINT it = 0; it < item_.GetSize(); ++it) {
        UIControl* ctrl = reinterpret_cast<UIControl*>(item_[it]);
        ctrl->DoPaint(v_hwnd, v_render);
    }
}
UIControl* UIContainer::FindCtrlFromPT(POINT v_pt) {
    if (!::PtInRect(&rect_, v_pt))
        return nullptr;
    for (UINT it = 0; it != item_.GetSize(); ++it) {
        UIControl* ctrl = ((UIControl*)item_[it])->FindCtrlFromPT(v_pt);
        if (ctrl != nullptr)
            return ctrl;
    }
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
    if (CmpStr(v_name, _T("Container")))
        return this;
    return UIControl::GetInterface(v_name);
}

void UIContainer::AfterSetAttribute() {
    UIControl::AfterSetAttribute();
}

}   // namespace DuiMini
