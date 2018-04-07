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

bool UIRenderImage::Load(LPCTSTR v_path) {
    switch (UIRender::GetRenderMode()) {
    case kRM_GDIPlus:
        renderimg_.reset(new UIRenderImageGDIP());
        break;
    }
    return renderimg_->Load(v_path);
}

void* UIRenderImage::GetInterface() const {
    if (!renderimg_)
        return nullptr;
    return renderimg_->GetInterface();
}

long UIRenderImage::GetWidth() const {
    if (!renderimg_)
        return 0;
    return renderimg_->GetWidth();
}

long UIRenderImage::GetHeight() const {
    if (!renderimg_)
        return 0;
    return renderimg_->GetHeight();
}

////////////////////////////////////////

RenderMode UIRender::render_mode_ = kRM_GDIPlus;

UIRender::UIRender() {
    SelectRender(&render_);
}

UIRender::~UIRender() {}

bool UIRender::GlobalInit() {
    // Using an new object for global init
    shared_ptr<IUIRender> render = nullptr;
    SelectRender(&render);
    return render->GlobalInit();
}

bool UIRender::GlobalInit(RenderMode v_mode) {
    SetRenderMode(v_mode);
    return GlobalInit();
}

bool UIRender::GlobalRelease() {
    shared_ptr<IUIRender> render = nullptr;
    SelectRender(&render);
    return render->GlobalRelease();
}

void UIRender::SetRenderMode(RenderMode v_mode) {
    render_mode_ = v_mode;
}

RenderMode UIRender::GetRenderMode() {
    return render_mode_;
}

bool UIRender::Paint(UIWindow* v_wnd) {
    RENDER_CALL(render_->Paint(v_wnd));
}

bool UIRender::RedrawBackground() {
    RENDER_CALL(render_->RedrawBackground());
}

bool UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         ALPHA v_alpha/* = 255*/, ImageMode v_mode/* = kIM_Extrude*/) {
    if (!v_img)
        return false;
    RENDER_CALL(render_->DrawImage(v_img, v_destrect,
                                   UIRect(0, 0, v_img->GetWidth(),
                                          v_img->GetHeight()),
                                   v_alpha, v_mode));
}

bool UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         const UIRect& v_srcrect, ALPHA v_alpha/* = 255*/,
                         ImageMode v_mode/* = kIM_Extrude*/) {
    RENDER_CALL(render_->DrawImage(v_img, v_destrect, v_srcrect, v_alpha,
                                   v_mode));
}

bool UIRender::DrawString(LPCTSTR v_text, const UIFont &v_font,
                          const UIStringFormat &v_format,
                          const UIRect &v_rect) {
    RENDER_CALL(render_->DrawString(v_text, v_font, v_format, v_rect));
}

bool UIRender::DrawRect(const UIRect &v_rect, const UIColor &v_color,
                        long v_border) {
    RENDER_CALL(render_->DrawRect(v_rect, v_color, v_border));
}

bool UIRender::DrawFillRect(const UIRect &v_rect, const UIColor &v_color) {
    RENDER_CALL(render_->DrawFillRect(v_rect, v_color));
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
