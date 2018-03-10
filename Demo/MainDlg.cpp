/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/06
 *
 * @Description:
 */
#include "stdafx.h"
#include "Demo.h"
#include "MainDlg.h"

MainDlg::MainDlg()
    :UIWindow(_T("main")) {
}

MainDlg::~MainDlg() {}

void MainDlg::OnInit() {
    SetIcon(IDI_DEMO);
    UIWindow::OnInit();
}

LRESULT MainDlg::MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    switch (v_msg) {
    case WM_RBUTTONDBLCLK:
        MessageBox(GetHWND(), _T("Sample of override message handler!"),
                   _T("Demo"), MB_OK);
        break;
    }
    return UIWindow::MsgHandler(v_msg, v_wparam, v_lparam);
}
