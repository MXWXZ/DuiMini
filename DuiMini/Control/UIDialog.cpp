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
    UIContainer::BeforeSetAttribute();
}

void UIDialog::AfterSetAttribute() {
    UIContainer::AfterSetAttribute();
    basewnd_->SetWindowPos(GetPos());   // Init dlg pos
    if (GetAttribute(_T("appwin")) == _T("0"))
        basewnd_->ShowTaskBar(false);
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
