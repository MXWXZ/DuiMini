/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIImage.h"

namespace DuiMini {
UIImage::UIImage() {}

UIImage::~UIImage() {
    UIResource::ReleaseRes(img_);
    img_ = nullptr;
}

bool UIImage::SetFile(LPCTSTR v_path) {
    UStr path = UIGetStrPath(v_path);
    UIRenderImage* tmp = (UIRenderImage*)UIResource::LoadRes(kFT_PIC, path);
    if (tmp) {
        UIResource::ReleaseRes(img_);
        img_ = tmp;
        SetAttribute(_T("file"), path);
        return true;
    }
    UIResource::ReleaseRes(tmp);
    tmp = nullptr;
    return false;
}

CUStr UIImage::GetFile() const {
    return GetAttribute(_T("file"));
}

void UIImage::SetMargin(LPCTSTR v_pos) {
    SetAttribute(_T("margin"), v_pos);
}

CUStr UIImage::GetMargin() const {
    return GetAttribute(_T("margin"));
}

void UIImage::SetMode(LPCTSTR v_mode) {
    SetAttribute(_T("mode"), v_mode);
}

ImageMode UIImage::GetMode() const {
    UStr mode = GetAttribute(_T("mode"));
    if (mode == _T("extrude"))
        return kIM_Extrude;
    else
        return kIM_Tile;
}

LPVOID UIImage::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_IMAGE))
        return this;
    return UIControl::GetInterface(v_name);
}

void UIImage::Paint(bool v_background/* = false*/) {
    if (!img_ || !basewnd_)
        return;
    UIRect tmprect(0, 0, img_->GetWidth(), img_->GetHeight());
    if (GetMode() == kIM_Extrude)
        PaintMarginImg(tmprect);
    else
        basewnd_->GetRender()->DrawImage(img_, rect_, GetAlpha(), kIM_Tile);
    UIControl::Paint(v_background);
}

void UIImage::PaintMarginImg(UIRect &srcrect) {
    UIRect extrude_rect = ParsePosStr(GetMargin(), &srcrect);
    long margin_left = extrude_rect.left - srcrect.left;
    long margin_right = srcrect.right - extrude_rect.right;
    long margin_top = extrude_rect.top - srcrect.top;
    long margin_bottom = srcrect.bottom - extrude_rect.bottom;
    ALPHA alpha = GetAlpha();

    // LT
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left, rect_.top,
                                                  rect_.left + margin_left,
                                                  rect_.top + margin_top),
                                     UIRect(srcrect.left, srcrect.top,
                                            extrude_rect.left, extrude_rect.top),
                                     alpha);
    // RT
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - margin_right,
                                                  rect_.top, rect_.right,
                                                  rect_.top + margin_top),
                                     UIRect(extrude_rect.right,
                                            srcrect.top, srcrect.right,
                                            extrude_rect.top),
                                     alpha);
    // LB
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left,
                                                  rect_.bottom - margin_bottom,
                                                  rect_.left + margin_left,
                                                  rect_.bottom),
                                     UIRect(srcrect.left, extrude_rect.bottom,
                                            extrude_rect.left, srcrect.bottom),
                                     alpha);
    // RB
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - margin_right,
                                                  rect_.bottom - margin_bottom,
                                                  rect_.right, rect_.bottom),
                                     UIRect(extrude_rect.right,
                                            extrude_rect.bottom,
                                            srcrect.right, srcrect.bottom),
                                     alpha);
    // Left
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left,
                                                  rect_.top + margin_top,
                                                  rect_.left + margin_left,
                                                  rect_.bottom - margin_bottom),
                                     UIRect(srcrect.left, extrude_rect.top,
                                            extrude_rect.left,
                                            extrude_rect.bottom),
                                     alpha);
    // Top
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + margin_left,
                                                  rect_.top,
                                                  rect_.right - margin_right,
                                                  rect_.top + margin_top),
                                     UIRect(extrude_rect.left, srcrect.top,
                                            extrude_rect.right,
                                            extrude_rect.top),
                                     alpha);
    // Right
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - margin_right,
                                                  rect_.top + margin_top,
                                                  rect_.right,
                                                  rect_.bottom - margin_bottom),
                                     UIRect(extrude_rect.right,
                                            extrude_rect.top, srcrect.right,
                                            extrude_rect.bottom),
                                     alpha);
    // Bottom
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + margin_left,
                                                  rect_.bottom - margin_bottom,
                                                  rect_.right - margin_right,
                                                  rect_.bottom),
                                     UIRect(extrude_rect.left,
                                            extrude_rect.bottom,
                                            extrude_rect.right,
                                            srcrect.bottom),
                                     alpha);
    // Center
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + margin_left,
                                                  rect_.top + margin_top,
                                                  rect_.right - margin_right,
                                                  rect_.bottom - margin_bottom),
                                     UIRect(extrude_rect.left, extrude_rect.top,
                                            extrude_rect.right,
                                            extrude_rect.bottom),
                                     alpha);
}

bool UIImage::OnSkinChange(const UIEvent& v_event) {
    SetFile(GetFile());
    return UIControl::OnSkinChange(v_event);
}

}   // namespace DuiMini
