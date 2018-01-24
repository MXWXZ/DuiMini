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

UIRenderImage::~UIRenderImage() {}

bool UIRenderImage::Load(LPCTSTR v_path) {
    switch (UIRender::GetRenderMode()) {
    case kGDIPlus:
        renderimg_ = new UIRenderImageGDIP();
        break;
    }
    return renderimg_->Load(v_path);
}

bool UIRenderImage::Release() {
    bool ret = renderimg_->Release();
    renderimg_ = nullptr;
    return ret;
}

void* UIRenderImage::GetInterface() {
    return renderimg_->GetInterface();
}

////////////////////////////////////////

RenderMode UIRender::render_mode_ = kGDIPlus;

UIRender::UIRender() {
    SelectRender(&render_);
}

UIRender::UIRender(UIWindow * v_parent)
    :UIRender() {
    SetParent(v_parent);
}

UIRender::~UIRender() {
    delete render_;
    render_ = nullptr;
}

bool UIRender::Init() {
    // Using an new object for global init
    IUIRender *render = nullptr;
    SelectRender(&render);
    bool ret = render->Init();
    delete render;
    render = nullptr;
    return ret;
}

bool UIRender::Init(RenderMode v_mode) {
    SetRenderMode(v_mode);
    Init();
    return true;
}

bool UIRender::Release() {
    IUIRender *render = nullptr;
    SelectRender(&render);
    bool ret = render->Release();
    delete render;
    render = nullptr;
    return ret;
}

RenderMode UIRender::SetRenderMode(RenderMode v_mode) {
    render_mode_ = v_mode;
    return render_mode_;
}

RenderMode UIRender::GetRenderMode() {
    return render_mode_;
}

UIWindow* UIRender::SetParent(UIWindow * v_parent) {
    if (!render_)
        return nullptr;
    render_->parent_ = v_parent;
    return render_->parent_;
}

bool UIRender::Paint() {
    if (!render_)
        return false;
    return render_->Paint();
}

IUIRender* UIRender::SelectRender(IUIRender** v_pointer) {
    switch (render_mode_) {
    case kGDIPlus:
        *v_pointer = new UIRenderGDIP();
        break;
    }
    return *v_pointer;
}
}    // namespace DuiMini
