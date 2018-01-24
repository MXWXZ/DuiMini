/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/05
 *
 * @Description:
 */
#pragma once
#include "Core/UIDlgBuilder.h"

namespace DuiMini {
class DUIMINI_API UIWindow {
public:
    UIWindow();
    explicit UIWindow(LPCTSTR v_name);
    ~UIWindow();

    HWND GetHWND() const;
    LPCTSTR SetDlgName(LPCTSTR v_name);
    LPCTSTR GetDlgName() const;
    UIDlgBuilder* SetDlgBuilder();
    UIDlgBuilder* GetBuilder();

    /**
     * Create and run window
     * @param    LPCTSTR v_classname:window class name
     */
    void Run(LPCTSTR v_classname = _T("DuiMini"));

    /**
     * Create window
     * @param    LPCTSTR v_classname:window class name
     * @return   nullptr for failed
     */
    HWND Create(LPCTSTR v_classname);

    /**
     * Show window
     * @param    bool v_show:true for show(default)
     * @param    bool v_focus:true for setfocus(default)
     */
    void ShowWindow(bool v_show = true, bool v_focus = true) const;

    /**
     * Do modal loop
     */
    void DoModal();

    bool SetWindowPos(HWND v_insertafter, int v_x, int v_y,
                      int v_width, int v_height, UINT v_flags);

protected:
    /**
     * Message handler
     */
    virtual LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam);
    static LRESULT CALLBACK WinProc(HWND v_hwnd, UINT v_msg,
                                    WPARAM v_wparam, LPARAM v_lparam);
    void Paint();

protected:
    UStr dlgname_;                      // dlg name
    HWND hwnd_ = nullptr;               // main window hwnd
    UIDlgBuilder* builder_ = nullptr;   // dlg builder
    UIRender* render_ = nullptr;        // render
};
}    // namespace DuiMini
