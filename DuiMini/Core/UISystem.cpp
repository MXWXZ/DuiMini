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

bool UISystem::ChangeSkin(CFGID v_id) {
    if (UIConfig::SetShownSkin(v_id)) {
        for (auto& i : window_)
            ((UIWindow*)i)->ChangeSkin(v_id);
        return true;
    }
    return false;
}

bool UISystem::ChangeLang(CFGID v_id) {
    if (UIConfig::SetShownLang(v_id)) {
        for (auto& i : window_)
            ((UIWindow*)i)->ChangeLang(v_id);
        return true;
    }
    return false;
}

void UISystem::AddWindow(UIWindow* v_window) {
    window_.push_back(v_window);
}

UIWindow* UISystem::GetWindow(LPCTSTR v_classname) {
    TCHAR buf[260];
    for (auto& i : window_) {
        GetClassName(((UIWindow*)i)->GetHWND(), buf, 256);
        if (CmpStr(buf, v_classname))
            return (UIWindow*)i;
    }
    return nullptr;
}

bool UISystem::RemoveWindow(UIWindow* v_window) {
    auto i = std::find(window_.begin(), window_.end(), (LPVOID)v_window);
    if (i != window_.end()) {
        window_.erase(i);
        return true;
    }
    return false;
}

void UISystem::RemoveAllWindow() {
    window_.clear();
}

}   // namespace DuiMini
