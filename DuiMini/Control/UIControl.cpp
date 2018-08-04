/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIControl.h"

namespace DuiMini {
UIControl::UIControl() {}

UIControl::~UIControl() {
    IUIContainer* tmp = dynamic_cast<IUIContainer*>(parent_);
    if (tmp)
        tmp->Remove(this);
}

void UIControl::SetAttribute(LPCTSTR v_name, LPCTSTR v_value) {
    attr_[v_name] = v_value;
}

void UIControl::AfterSetAttribute() {
    UpdatePos();
    INIT_STATE(DisableCtrl);
    INIT_STATE(VisibleCtrl);
    INIT_STATE(AttachBgPaint);
}

CUStr UIControl::GetAttribute(LPCTSTR v_name) const {
    auto it = attr_.find(v_name);
    return it != attr_.end() ? it->second : CUStr();
}

void UIControl::Paint(bool v_background) {
    long size = GetBorderSize();
    if (size != 0)
        basewnd_->GetRender()->DrawRect(rect_, GetBorderColor(), size);
}

UIControl* UIControl::FindCtrlFromPT(POINT v_pt) {
    if (PtInRect(v_pt) && VisibleCtrl(STAY)) {
        CtrlTransmouse mode = GetTransmouse();
        if (mode == kCT_Single) {
            return nullptr;
        } else if (mode == kCT_All) {
            if (!basewnd_)
                return nullptr;
            return basewnd_->GetDialog();
        }
        return this;
    } else {
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
    // check control status, ignore msg when disabled or invisible
    if (v_event < kWM_IgnoreLimit_ && (DisableCtrl(STAY) || !VisibleCtrl(STAY)))
        return true;

    // call notify func
    if (msgmap_[v_event])
        if (!msgmap_[v_event](v_event))
            return false;

    bool ret = true;
    // TODO: Add new Msg
    switch (v_event) {
    case kWM_MouseEnter:
        ret = OnMouseEnter(v_event);
        break;
    case kWM_MouseLeave:
        ret = OnMouseLeave(v_event);
        break;
    case kWM_MouseMove:
        ret = OnMouseMove(v_event);
        break;

    case kWM_LButtonDown:
        ret = OnLButtonDown(v_event);
        break;
    case kWM_LButtonUp:
        ret = OnLButtonUp(v_event);
        break;
    case kWM_LButtonClick:
        ret = OnLButtonClick(v_event);
        break;
    case kWM_LButtonDBClick:
        ret = OnLButtonDBClick(v_event);
        break;
    case kWM_RButtonDown:
        ret = OnRButtonDown(v_event);
        break;
    case kWM_RButtonUp:
        ret = OnRButtonUp(v_event);
        break;
    case kWM_RButtonClick:
        ret = OnRButtonClick(v_event);
        break;
    case kWM_RButtonDBClick:
        ret = OnRButtonDBClick(v_event);
        break;

    case kWM_Disable:
        ret = OnDisable(v_event);
        break;
    case kWM_Active:
        ret = OnActive(v_event);
        break;
    case kWM_Visible:
        ret = OnVisible(v_event);
        break;
    case kWM_Invisible:
        ret = OnInvisible(v_event);
        break;
    case kWM_SkinChange:
        ret = OnSkinChange(v_event);
        break;
    case kWM_LangChange:
        ret = OnLangChange(v_event);
        break;
    }
#ifdef _DEBUG
    UStr debugmsg;
    debugmsg.Format(_T("Control \"%s\" notify message %d!\n"),
                    GetName().GetData(), v_event.GetMsg());
    if (v_event != kWM_MouseMove)   // ignore too frequent msg
        OutputDebugString(debugmsg);
#endif // _DEBUG
    return ret;
}

void UIControl::SetMsgHandler(WindowMessage v_msg, MsgHandleFun v_func) {
    msgmap_[v_msg] = v_func;
}

MsgHandleFun UIControl::GetMsgHandler(WindowMessage v_msg) const {
    return msgmap_[v_msg];
}

bool UIControl::OnLangChange(const UIEvent & v_event) {
    SetToolTip(GetToolTip());
    return true;
}

long UIControl::ParsePosStr(LPCTSTR v_str, StrLoc v_loc,
                            UIRect* v_parentrect/* = nullptr*/) const {
    CUStr str = v_str;
    UIRect parentrc;
    if (v_parentrect) {
        parentrc = *v_parentrect;
    } else {
        if (!parent_)     // default parent is screen
            parentrc = UIUtils::GetScreenSize();
        else
            parentrc = parent_->GetPos();
    }
    if (str[0] == '$') {
        return str.Right(str.GetLength() - 1).Str2LL();
    } else if (str[0] == '|') {
        long offset = str.Right(str.GetLength() - 1).Str2LL();
        // ONLY 2nd layer control can be relative to parent
        long center;
        if (v_loc == left || v_loc == right)
            center = (parentrc.left + parentrc.right) / 2;
        else
            center = (parentrc.top + parentrc.bottom) / 2;
        return center + offset;
    } else if (str[0] == '%') {
        double percent = str.Right(str.GetLength() - 1).Str2Double();
        long ret;
        if (v_loc == left || v_loc == right)
            ret = parentrc.left + parentrc.width()*percent / 100;
        else
            ret = parentrc.top + parentrc.height()*percent / 100;
        return ret;
    } else {
        long offset = str.Str2LL();
        if (v_loc == left || v_loc == right) {
            if (str[0] == '-')
                return parentrc.right + offset;
            else
                return parentrc.left + offset;
        } else {
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
    ret.left   = ParsePosStr(DivideStr(v_str, 1), left,   v_parentrect);
    ret.top    = ParsePosStr(DivideStr(v_str, 2), top,    v_parentrect);
    ret.right  = ParsePosStr(DivideStr(v_str, 3), right,  v_parentrect);
    ret.bottom = ParsePosStr(DivideStr(v_str, 4), bottom, v_parentrect);
    return ret;
}

CUStr UIControl::DivideStr(LPCTSTR v_str, unsigned short v_cnt) const {
    UStr str = v_str;
    LL pos = 0;
    unsigned short cnt = 0;
    while (true) {
        LL tmp = str.Find(',', pos + 1);
        if (tmp != -1)
            ++cnt;
        else if (v_cnt - 1 == cnt)
            return str.Right(str.GetLength() - pos - 1);
        else
            return CUStr();
        if (v_cnt == cnt) {
            if (v_cnt == 1)
                return str.Left(tmp);
            return str.Mid(pos + 1, tmp - pos - 1);
        }
        pos = tmp;
    }
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
    size_t septimes = attr.Replace(_T(","), _T(","));
    if (septimes == 1) {    // pos=x,x
        rect_.left = ParsePosStr(DivideStr(attr, 1), left);
        rect_.top = ParsePosStr(DivideStr(attr, 2), top);
        if (GetAttribute(_T("width")) == _T("0") &&
            GetAttribute(_T("height")) == _T("0")) {
            UStr size = GetAttribute(_T("size"));
            rect_.right = rect_.left + DivideStr(size, 1).Str2LL();
            rect_.bottom = rect_.top + DivideStr(size, 2).Str2LL();
        } else {
            rect_.right = rect_.left + GetAttribute(_T("width")).Str2LL();
            rect_.bottom = rect_.top + GetAttribute(_T("height")).Str2LL();
        }
    } else {    // pos=x,x,x,x
        rect_ = ParsePosStr(attr);
    }
    UStr width(rect_.width());
    UStr height(rect_.height());
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
    return rect_.width();
}

long UIControl::GetHeight() const {
    return rect_.height();
}

bool UIControl::DisableCtrl(BOOL v_disable) {
    STATE_FUNC_START(_T("disable"), v_disable)
        if (v_disable == TRUE)
            Event(UIEvent(kWM_Disable));
        else
            Event(UIEvent(kWM_Active));
        STATE_FUNC_END
}

bool UIControl::VisibleCtrl(BOOL v_visible) {
    STATE_FUNC_START(_T("visible"), v_visible)
        if (v_visible == TRUE)
            Event(UIEvent(kWM_Visible));
        else
            Event(UIEvent(kWM_Invisible));
        STATE_FUNC_END
}

bool UIControl::AttachBgPaint(BOOL v_bg) {
    STATE_FUNC_START(_T("bgpaint"), v_bg)
        STATE_FUNC_END
}

void UIControl::SetAlpha(ALPHA v_alpha) {
    SetAttribute(_T("alpha"), UStr(v_alpha));
}

ALPHA UIControl::GetAlpha() const {
    return (ALPHA)GetAttribute(_T("alpha")).Str2LL();
}

void UIControl::SetBorderSize(long v_border) {
    SetAttribute(_T("bordersize"), UStr(v_border));
}

long UIControl::GetBorderSize() const {
    return (long)GetAttribute(_T("bordersize")).Str2LL();
}

void UIControl::SetBorderColor(LPCTSTR v_color) {
    SetAttribute(_T("bordercolor"), v_color);
}

UIColor UIControl::GetBorderColor() const {
    return UIColor(GetAttribute(_T("bordercolor")));
}

void UIControl::SetToolTip(LPCTSTR v_str) {
    SetAttribute(_T("tooltip"), UITranslateStr(v_str));
}

CUStr UIControl::GetToolTip() const {
    return GetAttribute(_T("tooltip"));
}

void UIControl::SetToolTipWidth(long v_width) {
    SetAttribute(_T("tooltipwidth"), UStr(v_width));
}

long UIControl::GetToolTipWidth() const {
    return (long)GetAttribute(_T("tooltipwidth")).Str2LL();
}

void UIControl::SetTransmouse(LPCTSTR v_str) {
    SetAttribute(_T("transmouse"), v_str);
}

CtrlTransmouse UIControl::GetTransmouse() const {
    UStr mode = GetAttribute(_T("transmouse"));
    if (mode == _T("all"))
        return kCT_All;
    else if (mode == _T("single"))
        return kCT_Single;
    else
        return kCT_None;
}

}   // namespace DuiMini
