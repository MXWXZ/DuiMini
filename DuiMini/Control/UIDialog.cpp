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
    delete bgimg_;
    bgimg_ = nullptr;
    bgimg_ = new UIRenderImage();
    int ret = bgimg_->Load(v_path);
    ret += basewnd_->GetRender()->RedrawBackground();
    return ret;
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
    if (CmpStr(v_name, _T("dlg")))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
