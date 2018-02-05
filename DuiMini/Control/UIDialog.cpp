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
    delete bgimg_;
    bgimg_ = nullptr;
}

bool UIDialog::SetBackground(LPCTSTR v_path) {
    UIRenderImage* tmp = new UIRenderImage();
    if (tmp->Load(v_path)) {
        delete bgimg_;
        bgimg_ = tmp;
        SetAttribute(_T("background"), v_path);
        // once failed, bgimg_ is still the new one(only redraw failed)
        return basewnd_->GetRender()->RedrawBackground();
    }
    delete tmp;
    tmp = nullptr;
    return false;
}

void UIDialog::PaintBackground() {
    basewnd_->GetRender()->DrawImage(bgimg_, 0, 0,
                                     GetAttribute(_T("width")).Str2Int(),
                                     GetAttribute(_T("height")).Str2Int());
}

void UIDialog::BeforeSetAttribute() {
    SetAttribute(_T("background"), _T(""));
    SetAttribute(_T("title"), _T(""));
    SetAttribute(_T("appwin"), _T("1"));
    SetAttribute(_T("caption"), _T("0,0,-0,-0"));
    SetAttribute(_T("movable"), _T("1"));
    SetAttribute(_T("sizebox"), _T("0,0,0,0"));
    SetAttribute(_T("resizable"), _T("0"));
    UIContainer::BeforeSetAttribute();
}

void UIDialog::AfterSetAttribute() {
    UIContainer::AfterSetAttribute();
    basewnd_->SetWindowPos(GetPos());   // Init dlg pos
    basewnd_->SetSizeBox(GetAttribute(_T("sizebox")));
    if (GetAttribute(_T("appwin")) == _T("0"))
        basewnd_->ShowTaskBar(false);
}

void UIDialog::Event(WindowMessage v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    switch (v_msg) {
    case kWM_LButtonDown:
    {
        // move window
        if (!GetAttribute(_T("movable")).Str2Int())
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
        basewnd_->SendWindowMessage(WM_NCLBUTTONDOWN, HTCAPTION,
                                    MAKELPARAM(pt.x, pt.y));
        basewnd_->SendWindowMessage(WM_LBUTTONUP, v_wparam, v_lparam);
        break;
    }
    }
}

// TODO
void UIDialog::LoadResAttr() {
    SetBackground(GetAttrFile(_T("background")));
    UIContainer::LoadResAttr();
}

void UIDialog::LoadTextAttr() {
    basewnd_->SetTitle(GetAttrStr(_T("title")));
    UIContainer::LoadTextAttr();
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_DIALOG))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
