/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/19
 *
 * @Description:
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
    if (!render_)
        return false;
    bool ret = render_->Paint(v_wnd);
    if (!ret)
        UIHandleError();
    return ret;
}

bool UIRender::RedrawBackground() {
    if (!render_)
        return false;
    bool ret = render_->RedrawBackground();
    if (!ret)
        UIHandleError();
    return ret;
}

bool UIRender::DrawImage(UIRenderImage * v_img, int v_left, int v_top, int v_width, int v_height) {
    if (!render_)
        return false;
    bool ret = render_->DrawImage(v_img, v_left, v_top, v_width, v_height);
    if (!ret)
        UIHandleError();
    return ret;
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
