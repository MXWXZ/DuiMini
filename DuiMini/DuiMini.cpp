// ****************************************
// Copyright (c) 2017-2050
// All rights reserved.
//
// Author:MXWXZ
// Date:2017/09/05
//
// Description:DLL entrance
// ****************************************
#include "StdAfx.h"
#include "DuiMini.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

