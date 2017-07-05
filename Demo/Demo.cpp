/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "Demo.h"

#pragma comment(lib, "Bin/DuiMini.lib")

using namespace DuiMini;    // NOLINT

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPWSTR    lpCmdLine,
                       _In_ int       nCmdShow) {
    UISystem::Init(hInstance);


    UISystem::Cleanup();
    return 0;
}
