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

UIControl::~UIControl() {
    if (parent_)
        dynamic_cast<IUIContainer*>(parent_)->Remove(this);
}

void UIControl::SetAttribute(LPCTSTR v_name, LPCTSTR v_value) {
    attr_[v_name] = v_value;
}

void UIControl::AfterSetAttribute() {
    UpdatePos();
    Event(UIEvent(kWM_LangChange, 0, UIConfig::GetShownLang()));
    Event(UIEvent(kWM_SkinChange, 0, UIConfig::GetShownSkin()));
    DisableCtrl(DisableCtrl(-1));
}

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
    if (PtInRect(v_pt)) {
        if (AttachBackground(STAY))
            return basewnd_->GetDialog();
        return this;
    } 
    else {
        return nullptr;
    }
}

UIControl* UIControl::FindCtrlFromName(LPCTSTR v_name) {
    if (GetName() == v_name)
        return this;
    else
        return nullptr;
}

bool UIControl::Event(const UIEvent& v_event) {
    if (v_event < kWM_IgnoreDisable_ && DisableCtrl(STAY))
        return true;
    bool ret = true;
    // call notify func
    if (msgmap_[v_event])
        ret = (basewnd_->*msgmap_[v_event])(v_event);
    if (!ret)
        return false;
    bool flg = true;
    // TODO: Add new Msg
    switch (v_event) {
    case kWM_MouseEnter:
        ret = OnMouseEnter(v_event);
        break;
    case kWM_MouseLeave:
        ret = OnMouseLeave(v_event);
        break;
    case kWM_MouseMove:
        OnMouseMove(v_event);
        return true;    // Do NOT record MouseMove MSG

    case kWM_LButtonDown:
        if (flg)
            (ret = OnLButtonDown(v_event)), flg = false;
    case kWM_LButtonUp:
        if (flg)
            (ret = OnLButtonUp(v_event)), flg = false;
    case kWM_LButtonClick:
        if (flg)
            (ret = OnLButtonClick(v_event)), flg = false;
    case kWM_LButtonDBClick:
        if (flg)
            (ret = OnLButtonDBClick(v_event)), flg = false;
    case kWM_RButtonDown:
        if (flg)
            (ret = OnRButtonDown(v_event)), flg = false;
    case kWM_RButtonUp:
        if (flg)
            (ret = OnRButtonUp(v_event)), flg = false;
    case kWM_RButtonClick:
        if (flg)
            (ret = OnRButtonClick(v_event)), flg = false;
    case kWM_RButtonDBClick:
        if (flg)
            (ret = OnRButtonDBClick(v_event)), flg = false;
        break;

    case kWM_Disable:
        ret = OnDisable(v_event);
        break;
    case kWM_Active:
        ret = OnActive(v_event);
        break;
    case kWM_SkinChange:
        ret = OnSkinChange(v_event);
        break;
    case kWM_LangChange:
        ret = OnLangChange(v_event);
        break;
    }
    UIRecLog::RecordLog(kLL_Info, _T("Message hit! Control name:\"%s\",Message:%d"),
                        GetAttribute(_T("name")).GetData(), v_event.GetMsg());
    return ret;
}

void UIControl::SetMsgHandler(WindowMessage v_msg, MsgHandleFun v_func) {
    msgmap_[v_msg] = v_func;
}

MsgHandleFun UIControl::GetMsgHandler(WindowMessage v_msg) const {
    return msgmap_[v_msg];
}

int UIControl::ParsePosStr(LPCTSTR v_str, StrLoc v_loc,
                           UIRect* v_parentrect/* = nullptr*/) const {
    CUStr str = v_str;
    UIRect parentrc;
    if (v_parentrect) {
        parentrc = *v_parentrect;
    } else {
        if (!parent_) {     // default parent is screen
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
        if (v_loc == left || v_loc == right) {
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

UIRect UIControl::ParsePosStr(LPCTSTR v_str,
                              UIRect* v_parentrect/* = nullptr*/) const {
    UIRect ret;
    CUStr tmp = v_str;
    int seppos1 = tmp.Find(_T(","));
    ret.left = ParsePosStr(tmp.Left(seppos1), left, v_parentrect);
    int seppos2 = tmp.Find(_T(","), seppos1 + 1);
    ret.top = ParsePosStr(tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top, v_parentrect);
    int seppos3 = tmp.Find(_T(","), seppos2 + 1);
    ret.right = ParsePosStr(tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right, v_parentrect);
    ret.bottom = ParsePosStr(tmp.Right(tmp.GetLength() - seppos3 - 1), bottom, v_parentrect);
    return ret;
}

LPVOID UIControl::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_CONTROL))
        return this;
    return nullptr;
}

bool UIControl::PtInRect(POINT v_pt) {
    return ::PtInRect(&rect_.rect(), v_pt);
}

UIRect UIControl::UpdatePos() {
    UStr attr = GetAttribute(_T("pos"));
    int septimes = attr.Replace(_T(","), _T(","));
    if (septimes == 1) {    // pos=x,x
        int seppos = attr.Find(_T(","));
        rect_.left = ParsePosStr(attr.Left(seppos), left);
        rect_.top = ParsePosStr(attr.Right(attr.GetLength() - seppos - 1), top);
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
        rect_ = ParsePosStr(attr);
    }
    UStr width(rect_.right - rect_.left);
    UStr height(rect_.bottom - rect_.top);
    SetAttribute(_T("width"), width);
    SetAttribute(_T("height"), height);
    SetAttribute(_T("size"), width + _T(",") + height);
    return rect_;
}

CUStr UIControl::GetName() const {
    return GetAttribute(_T("name"));
}

void UIControl::SetPos(LPCTSTR v_pos) {
    SetAttribute(_T("pos"), v_pos);
    UpdatePos();
}

UIRect UIControl::GetPos() const {
    return rect_;
}

long UIControl::GetWidth() const {
    return rect_.right - rect_.left;
}

long UIControl::GetHeight() const {
    return rect_.bottom - rect_.top;
}

bool UIControl::DisableCtrl(BOOL v_disable) {
    STATE_FUNC_START(_T("disable"), v_disable)
        if (v_disable == TRUE)
            Event(UIEvent(kWM_Disable));
        else
            Event(UIEvent(kWM_Active));
        STATE_FUNC_END
}

bool UIControl::AttachBackground(BOOL v_bg) {
    STATE_FUNC_START(_T("background"), v_bg)
        STATE_FUNC_END
}

}   // namespace DuiMini
