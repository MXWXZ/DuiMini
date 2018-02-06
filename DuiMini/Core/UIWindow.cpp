/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/05
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIWindow.h"

namespace DuiMini {
int UIWindow::classname_cnt_ = 0;

UIWindow::UIWindow() {
    render_ = new UIRender;
}

UIWindow::UIWindow(LPCTSTR v_name)
    :UIWindow() {
    SetDlgName(v_name);
}

UIWindow::~UIWindow() {
    delete builder_;
    builder_ = nullptr;
    delete render_;
    render_ = nullptr;
}

HWND UIWindow::GetHWND() const {
    return hwnd_;
}

LPCTSTR UIWindow::SetDlgName(LPCTSTR v_dlgname) {
    dlgname_ = v_dlgname;
    return dlgname_;
}

LPCTSTR UIWindow::GetDlgName() const {
    return dlgname_;
}

UIDlgBuilder* UIWindow::SetDlgBuilder(LPCTSTR v_dlgname) {
    if (builder_)
        return nullptr;
    builder_ = new UIDlgBuilder;
    UIAttr* dlgattr = UIConfig::FindDlg(v_dlgname);
    if (!dlgattr)
        return nullptr;
    UIXmlLoader config(dlgattr->GetValue(_T("file")));
    builder_->Init(config.GetRoot(), this);
    UIHandleError();
    return builder_;
}

UIDlgBuilder* UIWindow::GetDlgBuilder() const {
    return builder_;
}

LRESULT UIWindow::SendWindowMessage(UINT v_msg, WPARAM v_wparam,
                                    LPARAM v_lparam) const {
    return SendMessage(hwnd_, v_msg, v_wparam, v_lparam);
}

UIControl* UIWindow::CreateControl(UIControl* v_ctrl,
                                   UIControl* v_parent/* = nullptr*/) {
    return builder_->CreateControl(v_ctrl, this, v_parent);
}

void UIWindow::FinishCreateControl(UIControl* v_ctrl) {
    builder_->FinishCreateControl(v_ctrl);
}

bool UIWindow::BindMsgHandler(LPCTSTR v_name, WindowMessage v_msg,
                              MsgHandleFun v_func) const {
    UIControl* ctrl = builder_->GetCtrlRoot()->FindCtrlFromName(v_name);
    if (!ctrl) {
        UIHandleError(kLL_Warning, kEC_IDInvalid,
                      _T("Ctrl name \"%s\" invalid!"), v_name);
        return false;
    }
    ctrl->SetMsgHandler(v_msg, v_func);
    return true;
}

bool UIWindow::UnbindMsgHandler(LPCTSTR v_name, WindowMessage v_msg) const {
    UIControl* ctrl = builder_->GetCtrlRoot()->FindCtrlFromName(v_name);
    if (!ctrl) {
        UIHandleError(kLL_Warning, kEC_IDInvalid,
                      _T("Ctrl name \"%s\" invalid!"), v_name);
        return false;
    }
    ctrl->SetMsgHandler(v_msg, nullptr);
    return true;
}

bool UIWindow::SetBackground(LPCTSTR v_path) {
    return builder_->GetCtrlRoot()->SetBackground(v_path);
}

void UIWindow::SetBGAlpha(ALPHA v_alpha) {
    builder_->GetCtrlRoot()->SetAttribute(_T("bgalpha"), UStr(v_alpha));
}

void UIWindow::SetAlpha(ALPHA v_alpha) {
    builder_->GetCtrlRoot()->SetAttribute(_T("alpha"), UStr(v_alpha));
}

ALPHA UIWindow::GetBGAlpha() {
    return (ALPHA)(builder_->GetCtrlRoot()->GetAttribute(_T("bgalpha")).Str2Int());
}

ALPHA UIWindow::GetAlpha() {
    return (ALPHA)(builder_->GetCtrlRoot()->GetAttribute(_T("alpha")).Str2Int());
}

UIRender* UIWindow::GetRender() const {
    return render_;
}

UIControl* UIWindow::FindCtrlFromName(LPCTSTR v_name) {
    if (!builder_)
        return nullptr;
    return builder_->GetCtrlRoot()->FindCtrlFromName(v_name);
}

void UIWindow::UpdateWindow() const {
    builder_->GetCtrlRoot()->UpdatePos();
    SendWindowMessage(WM_PAINT, NULL, NULL);
}

void UIWindow::Run(LPCTSTR v_classname/* = _T("DuiMini")*/) {
    Create(v_classname);
    ShowWindow();
    DoModal();
}

#define WLPARAM v_wparam, v_lparam
LRESULT UIWindow::MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    // mouse msg:mouse position ctrl
    UIControl *mousepos_ctrl = nullptr;
    // mouse msg:ctrl_lclick_ or ctrl_rclick_
    UIControl** ctrl_click_tmp = &ctrl_rclick_;
    WindowMessage mouse_msg = kWM_Start_;
    switch (v_msg) {
    case WM_LBUTTONDOWN:
        if (!mouse_msg)mouse_msg = kWM_LButtonDown;
    case WM_LBUTTONUP:
        if (!mouse_msg)mouse_msg = kWM_LButtonUp;
        ctrl_click_tmp = &ctrl_lclick_;  // change default value
    case WM_RBUTTONDOWN:                 // default value,no need to change
        if (!mouse_msg)mouse_msg = kWM_RButtonDown;
    case WM_RBUTTONUP:
        if (!mouse_msg)mouse_msg = kWM_RButtonUp;
    case WM_LBUTTONDBLCLK:
        if (!mouse_msg)mouse_msg = kWM_LButtonDBClick;
    case WM_RBUTTONDBLCLK:
        if (!mouse_msg)mouse_msg = kWM_RButtonDBClick;
    case WM_MOUSEMOVE:
        mousepos_ctrl = builder_->GetCtrlRoot()->FindCtrlFromPT(last_mousepos_);
        break;
    }
    UIControl* &ctrl_click = *ctrl_click_tmp;

    switch (v_msg) {
    case WM_CREATE:
    {
        if (!SetDlgBuilder(dlgname_))
            break;
        _CtrlBindMsgHandler();
        UpdateWindow();
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    case WM_CLOSE:
    {
        DWORD lparam = MAKELPARAM(last_mousepos_.x, last_mousepos_.y);
        // send btnup msg to current click ctrl
        if (ctrl_lclick_)
            ctrl_lclick_->Event(kWM_LButtonUp, NULL, lparam);
        if (ctrl_rclick_)
            ctrl_rclick_->Event(kWM_RButtonUp, NULL, lparam);
        break;
    }
    case WM_PAINT:
    {
        Paint();
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    {
        if (!mousepos_ctrl)
            break;
        ctrl_click = mousepos_ctrl;
        SetCapture(hwnd_);
        mousepos_ctrl->Event(mouse_msg, WLPARAM);
        break;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    {
        if (!ctrl_click)
            break;

        if (ctrl_click != mousepos_ctrl) {
            ctrl_click = nullptr;
            break;
        }
        ReleaseCapture();
        ctrl_click->Event(mouse_msg, WLPARAM);
        if (v_msg == WM_LBUTTONUP)
            ctrl_click->Event(kWM_LButtonClick, WLPARAM);
        else
            ctrl_click->Event(kWM_RButtonClick, WLPARAM);
        ctrl_click = nullptr;
        break;
    }
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    {
        if (!mousepos_ctrl)
            break;
        mousepos_ctrl->Event(mouse_msg, WLPARAM);
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (!mouse_tracking_) {
            TRACKMOUSEEVENT tmp;
            tmp.cbSize = sizeof(tmp);
            tmp.dwFlags = TME_LEAVE | TME_HOVER;
            tmp.hwndTrack = hwnd_;
            tmp.dwHoverTime = 1000;     // 1000 delay time
            ::TrackMouseEvent(&tmp);
            mouse_tracking_ = true;
        }
        last_mousepos_.x = GET_X_LPARAM(v_lparam);
        last_mousepos_.y = GET_Y_LPARAM(v_lparam);

        // enter new ctrl
        if (mousepos_ctrl != ctrl_hover_) {
            if (ctrl_hover_)     // former ctrl leave
                ctrl_hover_->Event(kWM_MouseLeave, WLPARAM);
            if (mousepos_ctrl) {
                mousepos_ctrl->Event(kWM_MouseEnter, WLPARAM);
                ctrl_hover_ = mousepos_ctrl;
            }
        }
        if (mousepos_ctrl)
            mousepos_ctrl->Event(kWM_MouseMove, WLPARAM);
        break;
    }
    case WM_MOUSELEAVE:
    {
        mouse_tracking_ = false;
        if (ctrl_hover_) {      // clear hover control
            ctrl_hover_->Event(kWM_MouseLeave, WLPARAM);
            ctrl_hover_ = nullptr;
        }
        break;
    }
    case WM_NCHITTEST:
    {
        if (builder_->GetCtrlRoot()->GetAttribute(_T("resizable")).Str2Int()) {
            POINT pt;
            pt.x = GET_X_LPARAM(v_lparam);
            pt.y = GET_Y_LPARAM(v_lparam);
            ::ScreenToClient(hwnd_, &pt);
            int border_left = builder_->GetCtrlRoot()->GetAttribute(_T("sizebox_left")).Str2Int();
            int border_top = builder_->GetCtrlRoot()->GetAttribute(_T("sizebox_top")).Str2Int();
            int border_right = builder_->GetCtrlRoot()->GetAttribute(_T("sizebox_right")).Str2Int();
            int border_bottom = builder_->GetCtrlRoot()->GetAttribute(_T("sizebox_bottom")).Str2Int();

            if (pt.x < rect_.left + border_left && pt.y < rect_.top + border_top)
                return HTTOPLEFT;
            else if (pt.x > rect_.right - border_right && pt.y < rect_.top + border_top)
                return HTTOPRIGHT;
            else if (pt.x<rect_.left + border_left && pt.y>rect_.bottom - border_bottom)
                return HTBOTTOMLEFT;
            else if (pt.x > rect_.right - border_right && pt.y > rect_.bottom - border_bottom)
                return HTBOTTOMRIGHT;
            else if (pt.x < rect_.left + border_left)
                return HTLEFT;
            else if (pt.x > rect_.right - border_right)
                return HTRIGHT;
            else if (pt.y < rect_.top + border_top)
                return HTTOP;
            else if (pt.y > rect_.bottom - border_bottom)
                return HTBOTTOM;
        }
        break;
    }
    case WM_SIZE:
    {
        GetClientRect(hwnd_, &rect_);

        UStr pos;
        pos.Format(_T("0,0,%d,%d"), rect_.right - rect_.left,
                   rect_.bottom - rect_.top);
        builder_->GetCtrlRoot()->SetPos(pos);
        UpdateWindow();
        break;
    }
    }

    return CallWindowProc(DefWindowProc, hwnd_, v_msg, WLPARAM);
}
#undef DEFPARAM

LRESULT CALLBACK UIWindow::WinProc(HWND v_hwnd, UINT v_msg,
                                   WPARAM v_wparam, LPARAM v_lparam) {
    UIWindow* pthis = nullptr;
    if (v_msg == WM_NCCREATE) {
        // create window save this pointer, because WinProc is a static function
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(v_lparam);
        pthis = reinterpret_cast<UIWindow*>(lpcs->lpCreateParams);
        pthis->hwnd_ = v_hwnd;
        SetWindowLongPtr(v_hwnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pthis));
    } else {
        pthis = reinterpret_cast<UIWindow*>(GetWindowLongPtr(v_hwnd,
                                                             GWLP_USERDATA));
        if (v_msg == WM_NCDESTROY && pthis != NULL) {
            // destroy window
            SetWindowLongPtr(pthis->hwnd_, GWLP_USERDATA, 0L);

            pthis->hwnd_ = nullptr;
            return true;
        }
    }
    if (pthis)
        return pthis->MsgHandler(v_msg, v_wparam, v_lparam);
    else
        return DefWindowProc(v_hwnd, v_msg, v_wparam, v_lparam);
}

bool UIWindow::Paint() {
    if (!render_)
        return false;
    return render_->Paint(this);
}

bool UIWindow::ShowWindow(bool v_show /*= true*/,
                          bool v_focus /*= true*/) const {
    return ::ShowWindow(hwnd_, v_show ? (v_focus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

void UIWindow::DoModal() {
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool UIWindow::AllowWindowMove(bool v_movable/* = true*/) {
    bool ret = builder_->GetCtrlRoot()->GetAttribute(_T("movable")).Str2Int();
    builder_->GetCtrlRoot()->SetAttribute(_T("movable"), UStr(v_movable));
    return ret;
}

bool UIWindow::AllowWindowResize(bool v_resizable/* = true*/) {
    bool ret = builder_->GetCtrlRoot()->GetAttribute(_T("resizable")).Str2Int();
    builder_->GetCtrlRoot()->SetAttribute(_T("resizable"), UStr(v_resizable));
    return ret;
}

void UIWindow::SetSizeBox(LPCTSTR v_sizestr) {
    builder_->GetCtrlRoot()->SetAttribute(_T("sizebox"), v_sizestr);
    UStr tmp = v_sizestr;
    int seppos1 = tmp.Find(_T(","));
    builder_->GetCtrlRoot()->SetAttribute(_T("sizebox_left"), tmp.Left(seppos1));
    int seppos2 = tmp.Find(_T(","), seppos1 + 1);
    builder_->GetCtrlRoot()->SetAttribute(_T("sizebox_top"), tmp.Mid(seppos1 + 1, seppos2 - seppos1 - 1));
    int seppos3 = tmp.Find(_T(","), seppos2 + 1);
    builder_->GetCtrlRoot()->SetAttribute(_T("sizebox_right"), tmp.Mid(seppos2 + 1, seppos3 - seppos2 - 1));
    builder_->GetCtrlRoot()->SetAttribute(_T("sizebox_bottom"), tmp.Right(tmp.GetLength() - seppos3 - 1));
}

void UIWindow::SetCaptionRect(LPCTSTR v_pos) {
    builder_->GetCtrlRoot()->SetAttribute(_T("caption"), v_pos);
}

RECT UIWindow::GetWindowPos() const {
    return rect_;
}

bool UIWindow::SetWindowSize(int v_width, int v_height) {
    return SetWindowPos(NULL, rect_.left, rect_.top, v_width, v_height,
                        SWP_NOMOVE | SWP_NOZORDER);
}

bool UIWindow::SetWindowPos(int v_x, int v_y) {
    return SetWindowPos(NULL, v_x, v_y, rect_.right - rect_.left,
                        rect_.bottom - rect_.top,
                        SWP_NOSIZE | SWP_NOZORDER);
}

bool UIWindow::SetWindowPos(RECT v_rect) {
    return SetWindowPos(NULL, v_rect.left, v_rect.top,
                        v_rect.right - v_rect.left,
                        v_rect.bottom - v_rect.top,
                        SWP_NOZORDER);
}

bool UIWindow::SetWindowPos(int v_x, int v_y, int v_width, int v_height) {
    return SetWindowPos(NULL, v_x, v_y, v_width, v_height,
                        SWP_NOZORDER);
}

bool UIWindow::SetWindowPos(HWND v_insertafter, int v_x, int v_y,
                            int v_width, int v_height, UINT v_flags) {
    return ::SetWindowPos(hwnd_, v_insertafter, v_x, v_y,
                              v_width, v_height, v_flags);
}

bool UIWindow::CenterWindow() {
    RECT newpos;
    int screenwidth = GetSystemMetrics(SM_CXSCREEN);
    int screenheight = GetSystemMetrics(SM_CYSCREEN);
    int width = rect_.right - rect_.left;
    int height = rect_.bottom - rect_.top;
    newpos.left = (screenwidth - width) / 2;
    newpos.top = (screenheight - height) / 2;
    newpos.right = newpos.left + width;
    newpos.bottom = newpos.top + height;
    return SetWindowPos(newpos);
}

void UIWindow::ShowTaskBar(bool v_show/* = true*/) const {
    LONG style = GetWindowLong(hwnd_, GWL_EXSTYLE);
    if (v_show)
        style &= ~WS_EX_TOOLWINDOW;
    else
        style |= WS_EX_TOOLWINDOW;
    SetWindowLong(hwnd_, GWL_EXSTYLE, style);
    builder_->GetCtrlRoot()->SetAttribute(_T("appwin"), UStr(v_show));
}

CUStr UIWindow::GetTitle() const {
    return builder_->GetCtrlRoot()->GetAttribute(_T("title"));
}

void UIWindow::SetTitle(LPCTSTR v_title) {
    SetWindowText(hwnd_, v_title);
    builder_->GetCtrlRoot()->SetAttribute(_T("title"), v_title);
}

HWND UIWindow::Create(LPCTSTR v_classname) {
    if (hwnd_)
        return hwnd_;

    UStr classname = v_classname;
    if (classname == _T("DuiMini"))
        classname += UStr(++classname_cnt_);
    WNDCLASSEX wce = { 0 };
    wce.cbSize = sizeof(wce);
    wce.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wce.lpfnWndProc = WinProc;
    wce.cbClsExtra = 0;
    wce.cbWndExtra = 0;
    wce.hInstance = UISystem::GetInstance();
    wce.hIcon = NULL;
    wce.hCursor = LoadCursor(NULL, IDC_ARROW);
    wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wce.lpszMenuName = NULL;
    wce.lpszClassName = classname;
    wce.hIconSm = NULL;
    ATOM nAtom = RegisterClassEx(&wce);
    if (!nAtom) {
        UIHandleError(kLL_Warning, kEC_RegWndFailed,
                      _T("Register window class failed"));
        return nullptr;
    }

    hwnd_ = CreateWindowEx(WS_EX_LAYERED, classname, _T(""),
                           WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
                           UISystem::GetInstance(), this);

    if (hwnd_ == nullptr || !IsWindow(hwnd_))
        return nullptr;

    return hwnd_;
}

}    // namespace DuiMini
