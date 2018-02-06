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
enum WindowMessage {
    //      Msg                 WPARAM              LPARAM
    kWM_Start_ = 0,    // USELESS

    kWM_MouseEnter,    //               WM_MOUSEMOVE
    kWM_MouseLeave,    //                    ...
    kWM_MouseMove,     //                    ...
    kWM_LButtonDown,   //               WM_LBUTTONDOWN
    kWM_LButtonUp,     //                    ...
    kWM_LButtonClick,  //                    ...
    kWM_LButtonDBClick,//                    ...
    kWM_RButtonDown,   //                    ...
    kWM_RButtonUp,     //                    ...
    kWM_RButtonClick,  //                    ...
    kWM_RButtonDBClick,//                    ...

    kWM_End_           // USELESS
};

typedef bool(UIWindow::*MsgHandleFun)(WPARAM v_wparam, LPARAM v_lparam);

#define MSG_MAP_BEGIN(theclass) virtual void _CtrlBindMsgHandler() { \
                                    typedef theclass thisclass;
#define MSG_MAP_END   }
#define ON_CONTROL_MSG(name, msg, func)   BindMsgHandler(name, msg, static_cast<MsgHandleFun>(&thisclass::func));

class DUIMINI_API UIWindow {
public:
    UIWindow();
    explicit UIWindow(LPCTSTR v_name);
    ~UIWindow();

public:
    HWND GetHWND() const;

    LPCTSTR SetDlgName(LPCTSTR v_dlgname);  // Please ONLY set before create
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

    bool ShowWindow(bool v_show = true, bool v_focus = true) const;

    void DoModal();     // Do modal loop

    bool AllowWindowMove(bool v_movable = true);
    bool AllowWindowResize(bool v_resizable = true);
    void SetSizeBox(LPCTSTR v_sizestr);
    void SetCaptionRect(LPCTSTR v_pos);

    RECT GetWindowPos() const;
    bool SetWindowSize(int v_width, int v_height);      // Set width&height
    bool SetWindowPos(int v_x, int v_y);     // Set x&y
    bool SetWindowPos(RECT v_rect);          // Set x&y&width&height
    bool SetWindowPos(int v_x, int v_y, int v_width, int v_height);
    bool SetWindowPos(HWND v_insert_after, int v_x, int v_y,
                      int v_width, int v_height, UINT v_flags);
    bool CenterWindow();

    void ShowTaskBar(bool v_show = true) const;

    CUStr GetTitle() const;
    void SetTitle(LPCTSTR v_title);

    UIControl* FindCtrlFromName(LPCTSTR v_name);

    void UpdateWindow() const;

    /**
    * Create control
    * @param    UIControl* v_ctrl:allocated ctrl pointer
    * @param    UIControl* v_parent:parent ctrl
    * @return   created ctrl pointer
    * After this function, you can use SetAttribute to set the attr
    * when you finish, call FinishCreateControl;
    */
    UIControl* CreateControl(UIControl* v_ctrl,
                             UIControl* v_parent = nullptr);

    /**
    * Finish create control
    * @param    UIControl* v_ctrl:created ctrl pointer
    * @return   finish created ctrl pointer
    */
    void FinishCreateControl(UIControl* v_ctrl);

    /**
     * Bind & Unbind message handler
     * @param    LPCTSTR v_name:ctrl name
     * @param    WindowMessage v_msg:window message
     * @param    MsgHandleFun v_func:handler function
     * @return   true for success
     */
    bool BindMsgHandler(LPCTSTR v_name, WindowMessage v_msg,
                        MsgHandleFun v_func) const;
    bool UnbindMsgHandler(LPCTSTR v_name, WindowMessage v_msg) const;

    bool SetBackground(LPCTSTR v_path);
    void SetBGAlpha(ALPHA v_alpha);
    void SetAlpha(ALPHA v_alpha);
    ALPHA GetBGAlpha();
    ALPHA GetAlpha();

public:
    UIRender* GetRender() const;
    UIDlgBuilder* GetDlgBuilder() const;
    LRESULT SendWindowMessage(UINT v_msg, WPARAM v_wparam,
                              LPARAM v_lparam) const;

protected:
    /**
     * Message handler
     */
    virtual LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam);
    static LRESULT CALLBACK WinProc(HWND v_hwnd, UINT v_msg,
                                    WPARAM v_wparam, LPARAM v_lparam);
    bool Paint();

    UIDlgBuilder* SetDlgBuilder(LPCTSTR v_dlgname);

protected:
    // window info
    UStr             dlgname_;                    // dlg name
    HWND             hwnd_ = nullptr;             // main window hwnd
    UIDlgBuilder*    builder_ = nullptr;          // dlg builder
    UIRender*        render_ = nullptr;           // render
    RECT             rect_{ 0, 0, 0, 0 };         // window rect
    static int       classname_cnt_;              // auto classname counter

    // Event system
    bool             mouse_tracking_ = false;     // mouse tracking state
    POINT            last_mousepos_{ 0,0 };       // last mouse position
    UIControl*       ctrl_lclick_ = nullptr;      // current left clicked ctrl
    UIControl*       ctrl_rclick_ = nullptr;      // current right clicked ctrl
    UIControl*       ctrl_hover_ = nullptr;       // current hovered ctrl

    MSG_MAP_BEGIN(UIWindow)
        MSG_MAP_END
};
}    // namespace DuiMini
