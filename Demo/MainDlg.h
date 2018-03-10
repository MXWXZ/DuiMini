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

    void OnInit() override;

private:

protected:
    // override message handler sample
    LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) override;

    MSG_MAP_BEGIN(MainDlg)
        ON_PARENT_MSG(UIWindow)
        MSG_MAP_END

    VAR_MAP_BEGIN
        ON_PARENT_VAR(UIWindow)
        VAR_MAP_END
};