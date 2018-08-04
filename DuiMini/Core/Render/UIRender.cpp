/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#include "stdafx.h"
#include "UIRender.h"
#include "UIRenderGDIP.h"

namespace DuiMini {
UIRenderImage::UIRenderImage() {}

UIRenderImage::UIRenderImage(LPCTSTR v_path) {
    Load(v_path);
}

UIRenderImage::~UIRenderImage() {}

void UIRenderImage::Load(LPCTSTR v_path) {
    switch (UIRender::GetRenderMode()) {
    case kRM_GDIPlus:
        renderimg_.reset(new UIRenderImageGDIP());
        break;
    }
    renderimg_->Load(v_path);
}

void* UIRenderImage::GetInterface() const {
    assert(renderimg_);
    return renderimg_->GetInterface();
}

UINT UIRenderImage::GetWidth() const {
    assert(renderimg_);
    return renderimg_->GetWidth();
}

UINT UIRenderImage::GetHeight() const {
    assert(renderimg_);
    return renderimg_->GetHeight();
}

////////////////////////////////////////

RenderMode UIRender::render_mode_ = kRM_GDIPlus;

UIRender::UIRender() {
    SelectRender(&render_);
}

UIRender::~UIRender() {}

void UIRender::GlobalInit() {
    // Using an new object for global init
    shared_ptr<IUIRender> render = nullptr;
    SelectRender(&render);
    render->GlobalInit();
}

void UIRender::GlobalInit(RenderMode v_mode) {
    SetRenderMode(v_mode);
    GlobalInit();
}

void UIRender::GlobalRelease() {
    shared_ptr<IUIRender> render = nullptr;
    SelectRender(&render);
    render->GlobalRelease();
}

void UIRender::Paint(UIWindow* v_wnd) {
    assert(render_);
    render_->Paint(v_wnd);
}

void UIRender::RedrawBackground() {
    assert(render_);
    render_->RedrawBackground();
}

void UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         ALPHA v_alpha/* = 255*/, ImageMode v_mode/* = kIM_Extrude*/) {
    assert(render_ && v_img);
    render_->DrawImage(v_img, v_destrect,
                       UIRect(0, 0, v_img->GetWidth(),
                              v_img->GetHeight()),
                       v_alpha, v_mode);
}

void UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         const UIRect& v_srcrect, ALPHA v_alpha/* = 255*/,
                         ImageMode v_mode/* = kIM_Extrude*/) {
    assert(render_);
    render_->DrawImage(v_img, v_destrect, v_srcrect, v_alpha, v_mode);
}

void UIRender::DrawString(LPCTSTR v_text, const UIFont &v_font,
                          const UIStringFormat &v_format,
                          const UIRect &v_rect) {
    assert(render_);
    render_->DrawString(v_text, v_font, v_format, v_rect);
}

void UIRender::DrawRect(const UIRect &v_rect, const UIColor &v_color,
                        long v_border) {
    assert(render_);
    render_->DrawRect(v_rect, v_color, v_border);
}

void UIRender::DrawFillRect(const UIRect &v_rect, const UIColor &v_color) {
    assert(render_);
    render_->DrawFillRect(v_rect, v_color);
}

IUIRender* UIRender::SelectRender(shared_ptr<IUIRender>* v_pointer) {
    switch (render_mode_) {
    case kRM_GDIPlus:
        (*v_pointer).reset(new UIRenderGDIP());
        break;
    }
    return (*v_pointer).get();
}
}    // namespace DuiMini
