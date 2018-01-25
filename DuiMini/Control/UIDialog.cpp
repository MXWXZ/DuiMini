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

bool UIDialog::ChangeBackground(LPCTSTR v_path) {
    delete bgimg_;
    bgimg_ = nullptr;
    int ret = LoadBackground(v_path);
    ret += basewnd_->GetRender()->RedrawBackground();
    return ret;
}

void UIDialog::DoPaintBackground(IUIRender* v_render) {
    v_render->DrawImage(bgimg_, 0, 0, GetAttribute(_T("width")).Str2Int(),
                        GetAttribute(_T("height")).Str2Int());
}

void UIDialog::BeforeSetAttribute() {
    SetAttribute(_T("background"), _T(""));
    SetAttribute(_T("title"), _T(""));
    SetAttribute(_T("appwin"), _T("1"));
}

void UIDialog::AfterSetAttribute() {
    ChangeBackground(GetAttrFile(_T("background")));
    UIContainer::AfterSetAttribute();
    basewnd_->SetWindowPos(GetPos());   // Init dlg pos
    if (GetAttribute(_T("appwin")) == _T("0"))
        basewnd_->ShowTaskBar(false);
    basewnd_->SetTitle(GetAttrStr(_T("title")));
}

// TODO
void UIDialog::OnChangeSkin() {
    ChangeBackground(GetAttrFile(_T("background")));
    UIContainer::OnChangeSkin();
}

void UIDialog::OnChangeLanguage() {
    basewnd_->SetTitle(GetAttrStr(_T("title")));
    UIContainer::OnChangeLanguage();
}

bool UIDialog::LoadBackground(LPCTSTR v_path) {
    if (!bgimg_) {
        bgimg_ = new UIRenderImage();
        return bgimg_->Load(v_path);
    } else {
        return false;
    }
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, _T("Dlg")))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
