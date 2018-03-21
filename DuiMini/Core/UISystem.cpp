/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#include "stdafx.h"
#include "UISystem.h"

namespace DuiMini {
HINSTANCE UISystem::instance_ = NULL;
UIPtrArray UISystem::window_;

void UISystem::Init(HINSTANCE v_instance) {
    _tsetlocale(LC_ALL, _T(""));
    SetInstance(v_instance);
}

void UISystem::Cleanup() {
    UIRender::GlobalRelease();
}

void UISystem::Exit(const int v_code /*= 0*/) {
    Cleanup();
    exit(v_code);
}

void UISystem::SetInstance(HINSTANCE v_instance) {
    instance_ = v_instance;
}

HINSTANCE UISystem::GetInstance() {
    return instance_;
}

bool UISystem::ChangeSkin(SKINID v_id) {
    if (UIConfig::SetShownSkin(v_id)) {
        for (UINT it = 0; it < window_.GetSize(); ++it)
            ((UIWindow*)window_[it])->ChangeSkin(v_id);
        return true;
    }
    return false;
}

bool UISystem::ChangeLang(LANGID v_id) {
    if (UIConfig::SetShownLang(v_id)) {
        for (UINT it = 0; it < window_.GetSize(); ++it)
            ((UIWindow*)window_[it])->ChangeLang(v_id);
        return true;
    }
    return false;
}

bool UISystem::AddWindow(UIWindow* v_window) {
    return window_.Add(v_window);
}

UIWindow* UISystem::GetWindow(LPCTSTR v_classname) {
    TCHAR buf[260];
    for (UINT it = 0; it < window_.GetSize(); ++it) {
        GetClassName(((UIWindow*)window_[it])->GetHWND(), buf, 256);
        if (CmpStr(buf, v_classname))
            return (UIWindow*)window_[it];
    }
    return nullptr;
}

bool UISystem::RemoveWindow(UIWindow* v_window) {
    for (UINT it = 0; it < window_.GetSize(); ++it)
        if ((UIWindow*)window_[it] == v_window)
            return window_.Remove(it);
    return false;
}

void UISystem::RemoveAllWindow() {
    window_.Empty();
}

}   // namespace DuiMini
