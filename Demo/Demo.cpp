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
#include "Demo.h"

#pragma comment(lib, "Bin/DuiMini.lib")

using namespace DuiMini;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPTSTR    lpCmdLine,
                      _In_ int       nCmdShow) {
    UISystem::Init(hInstance);      // Initialize UI library
    UISystem::LoadConfig();

    UISystem::Cleanup();            // Clean up UI library
    return 0;
}
