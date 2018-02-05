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

protected:
    // override message handler sample
    LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) override;
};