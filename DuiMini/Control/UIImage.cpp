/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/01/28
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIImage.h"

namespace DuiMini {
UIImage::UIImage() {}

UIImage::~UIImage() {
    delete img_;
    img_ = nullptr;
}

bool UIImage::SetFile(LPCTSTR v_path) {
    UIRenderImage* tmp = new UIRenderImage();
    if (tmp->Load(v_path)) {
        delete img_;
        img_ = tmp;
        SetAttribute(_T("file"), v_path);
        return true;
    }
    delete tmp;
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

LPVOID UIImage::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_IMAGE))
        return this;
    return UIControl::GetInterface(v_name);
}

void UIImage::Paint(bool v_background/* = false*/) {
    long src_width = img_->GetWidth();
    long src_height = img_->GetHeight();
    long width = rect_.width();
    long height = rect_.height();
    UIRect tmprect(0, 0, src_width, src_height);
    UIRect extrude_rect = ParsePosStr(GetMargin(), &tmprect);
    long width_left = extrude_rect.left;
    long width_right = src_width - extrude_rect.right;
    long height_top = extrude_rect.top;
    long height_bottom = src_height - extrude_rect.bottom;

    // LT
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left, rect_.top,
                                                  rect_.left + width_left,
                                                  rect_.top + height_top),
                                     UIRect(0, 0, width_left, height_top));
    // RT
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - width_right,
                                                  rect_.top,
                                                  rect_.right,
                                                  rect_.top + height_top),
                                     UIRect(src_width - width_right,
                                            0, src_width, height_top));
    // LB
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left,
                                                  rect_.bottom - height_bottom,
                                                  rect_.left + width_left,
                                                  rect_.bottom),
                                     UIRect(0, src_height - height_bottom,
                                            width_left, src_height));
    // RB
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - width_right,
                                                  rect_.bottom - height_bottom,
                                                  rect_.right, rect_.bottom),
                                     UIRect(src_width - width_right,
                                            src_height - height_bottom,
                                            src_width, src_height));
    // Left
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left,
                                                  rect_.top + height_top,
                                                  width_left,
                                                  rect_.bottom - height_bottom),
                                     UIRect(0, height_top, width_left,
                                            src_height - height_bottom));
    // Top
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + width_left,
                                                  rect_.top,
                                                  rect_.right - width_right,
                                                  rect_.top + height_top),
                                     UIRect(width_left, 0,
                                            src_width - width_right,
                                            height_top));
    // Right
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.right - width_right,
                                                  rect_.top + height_top,
                                                  rect_.right,
                                                  rect_.bottom - height_bottom),
                                     UIRect(src_width - width_right,
                                            height_top, src_width,
                                            src_height - height_bottom));
    // Bottom
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + width_left,
                                                  rect_.bottom - height_bottom,
                                                  rect_.right - width_right,
                                                  rect_.bottom),
                                     UIRect(width_left,
                                            src_height - height_bottom,
                                            src_width - width_right,
                                            src_height));
    // Center
    basewnd_->GetRender()->DrawImage(img_, UIRect(rect_.left + width_left,
                                                  rect_.top + height_top,
                                                  rect_.right - width_right,
                                                  rect_.bottom - height_bottom),
                                     UIRect(width_left, height_top,
                                            src_width - width_right,
                                            src_height - height_bottom));
}

bool UIImage::OnSkinChange(const UIEvent& v_event) {
    SetFile(GetAttrPath(GetFile()));
    return UIControl::OnSkinChange(v_event);
}

}   // namespace DuiMini
