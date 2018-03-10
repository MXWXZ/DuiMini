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
    STATE_FUNC_START(_T("resizable"), v_resizable)
        STATE_FUNC_END
}

void UIDialog::SetSizeBox(LPCTSTR v_sizestr) {
    SetAttribute(_T("sizebox"), v_sizestr);
    UStr tmp = v_sizestr;
    int seppos1 = tmp.Find(_T(","));
    SetAttribute(_T("sizebox_left"), tmp.Left(seppos1));
    int seppos2 = tmp.Find(_T(","), seppos1 + 1);
    SetAttribute(_T("sizebox_top"), tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1));
    int seppos3 = tmp.Find(_T(","), seppos2 + 1);
    SetAttribute(_T("sizebox_right"), tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1));
    SetAttribute(_T("sizebox_bottom"), tmp.Right(tmp.GetLength() - seppos3 - 1));
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
    SetWindowText(basewnd_->GetHWND(), v_title);
    SetAttribute(_T("title"), v_title);
}

bool UIDialog::ShowTaskBar(BOOL v_show/* = TRUE*/) {
    STATE_FUNC_START(_T("appwin"), v_show) {
        LONG style = GetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE);
        if (v_show == TRUE)
            style &= ~WS_EX_TOOLWINDOW;
        else
            style |= WS_EX_TOOLWINDOW;
        SetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE, style);
    }
    STATE_FUNC_END
}

void UIDialog::SetAlpha(ALPHA v_alpha) {
    SetAttribute(_T("alpha"), UStr(v_alpha));
}

ALPHA UIDialog::GetAlpha() const {
    return (ALPHA)(GetAttribute(_T("alpha")).Str2Int());
}

void UIDialog::SetMinWidth(long v_width) {
    SetAttribute(_T("minwidth"), UStr(v_width));
}

long UIDialog::GetMinWidth() const {
    return GetAttribute(_T("minwidth")).Str2Int();
}

void UIDialog::SetMaxWidth(long v_width) {
    SetAttribute(_T("maxwidth"), UStr(v_width));
}

long UIDialog::GetMaxWidth() const {
    return GetAttribute(_T("maxwidth")).Str2Int();
}

void UIDialog::SetMinHeight(long v_height) {
    SetAttribute(_T("minheight"), UStr(v_height));
}

long UIDialog::GetMinHeight() const {
    return GetAttribute(_T("minheight")).Str2Int();
}

void UIDialog::SetMaxHeight(long v_height) {
    SetAttribute(_T("maxheight"), UStr(v_height));
}

long UIDialog::GetMaxHeight() const {
    return GetAttribute(_T("maxheight")).Str2Int();
}

void UIDialog::AfterSetAttribute() {
    UIContainer::AfterSetAttribute();
    // Init dlg pos
    basewnd_->SetWindowPos(GetPos());
    SetSizeBox(GetSizeBox());           // Init size box
    if (!ShowTaskBar(STAY))
        ShowTaskBar(FALSE);
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
        int seppos1 = tmp.Find(_T(","));
        test.left = ParsePosStr(tmp.Left(seppos1), left, &tmprect);
        int seppos2 = tmp.Find(_T(","), seppos1 + 1);
        test.top = ParsePosStr(tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top, &tmprect);
        int seppos3 = tmp.Find(_T(","), seppos2 + 1);
        test.right = ParsePosStr(tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right, &tmprect);
        test.bottom = ParsePosStr(tmp.Right(tmp.GetLength() - seppos3 - 1), bottom, &tmprect);
        POINT pt = v_event.GetPos();
        if (!::PtInRect(&test.rect(), pt))
            break;

        ClientToScreen(basewnd_->GetHWND(), &pt);
        ReleaseCapture();
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
    SetTitle(GetAttrStr(GetTitle()));
    return UIContainer::OnLangChange(v_event);
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_DIALOG))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
