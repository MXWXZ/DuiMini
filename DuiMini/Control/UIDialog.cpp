/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIDialog.h"

namespace DuiMini {
UIDialog::UIDialog() {}

UIDialog::~UIDialog() {
}

bool UIDialog::AllowWindowMove(BOOL v_movable/* = TRUE*/) {
    STATE_FUNC_START(_T("movable"), v_movable)
        STATE_FUNC_END
}

bool UIDialog::AllowWindowResize(BOOL v_resizable/* = TRUE*/) {
    STATE_FUNC_START(_T("resizable"), v_resizable) {
        if (!basewnd_)
            return false;
        LONG style = GetWindowLong(basewnd_->GetHWND(), GWL_STYLE);
        if (v_resizable == TRUE)
            style |= WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
        else
            style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME);
        SetWindowLong(basewnd_->GetHWND(), GWL_STYLE, style);
    }
    STATE_FUNC_END
}

void UIDialog::SetSizeBox(LPCTSTR v_sizestr) {
    SetAttribute(_T("sizebox"), v_sizestr);
    SetAttribute(_T("sizebox_left"), DivideStr(v_sizestr, 1));
    SetAttribute(_T("sizebox_top"), DivideStr(v_sizestr, 2));
    SetAttribute(_T("sizebox_right"), DivideStr(v_sizestr, 3));
    SetAttribute(_T("sizebox_bottom"), DivideStr(v_sizestr, 4));
}

CUStr UIDialog::GetSizeBox() const {
    return GetAttribute(_T("sizebox"));
}

void UIDialog::SetCaptionRect(LPCTSTR v_pos) {
    SetAttribute(_T("caption"), v_pos);
    caption_rect_ = ParsePosStr(v_pos, &GetPos());
}

UIRect UIDialog::GetCaptionRect() const {
    return caption_rect_;
}

CUStr UIDialog::GetTitle() const {
    return GetAttribute(_T("title"));
}

void UIDialog::SetTitle(LPCTSTR v_title) {
    if (!basewnd_)
        return;
    UStr str = UITranslateStr(v_title);
    SetWindowText(basewnd_->GetHWND(), str);
    SetAttribute(_T("title"), str);
}

bool UIDialog::ShowTaskBar(BOOL v_show/* = TRUE*/) {
    STATE_FUNC_START(_T("appwin"), v_show) {
        if (!basewnd_)
            return false;
        LONG style = GetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE);
        if (v_show == TRUE) {
            style &= ~WS_EX_TOOLWINDOW;
            style |= WS_EX_APPWINDOW;
        } else {
            style &= ~WS_EX_APPWINDOW;
            style |= WS_EX_TOOLWINDOW;
        }
        SetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE, style);
    }
    STATE_FUNC_END
}

void UIDialog::SetAlpha(ALPHA v_alpha) {
    SetAttribute(_T("alpha"), UStr(v_alpha));
}

ALPHA UIDialog::GetAlpha() const {
    return (ALPHA)GetAttribute(_T("alpha")).Str2LL();
}

void UIDialog::SetMinWidth(long v_width) {
    SetAttribute(_T("minwidth"), UStr(v_width));
}

long UIDialog::GetMinWidth() const {
    return GetAttribute(_T("minwidth")).Str2LL();
}

void UIDialog::SetMaxWidth(long v_width) {
    SetAttribute(_T("maxwidth"), UStr(v_width));
}

long UIDialog::GetMaxWidth() const {
    return GetAttribute(_T("maxwidth")).Str2LL();
}

void UIDialog::SetMinHeight(long v_height) {
    SetAttribute(_T("minheight"), UStr(v_height));
}

long UIDialog::GetMinHeight() const {
    return GetAttribute(_T("minheight")).Str2LL();
}

void UIDialog::SetMaxHeight(long v_height) {
    SetAttribute(_T("maxheight"), UStr(v_height));
}

long UIDialog::GetMaxHeight() const {
    return GetAttribute(_T("maxheight")).Str2LL();
}

void UIDialog::AfterSetAttribute() {
    UIContainer::AfterSetAttribute();
    if (!basewnd_)
        return;
    // Init dlg pos
    basewnd_->SetWindowPos(GetPos());
    SetSizeBox(GetSizeBox());           // Init size box
    if (!ShowTaskBar(STAY))
        ShowTaskBar(FALSE);
    INIT_STATE(AllowWindowMove);
    INIT_STATE(AllowWindowResize);
}

bool UIDialog::Event(const UIEvent& v_event) {
    if (!UIContainer::Event(v_event))
        return false;
    switch (v_event) {
    case kWM_LButtonDown:
    {
        // move window
        if (!AllowWindowMove(STAY))
            break;
        UIRect test, tmprect = GetPos();
        UStr tmp = GetAttribute(_T("caption"));
        test.left   = ParsePosStr(DivideStr(tmp, 1), left,   &tmprect);
        test.top    = ParsePosStr(DivideStr(tmp, 2), top,    &tmprect);
        test.right  = ParsePosStr(DivideStr(tmp, 3), right,  &tmprect);
        test.bottom = ParsePosStr(DivideStr(tmp, 4), bottom, &tmprect);

        POINT pt = v_event.GetPos();
        if (!::PtInRect(&test.rect(), pt))
            break;

        ReleaseCapture();   // must do this

        basewnd_->SendWindowMessage(WM_NCLBUTTONDOWN, HTCAPTION,
                                    v_event.GetLParam());
        basewnd_->SendWindowMessage(WM_LBUTTONUP, v_event.GetWParam(),
                                    v_event.GetLParam());
        break;
    }
    }
    return true;
}

bool UIDialog::OnLangChange(const UIEvent& v_event) {
    SetTitle(GetTitle());
    return UIContainer::OnLangChange(v_event);
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_DIALOG))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
