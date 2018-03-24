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

UIRenderImage::~UIRenderImage() {
    Release();
}

bool UIRenderImage::Load(LPCTSTR v_path) {
    switch (UIRender::GetRenderMode()) {
    case kRM_GDIPlus:
        renderimg_ = new UIRenderImageGDIP();
        break;
    }
    bool ret = renderimg_->Load(v_path);
    if (!ret)
        UIHandleError();
    return ret;
}

bool UIRenderImage::Release() {
    if (!renderimg_)
        return false;
    bool ret = renderimg_->Release();
    if (!ret)
        UIHandleError();
    renderimg_ = nullptr;
    return ret;
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

UIRender::~UIRender() {
    delete render_;
    render_ = nullptr;
}

bool UIRender::GlobalInit() {
    // Using an new object for global init
    IUIRender *render = nullptr;
    SelectRender(&render);
    bool ret = render->GlobalInit();
    if (!ret)
        UIHandleError();
    delete render;
    render = nullptr;
    return ret;
}

bool UIRender::GlobalInit(RenderMode v_mode) {
    SetRenderMode(v_mode);
    return GlobalInit();
}

bool UIRender::GlobalRelease() {
    IUIRender *render = nullptr;
    SelectRender(&render);
    bool ret = render->GlobalRelease();
    if (!ret)
        UIHandleError();
    delete render;
    render = nullptr;
    return ret;
}

void UIRender::SetRenderMode(RenderMode v_mode) {
    render_mode_ = v_mode;
}

RenderMode UIRender::GetRenderMode() {
    return render_mode_;
}

bool UIRender::Paint(UIWindow* v_wnd) {
    RENDER_CALL_START
        render_->Paint(v_wnd);
    RENDER_CALL_END
}

bool UIRender::RedrawBackground() {
    RENDER_CALL_START
        render_->RedrawBackground();
    RENDER_CALL_END
}

bool UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         ALPHA v_alpha/* = 255*/) {
    if (!v_img)
        return false;
    RENDER_CALL_START
        render_->DrawImage(v_img, v_destrect,
                           UIRect(0, 0, v_img->GetWidth(),
                                  v_img->GetHeight()), v_alpha);
    RENDER_CALL_END
}

bool UIRender::DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                         const UIRect& v_srcrect, ALPHA v_alpha/* = 255*/) {
    RENDER_CALL_START
        render_->DrawImage(v_img, v_destrect, v_srcrect, v_alpha);
    RENDER_CALL_END
}

bool UIRender::DrawString(LPCTSTR v_text, const UIFont &v_font,
                          const UIStringFormat &v_format,
                          const UIRect &v_rect) {
    RENDER_CALL_START
        render_->DrawString(v_text, v_font, v_format, v_rect);
    RENDER_CALL_END
}

bool UIRender::DrawRect(const UIRect &v_rect, const UIColor &v_color,
                        BORDER_SIZE v_border) {
    RENDER_CALL_START
        render_->DrawRect(v_rect, v_color, v_border);
    RENDER_CALL_END
}

bool UIRender::DrawFillRect(const UIRect &v_rect, const UIColor &v_color) {
    RENDER_CALL_START
        render_->DrawFillRect(v_rect, v_color);
    RENDER_CALL_END
}

IUIRender* UIRender::SelectRender(IUIRender** v_pointer) {
    switch (render_mode_) {
    case kRM_GDIPlus:
        *v_pointer = new UIRenderGDIP();
        break;
    }
    return *v_pointer;
}
}    // namespace DuiMini
