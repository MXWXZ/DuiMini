/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/06
 *
 * @Description:
 */
#pragma once

class MainDlg :public UIWindow {
public:
    MainDlg();
    ~MainDlg(); 

    bool InitWindow() override;
    bool FuncName(WPARAM v_wparam, LPARAM v_lparam);

protected:
    // override message handler sample
    LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) override;

    MSG_MAP_BEGIN(MainDlg)
        ON_CONTROL_MSG(_T("head"), kWM_LButtonClick, FuncName);
        MSG_MAP_END
};