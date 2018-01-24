/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "UISystem.h"

namespace DuiMini {
HINSTANCE UISystem::instance_ = NULL;

void UISystem::Init(HINSTANCE v_instance) {
    _tsetlocale(LC_ALL, _T(""));
    SetInstance(v_instance);
}

void UISystem::Cleanup() {
    UIRender::Release();
}

void UISystem::Exit(const int v_code /*= 0*/) {
    Cleanup();
    exit(v_code);
}

HINSTANCE UISystem::SetInstance(HINSTANCE v_instance) {
    return instance_ = v_instance;
}

HINSTANCE UISystem::GetInstance() {
    return instance_;
}
}   // namespace DuiMini
