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
    bool ret = GetAttribute(_T("movable")).Str2Int();
    if (v_movable >= 0)
        SetAttribute(_T("movable"), UStr(v_movable));
    return ret;
}

bool UIDialog::AllowWindowResize(BOOL v_resizable/* = TRUE*/) {
    bool ret = GetAttribute(_T("resizable")).Str2Int();
    if (v_resizable >= 0)
        SetAttribute(_T("resizable"), UStr(v_resizable));
    return ret;
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
    UStr tmp = v_pos;
    int seppos1 = tmp.Find(_T(","));
    caption_rect_.left = GetPosFromStr(tmp.Left(seppos1), left, this);
    int seppos2 = tmp.Find(_T(","), seppos1 + 1);
    caption_rect_.top = GetPosFromStr(tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top, this);
    int seppos3 = tmp.Find(_T(","), seppos2 + 1);
    caption_rect_.right = GetPosFromStr(tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right, this);
    caption_rect_.bottom = GetPosFromStr(tmp.Right(tmp.GetLength() - seppos3 - 1), bottom, this);
}

RECT UIDialog::GetCaptionRect() const {
    return caption_rect_;
}

CUStr UIDialog::GetTitle() const {
    return GetAttribute(_T("title"));
}

void UIDialog::SetTitle(LPCTSTR v_title) {
    SetWindowText(basewnd_->GetHWND(), v_title);
    SetAttribute(_T("title"), v_title);
}

CUStr UIDialog::GetBackground() const {
    return GetAttribute(_T("background"));
}

bool UIDialog::SetBackground(LPCTSTR v_path) {
    if (bgimg_->SetFile(v_path)) {
        SetAttribute(_T("background"), v_path);
        return basewnd_->GetRender()->RedrawBackground();
    }
    return false;
}

bool UIDialog::ShowTaskBar(BOOL v_show/* = TRUE*/) {
    bool ret = GetAttribute(_T("appwin")).Str2Int();
    if (v_show >= 0) {
        LONG style = GetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE);
        if (v_show == TRUE)
            style &= ~WS_EX_TOOLWINDOW;
        else
            style |= WS_EX_TOOLWINDOW;
        SetWindowLong(basewnd_->GetHWND(), GWL_EXSTYLE, style);
        SetAttribute(_T("appwin"), UStr(v_show));
    }
    return ret;
}

void UIDialog::SetBGAlpha(ALPHA v_alpha) {
    SetAttribute(_T("bgalpha"), UStr(v_alpha));
}

void UIDialog::SetAlpha(ALPHA v_alpha) {
    SetAttribute(_T("alpha"), UStr(v_alpha));
}

ALPHA UIDialog::GetBGAlpha() const {
    return (ALPHA)(GetAttribute(_T("bgalpha")).Str2Int());
}

ALPHA UIDialog::GetAlpha() const {
    return (ALPHA)(GetAttribute(_T("alpha")).Str2Int());
}

RECT UIDialog::PaintBackground() {
    RECT tmp = bgimg_->GetPos();
    bgimg_->Paint();
    return tmp;
}

void UIDialog::AfterSetAttribute() {
    // Init ctrl
    if (bgimg_)
        Remove(bgimg_);
    bgimg_ = new UIImage;
    basewnd_->CreateControl(bgimg_, this);
    bgimg_->SetAttribute(_T("pos"), _T("0,0,-0,-0"));
    bgimg_->SetAttribute(_T("file"), GetBackground());
    bgimg_->SetIndependent(FALSE);
    basewnd_->FinishCreateControl(bgimg_);

    UIContainer::AfterSetAttribute();
    basewnd_->SetWindowPos(GetPos());   // Init dlg pos
    SetSizeBox(GetSizeBox());           // Init size box
    if (!ShowTaskBar(-1))
        ShowTaskBar(FALSE);
}

bool UIDialog::Event(WindowMessage v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    if (!UIContainer::Event(v_msg, v_wparam, v_lparam))
        return false;
    switch (v_msg) {
    case kWM_LButtonDown:
    {
        // move window
        if (!AllowWindowMove(-1))
            break;
        RECT test;
        UStr tmp = GetAttribute(_T("caption"));
        int seppos1 = tmp.Find(_T(","));
        test.left = GetPosFromStr(tmp.Left(seppos1), left, this);
        int seppos2 = tmp.Find(_T(","), seppos1 + 1);
        test.top = GetPosFromStr(tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1), top, this);
        int seppos3 = tmp.Find(_T(","), seppos2 + 1);
        test.right = GetPosFromStr(tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1), right, this);
        test.bottom = GetPosFromStr(tmp.Right(tmp.GetLength() - seppos3 - 1), bottom, this);
        POINT pt;
        pt.x = GET_X_LPARAM(v_lparam);
        pt.y = GET_Y_LPARAM(v_lparam);
        if (!::PtInRect(&test, pt))
            break;

        ClientToScreen(basewnd_->GetHWND(), &pt);
        ReleaseCapture();
        basewnd_->SendWindowMessage(WM_NCLBUTTONDOWN, HTCAPTION,
                                    MAKELPARAM(pt.x, pt.y));
        basewnd_->SendWindowMessage(WM_LBUTTONUP, v_wparam, v_lparam);
        break;
    }
    }
    return true;
}

void UIDialog::OnSkinChange(SKINID v_former, SKINID v_new) {
    SetBackground(GetAttrPath(GetBackground()));
    UIContainer::OnSkinChange(v_former, v_new);
}

void UIDialog::OnLangChange(LANGID v_former, LANGID v_new) {
    SetTitle(GetAttrStr(GetTitle()));
    UIContainer::OnLangChange(v_former, v_new);
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_DIALOG))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
