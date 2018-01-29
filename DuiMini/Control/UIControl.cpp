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
#include "UIControl.h"

namespace DuiMini {
UIControl::UIControl() {}

UIControl::~UIControl() {}

void UIControl::BeforeSetAttribute() {
    SetAttribute(_T("name"), _T("Static"));
    SetAttribute(_T("pos"), _T("0,0"));
    SetAttribute(_T("width"), _T("0"));
    SetAttribute(_T("height"), _T("0"));
}

void UIControl::SetAttribute(LPCTSTR v_name, LPCTSTR v_value) {
    attr_[v_name] = v_value;
}

void UIControl::AfterSetAttribute() {
    UpdatePos();
    LoadTextAttr();
    LoadResAttr();
}

void UIControl::LoadResAttr() {}

void UIControl::LoadTextAttr() {}

CUStr UIControl::GetAttribute(LPCTSTR v_name) const {
    return attr_.GetValue(v_name);
}

void UIControl::SetParent(UIControl* v_parent) {
    parent_ = v_parent;
}

UIControl* UIControl::GetParent() const {
    return parent_;
}

void UIControl::SetBaseWindow(UIWindow* v_basewnd) {
    basewnd_ = v_basewnd;
}

UIWindow* UIControl::GetBaseWindow() const {
    return basewnd_;
}

UIControl* UIControl::FindCtrlFromPT(POINT v_pt) {
    if (PtInRect(&rect_, v_pt))
        return this;
    else
        return nullptr;
}

UIControl * UIControl::FindCtrlFromName(LPCTSTR v_name) {
    if (GetAttribute(_T("name")) == v_name)
        return this;
    else
        return nullptr;
}

int UIControl::GetPosFromStr(LPCTSTR v_str, StrLoc v_loc) const {
    CUStr str = v_str;
    RECT screen{ 0, 0, 0, 0 };
    if (!parent_) {     // default parent is screen
        screen.right = GetSystemMetrics(SM_CXSCREEN);
        screen.bottom = GetSystemMetrics(SM_CYSCREEN);
    }
    if (str[0] == '$') {
        return str.Right(str.GetLength() - 1).Str2Int();
    } else if (str[0] == '|') {
        int offset = str.Right(str.GetLength() - 1).Str2Int();
        // ONLY 2nd layer control can be relative to parent
        RECT parentrc = parent_ ? parent_->GetPos() : screen;
        int center;
        if (v_loc == left || v_loc == right)
            center = (parentrc.left + parentrc.right) / 2;
        else
            center = (parentrc.top + parentrc.bottom) / 2;
        return center + offset;
    } else if (str[0] == '%') {
        int percent = str.Right(str.GetLength() - 1).Str2Int();
        RECT parentrc = parent_ ? parent_->GetPos() : screen;
        int ret;
        if (v_loc == left || v_loc == right)
            ret = parentrc.left + (parentrc.right - parentrc.left)*percent / 100;
        else
            ret = parentrc.top + (parentrc.bottom - parentrc.top)*percent / 100;
        return ret;
    } else {
        return str.Str2Int();
    }
}

// void UIControl::Event(TEventUI& event) {
// 
// }

LPVOID UIControl::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_CONTROL))
        return this;
    return nullptr;
}

RECT UIControl::UpdatePos() {
    UStr attr = GetAttribute(_T("pos"));
    int septimes = attr.Replace(_T(","), _T(","));
    if (septimes == 1) {
        int seppos = attr.Find(_T(","));
        rect_.left = GetPosFromStr(attr.Left(seppos), left);
        rect_.top = GetPosFromStr(attr.Right(attr.GetLength() - seppos - 1), top);
        rect_.right = rect_.left + GetAttribute(_T("width")).Str2Int();
        rect_.bottom = rect_.top + GetAttribute(_T("height")).Str2Int();
    } else {
        int seppos1 = attr.Find(_T(","));
        rect_.left = GetPosFromStr(attr.Left(seppos1), left);
        int seppos2 = attr.Find(_T(","), seppos1 + 1);
        rect_.top = GetPosFromStr(attr.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top);
        int seppos3 = attr.Find(_T(","), seppos2 + 1);
        rect_.right = GetPosFromStr(attr.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right);
        rect_.bottom = GetPosFromStr(attr.Right(attr.GetLength() - seppos3 - 1), bottom);
        SetAttribute(_T("width"), UStr(rect_.right - rect_.left));
        SetAttribute(_T("height"), UStr(rect_.bottom - rect_.top));
    }
    return rect_;
}

RECT UIControl::SetPos(LPCTSTR v_pos) {
    SetAttribute(_T("pos"), v_pos);
    return UpdatePos();
}

RECT UIControl::GetPos() const {
    return rect_;
}

}   // namespace DuiMini
