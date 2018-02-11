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

void UIControl::SetAttribute(LPCTSTR v_name, LPCTSTR v_value) {
    attr_[v_name] = v_value;
}

void UIControl::AfterSetAttribute() {
    UpdatePos();
    Event(kWM_LangChange, 0, UIConfig::GetShownLang());
    Event(kWM_SkinChange, 0, UIConfig::GetShownSkin());
}

void UIControl::OnSkinChange(SKINID v_former, SKINID v_new) {}

void UIControl::OnLangChange(LANGID v_former, LANGID v_new) {}

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
    if (!independent_)
        return nullptr;

    if (PtInRect(v_pt))
        return this;
    else
        return nullptr;
}

UIControl* UIControl::FindCtrlFromName(LPCTSTR v_name) {
    if (!independent_)
        return nullptr;

    if (GetAttribute(_T("name")) == v_name)
        return this;
    else
        return nullptr;
}

bool UIControl::Event(WindowMessage v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    bool ret = true;
    // call notify func
    if (msgmap_[v_msg])
        ret = (basewnd_->*msgmap_[v_msg])(v_wparam, v_lparam);
    if (!ret)
        return false;
    switch (v_msg) {
    case kWM_LButtonDown:
    case kWM_LButtonUp:
    case kWM_LButtonClick:
    case kWM_LButtonDBClick:
    case kWM_RButtonDown:
    case kWM_RButtonUp:
    case kWM_RButtonClick:
    case kWM_RButtonDBClick:
        UIRecLog::RecordLog(kLL_Info, _T("Message hit! Control name:\"%s\",Message:%d"),
                            GetAttribute(_T("name")).GetData(), v_msg);
        break;
    case kWM_SkinChange:
        OnSkinChange(static_cast<SKINID>(v_wparam),
                     static_cast<SKINID>(v_lparam));
        break;
    case kWM_LangChange:
        OnLangChange(static_cast<LANGID>(v_wparam),
                     static_cast<LANGID>(v_lparam));
        break;
    }
    return true;
}

void UIControl::SetMsgHandler(WindowMessage v_msg, MsgHandleFun v_func) {
    msgmap_[v_msg] = v_func;
}

MsgHandleFun UIControl::GetMsgHandler(WindowMessage v_msg) const {
    return msgmap_[v_msg];
}

bool UIControl::SetIndependent(BOOL v_independent/* = TRUE*/) {
    bool ret = independent_;
    if (v_independent >= 0)
        ret = independent_ = v_independent;
    return ret;
}

int UIControl::GetPosFromStr(LPCTSTR v_str, StrLoc v_loc,
                             UIControl* v_parent/* = nullptr*/) const {
    CUStr str = v_str;
    RECT parentrc;
    if (v_parent) {
        parentrc = v_parent->GetPos();
    } else {
        if (!parent_) {     // default parent is screen
            parentrc.left = 0;
            parentrc.top = 0;
            parentrc.right = GetSystemMetrics(SM_CXSCREEN);
            parentrc.bottom = GetSystemMetrics(SM_CYSCREEN);
        } else {
            parentrc = parent_->GetPos();
        }
    }
    if (str[0] == '$') {
        return str.Right(str.GetLength() - 1).Str2Int();
    } else if (str[0] == '|') {
        int offset = str.Right(str.GetLength() - 1).Str2Int();
        // ONLY 2nd layer control can be relative to parent
        int center;
        if (v_loc == left || v_loc == right)
            center = (parentrc.left + parentrc.right) / 2;
        else
            center = (parentrc.top + parentrc.bottom) / 2;
        return center + offset;
    } else if (str[0] == '%') {
        int percent = str.Right(str.GetLength() - 1).Str2Int();
        int ret;
        if (v_loc == left || v_loc == right)
            ret = parentrc.left + (parentrc.right - parentrc.left)*percent / 100;
        else
            ret = parentrc.top + (parentrc.bottom - parentrc.top)*percent / 100;
        return ret;
    } else {
        int offset = str.Str2Int();
        if (v_loc == left)
            return parentrc.left + offset;
        else if (v_loc == top)
            return parentrc.top + offset;
        else if (v_loc == right) {
            if (str[0] == '-')
                return parentrc.right + offset;
            else
                return parentrc.left + offset;
        }
        else {
            if (str[0] == '-')
                return parentrc.bottom + offset;
            else
                return parentrc.top + offset;
        }
    }
}

LPVOID UIControl::GetInterface(LPCTSTR v_name) {
    if (!independent_)
        return nullptr;

    if (CmpStr(v_name, CTRLNAME_CONTROL))
        return this;
    return nullptr;
}

bool UIControl::PtInRect(POINT v_pt) {
    return ::PtInRect(&rect_, v_pt);
}

RECT UIControl::UpdatePos() {
    UStr attr = GetAttribute(_T("pos"));
    int septimes = attr.Replace(_T(","), _T(","));
    if (septimes == 1) {    // pos=x,x
        int seppos = attr.Find(_T(","));
        rect_.left = GetPosFromStr(attr.Left(seppos), left);
        rect_.top = GetPosFromStr(attr.Right(attr.GetLength() - seppos - 1), top);
        if (GetAttribute(_T("width")) == _T("0") &&
            GetAttribute(_T("height")) == _T("0")) {
            UStr size = GetAttribute(_T("size"));
            int tmppos = size.Find(_T(","));
            rect_.right = rect_.left + size.Left(tmppos).Str2Int();
            rect_.bottom = rect_.top + size.Right(size.GetLength() - tmppos - 1).Str2Int();
        } else {
            rect_.right = rect_.left + GetAttribute(_T("width")).Str2Int();
            rect_.bottom = rect_.top + GetAttribute(_T("height")).Str2Int();
        }
    } else {    // pos=x,x,x,x
        int seppos1 = attr.Find(_T(","));
        rect_.left = GetPosFromStr(attr.Left(seppos1), left);
        int seppos2 = attr.Find(_T(","), seppos1 + 1);
        rect_.top = GetPosFromStr(attr.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top);
        int seppos3 = attr.Find(_T(","), seppos2 + 1);
        rect_.right = GetPosFromStr(attr.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right);
        rect_.bottom = GetPosFromStr(attr.Right(attr.GetLength() - seppos3 - 1), bottom);
    }
    UStr width(rect_.right - rect_.left);
    UStr height(rect_.bottom - rect_.top);
    SetAttribute(_T("width"), width);
    SetAttribute(_T("height"), height);
    SetAttribute(_T("size"), width + _T(",") + height);
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
