/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include <cstdlib>
#include <locale.h>
#include "Core/UISystem.h"

namespace DuiMini {
void UISystem::Init() { setlocale(LC_ALL, ""); }

void UISystem::Cleanup() {}

void UISystem::Exit(const int code /*= 0*/) {
    Cleanup();
    exit(code);
}
}  // namespace DuiMini
