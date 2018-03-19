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
#include "Demo.h"
#include "MainDlg.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPTSTR    lpCmdLine,
                      _In_ int       nCmdShow) {
    UISystem::Init(hInstance);      // Initialize UI library
    /* [option]Set Res Type
    UIResource::SetResType(...);
    UIResource::SetResInfo(...);
    */
    UIRecLog::SetLogLevel(kRL_Release);     // [option]Set log level
    // UIRecLog::SetLogFilePath(...);       // [option]Set logfile path
    UIRender::GlobalInit();         // Init render
    UIConfig::LoadConfig();         // Load main config

    {                       // Please write code between the brackets
        MainDlg dlg;        // Show main dlg
        dlg.Run();
    }

    UISystem::Cleanup();            // Clean up UI library
    return 0;
}
