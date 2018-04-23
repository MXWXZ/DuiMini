/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once
#include "Core/UIDlgBuilder.h"

namespace DuiMini {
#define MSG_MAP_BEGIN(theclass)         virtual void _CtrlBindMsgHandler() { \
                                            typedef theclass _thisclass;
#define ON_CONTROL_MSG(name, msg, func)     BindMsgHandler(name, msg, (MsgHandleFun)(&_thisclass::func));
#define ON_PARENT_MSG(parentclass)          parentclass::_CtrlBindMsgHandler();
#define MSG_MAP_END                     }

#define VAR_MAP_BEGIN               virtual void _CtrlBindVar() {       \
                                        UIControl** tmp = nullptr;
#define ON_CONTROL_VAR(name, var)       tmp = (UIControl**)&var;       \
                                        *tmp = FindCtrlFromName(name); \
                                        if (!var)                      \
                                            UISetError(kEL_Warning, kEC_IDInvalid, ErrorMsg_IDInvalid(name));
#define ON_PARENT_VAR(parentclass)      parentclass::_CtrlBindVar();
#define VAR_MAP_END                 }

typedef bool(UIWindow::*MsgHandleFun)(const UIEvent& v_event);

class DUIMINI_API UIWindow {
public:
    UIWindow();
    explicit UIWindow(LPCTSTR v_name);
    virtual ~UIWindow();

public:
    UIDialog* GetDialog() const;
    HWND GetHWND() const;

    void  SetDlgName(LPCTSTR v_dlgname);  // Please ONLY set before create
    CUStr GetDlgName() const;

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

    bool SetIcon(UINT v_res);

    UIRect GetWindowPos() const;
    bool SetWindowSize(int v_width, int v_height);   // Set width&height
    bool SetWindowPos(int v_x, int v_y);             // Set x&y
    bool SetWindowPos(const UIRect& v_rect);         // Set x&y&width&height
    bool SetWindowPos(int v_x, int v_y, int v_width, int v_height);
    bool SetWindowPos(HWND v_insert_after, int v_x, int v_y,
                      int v_width, int v_height, UINT v_flags);
    bool CenterWindow();

    UIControl* FindCtrlFromName(LPCTSTR v_name) const;

    /**
     * Update Window
     * @param    bool v_updatebg:if true update background
     */
    void UpdateWindow(bool v_updatebg = false) const;

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
    bool FinishCreateControl(UIControl* v_ctrl);

    void Close() const;
    void Maximize() const;
    void Restore() const;
    void Minimize() const;

    /**
    * change language/skin
    * @param    v_id:config id
    * Only this window will receive event and global config will NOT be change!
    */
    void ChangeSkin(SKINID v_id);
    void ChangeLang(LANGID v_id);

public:
    UIRender* GetRender() const;
    UIDlgBuilder* GetDlgBuilder() const;
    LRESULT SendWindowMessage(UINT v_msg, WPARAM v_wparam,
                              LPARAM v_lparam) const;

protected:
    // better to call them if you override
    virtual void OnInit();
    virtual void OnClose();
    virtual void OnMaximize();
    virtual void OnRestore();
    virtual void OnMinimize();

protected:
    /**
     * Message handler
     */
    virtual LRESULT MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam);
    static LRESULT CALLBACK WinProc(HWND v_hwnd, UINT v_msg,
                                    WPARAM v_wparam, LPARAM v_lparam);
    bool Paint();

    bool SetDlgBuilder(LPCTSTR v_dlgname);

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

protected:
    // window info
    UStr             dlgname_;                    // dlg name
    HWND             hwnd_ = nullptr;             // main window hwnd
    shared_ptr<UIDlgBuilder> builder_ = nullptr;  // dlg builder
    shared_ptr<UIRender> render_ = nullptr;       // render
    UIRect           rect_;                       // window rect
    static UINT      classname_cnt_;              // auto classname counter
    HWND             tooltip_hwnd_ = nullptr;     // tooltip
    TOOLINFO         tooltip_info_;               // tooltip info
    bool             tooltip_active_ = false;     // is active tooltip

    // Event system
    bool             mouse_tracking_ = false;     // mouse tracking state
    POINT            last_mousepos_{ 0, 0 };      // last mouse position
    UIControl*       ctrl_lclick_ = nullptr;      // current left clicked ctrl
    UIControl*       ctrl_rclick_ = nullptr;      // current right clicked ctrl
    UIControl*       ctrl_hover_ = nullptr;       // current hovered ctrl

protected:
    bool OnCloseButton(const UIEvent& v_event);
    bool OnMaxButton(const UIEvent& v_event);
    bool OnRestoreButton(const UIEvent& v_event);
    bool OnMinButton(const UIEvent& v_event);

    MSG_MAP_BEGIN(UIWindow)
        ON_CONTROL_MSG(_T("btn_close"), kWM_LButtonClick, OnCloseButton)
        ON_CONTROL_MSG(_T("btn_max"), kWM_LButtonClick, OnMaxButton)
        ON_CONTROL_MSG(_T("btn_restore"), kWM_LButtonClick, OnRestoreButton)
        ON_CONTROL_MSG(_T("btn_min"), kWM_LButtonClick, OnMinButton)
        MSG_MAP_END

    VAR_MAP_BEGIN
        VAR_MAP_END
};
}    // namespace DuiMini
