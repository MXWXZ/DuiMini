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

UIDialog::~UIDialog() {}

void UIDialog::DoPaintBackground(IUIRender* v_render) {
    v_render->DrawImage(bgimg_, 0, 0, GetAttribute(_T("width")).Str2Int(),
                        GetAttribute(_T("height")).Str2Int());
}

void UIDialog::AfterSetAttribute() {
    LoadBackground();
    basewnd_->SetWindowPos(NULL, NULL, NULL,
                           GetAttribute(_T("width")).Str2Int(),
                           GetAttribute(_T("height")).Str2Int(),
                           SWP_NOMOVE | SWP_NOZORDER);
    UIContainer::AfterSetAttribute();
}

void UIDialog::LoadBackground() {
    if (!bgimg_) {
        bgimg_ = new UIRenderImage();
        bgimg_->Load(GetAttrFile(_T("background")));
    }
}

LPVOID UIDialog::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, _T("Dlg")))
        return this;
    return UIContainer::GetInterface(v_name);
}
}   // namespace DuiMini
