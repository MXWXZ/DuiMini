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
#include "DuiMini.h"
#include "UISystem.h"

namespace DuiMini {
// Initialize static member
HINSTANCE UISystem::instance_;

void UISystem::Init(HINSTANCE inst) {
    _tsetlocale(LC_ALL, _T(""));
    SetInstance(inst);
}

void UISystem::Cleanup() {
}

void UISystem::Exit(const int code /*= 0*/) {
    Cleanup();
    exit(code);
}

bool DuiMini::UISystem::LoadConfig(LPCTSTR path/* = DEFAULT_RESFILE*/) {
    // BYTE* buf = UIResource::GetFile(path);
   //  if (buf != NULL) {
         //xmldoc doc;
         //doc.parse<0>(buf);
   //  }
     //UIResource::FreeBuffer(buf);
    return false;
}

}   // namespace DuiMini
