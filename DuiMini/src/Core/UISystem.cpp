/**
 * @author  MXWXZ
 * @date    2019/03/09
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
