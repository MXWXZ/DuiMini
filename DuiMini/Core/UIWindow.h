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

public:
    HWND GetHWND() const;
    /**
     * Please ONLY set before create
     */
    LPCTSTR SetDlgName(LPCTSTR v_name);
    LPCTSTR GetDlgName() const;

    /**
    * Create and run window
    * @param    LPCTSTR v_classname:window class name
    * WARNING! window class name must NOT be same! If you use default(DuiMini)
    * it will automatically add an unique count as suffix like "DuiMini1"
    */
    void Run(LPCTSTR v_classname = _T("DuiMini"));

    /**
    * Create window
    * @param    LPCTSTR v_classname:window class name
    * @return   nullptr for failed
    */
    HWND Create(LPCTSTR v_classname);

    void ShowWindow(bool v_show = true, bool v_focus = true) const;

    /**
    * Do modal loop
    */
    void DoModal();

    RECT GetWindowPos() const;
    bool SetWindowSize(int v_width, int v_height);      // Set width&height
    bool SetWindowPos(int v_x, int v_y);    // Set x&y
    bool SetWindowPos(RECT v_rect);    // Set x&y&width&height
    bool SetWindowPos(int v_x, int v_y, int v_width, int v_height);
    bool SetWindowPos(HWND v_insertafter, int v_x, int v_y,
                      int v_width, int v_height, UINT v_flags);
    bool CenterWindow();

    void ShowTaskBar(bool v_show = true) const;
    void SetTitle(LPCTSTR v_title);

public:
    // dlg builder
    UIDlgBuilder* SetDlgBuilder();
    UIDlgBuilder* GetDlgBuilder();

    UIRender* GetRender();

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
    RECT rect_{ 0,0,0,0 };              // window rect
    static int classnamecnt_;           // auto classname counter
};
}    // namespace DuiMini
