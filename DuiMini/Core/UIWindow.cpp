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

UIDialog* UIWindow::GetDialog() const {
    return builder_->GetCtrlRoot();
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
    UStr dlg_file = UIConfig::FindDlgFile(v_dlgname);
    if (dlg_file.IsEmpty())
        return nullptr;
    UIXmlLoader config(dlg_file);
    builder_->Init(config.GetRoot(), this);
    UIHandleError();
    return builder_;
}

bool UIWindow::OnCloseButton(const UIEvent& v_event) {
    Close();
    return true;
}

bool UIWindow::OnMaxButton(const UIEvent & v_event) {
    Maximize();
    return true;
}

bool UIWindow::OnRestoreButton(const UIEvent & v_event) {
    Restore();
    return true;
}

bool UIWindow::OnMinButton(const UIEvent & v_event) {
    Minimize();
    return true;
}

void UIWindow::OnInit() {}

void UIWindow::OnClose() {}

void UIWindow::OnMaximize() {
    UIButton* btn_max = (UIButton*)FindCtrlFromName(_T("btn_max"));
    UIButton* btn_restore = (UIButton*)FindCtrlFromName(_T("btn_restore"));
    if (btn_max && btn_max->VisibleCtrl(STAY))
        btn_max->VisibleCtrl(FALSE);
    if (btn_restore && !btn_restore->VisibleCtrl(STAY))
        btn_restore->VisibleCtrl(TRUE);
}

void UIWindow::OnRestore() {
    UIButton* btn_max = (UIButton*)FindCtrlFromName(_T("btn_max"));
    UIButton* btn_restore = (UIButton*)FindCtrlFromName(_T("btn_restore"));
    if (btn_max && !btn_max->VisibleCtrl(STAY))
        btn_max->VisibleCtrl(TRUE);
    if (btn_restore && btn_restore->VisibleCtrl(STAY))
        btn_restore->VisibleCtrl(FALSE);
}

void UIWindow::OnMinimize() {}

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
    UIControl* ctrl = GetDialog()->FindCtrlFromName(v_name);
    if (!ctrl) {
        UIHandleError(kLL_Warning, kEC_IDInvalid,
                      _T("Ctrl name \"%s\" invalid!"), v_name);
        return false;
    }
    ctrl->SetMsgHandler(v_msg, v_func);
    return true;
}

bool UIWindow::UnbindMsgHandler(LPCTSTR v_name, WindowMessage v_msg) const {
    UIControl* ctrl = GetDialog()->FindCtrlFromName(v_name);
    if (!ctrl) {
        UIHandleError(kLL_Warning, kEC_IDInvalid,
                      _T("Ctrl name \"%s\" invalid!"), v_name);
        return false;
    }
    ctrl->SetMsgHandler(v_msg, nullptr);
    return true;
}

void UIWindow::Close() const {
    SendWindowMessage(WM_CLOSE, NULL, NULL);
}

void UIWindow::Maximize() const {
    SendWindowMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(last_mousepos_.x,
                                                             last_mousepos_.y));
}

void UIWindow::Restore() const {
    SendWindowMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(last_mousepos_.x,
                                                            last_mousepos_.y));
}

void UIWindow::Minimize() const {
    SendWindowMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(last_mousepos_.x,
                                                             last_mousepos_.y));
}

UIRender* UIWindow::GetRender() const {
    return render_;
}

UIControl* UIWindow::FindCtrlFromName(LPCTSTR v_name) {
    if (!builder_)
        return nullptr;
    return GetDialog()->FindCtrlFromName(v_name);
}

void UIWindow::UpdateWindow(bool v_updatebg/* = false*/) const {
    GetDialog()->UpdatePos();
    if (v_updatebg)
        render_->RedrawBackground();
    SendWindowMessage(WM_PAINT, NULL, NULL);
}

void UIWindow::Run(LPCTSTR v_classname/* = _T("DuiMini")*/) {
    Create(v_classname);
    ShowWindow();
    DoModal();
}

LRESULT UIWindow::MsgHandler(UINT v_msg, WPARAM v_wparam, LPARAM v_lparam) {
    UIEvent event(v_wparam, v_lparam);
    event.SetMsgFromWinMsg(v_msg);
    // mouse msg:mouse position ctrl
    UIControl *mousepos_ctrl = nullptr;
    // mouse msg:ctrl_lclick_ or ctrl_rclick_
    UIControl** ctrl_click_tmp = &ctrl_rclick_;
    // TODO: Add new Msg
    switch (v_msg) {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        ctrl_click_tmp = &ctrl_lclick_;  // change default value
    case WM_RBUTTONDOWN:                 // default value,no need to change
    case WM_RBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    case WM_MOUSEMOVE:
        last_mousepos_ = event.GetPos();
        mousepos_ctrl = GetDialog()->FindCtrlFromPT(last_mousepos_);
        break;
    }
    UIControl* &ctrl_click = *ctrl_click_tmp;

    switch (v_msg) {
    case WM_CREATE:
    {
        if (!SetDlgBuilder(dlgname_))
            break;
        _CtrlBindMsgHandler();
        _CtrlBindVar();
        OnInit();
        UpdateWindow(true);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    case WM_CLOSE:
    {
        UIEvent tmp(kWM_LButtonUp);
        tmp.SetPos(last_mousepos_);
        // send btnup msg to current click ctrl
        if (ctrl_lclick_)
            ctrl_lclick_->Event(tmp);
        if (ctrl_rclick_)
            ctrl_rclick_->Event(tmp);
        OnClose();
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
        SetCapture(hwnd_);
        ctrl_click = mousepos_ctrl;
        mousepos_ctrl->Event(event);
        break;
    }
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    {
        if (!ctrl_click)
            break;

        ReleaseCapture();
        if (ctrl_click != mousepos_ctrl) {
            ctrl_click = nullptr;
            break;
        }
        ctrl_click->Event(event);
        if (v_msg == WM_LBUTTONUP)
            ctrl_click->Event(UIEvent(kWM_LButtonClick, v_wparam, v_lparam));
        else
            ctrl_click->Event(UIEvent(kWM_RButtonClick, v_wparam, v_lparam));
        ctrl_click = nullptr;
        break;
    }
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    {
        if (!mousepos_ctrl)
            break;
        mousepos_ctrl->Event(event);
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

        // enter new ctrl
        if (mousepos_ctrl != ctrl_hover_) {
            if (ctrl_hover_)     // former ctrl leave
                ctrl_hover_->Event(UIEvent(kWM_MouseLeave, v_wparam, v_lparam));
            if (mousepos_ctrl) {
                mousepos_ctrl->Event(UIEvent(kWM_MouseEnter, v_wparam, v_lparam));
                ctrl_hover_ = mousepos_ctrl;
            }
        }
        if (mousepos_ctrl)
            mousepos_ctrl->Event(event);
        break;
    }
    case WM_MOUSELEAVE:
    {
        mouse_tracking_ = false;
        if (ctrl_hover_) {      // clear hover control
            ctrl_hover_->Event(event);
            ctrl_hover_ = nullptr;
        }
        break;
    }
    case WM_NCHITTEST:
    {
        if (GetDialog()->GetAttribute(_T("resizable")).Str2Int()) {
            POINT pt;
            pt.x = GET_X_LPARAM(v_lparam);
            pt.y = GET_Y_LPARAM(v_lparam);
            ::ScreenToClient(hwnd_, &pt);
            int border_left = GetDialog()->GetAttribute(_T("sizebox_left")).Str2Int();
            int border_top = GetDialog()->GetAttribute(_T("sizebox_top")).Str2Int();
            int border_right = GetDialog()->GetAttribute(_T("sizebox_right")).Str2Int();
            int border_bottom = GetDialog()->GetAttribute(_T("sizebox_bottom")).Str2Int();

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
        GetClientRect(hwnd_, &rect_.rect());
        UStr pos;
        pos.Format(_T("0,0,%d,%d"), rect_.right - rect_.left,
                    rect_.bottom - rect_.top);
        GetDialog()->SetPos(pos);
        if (v_wparam == SIZE_RESTORED)
            OnRestore();
        if (IsWindowVisible(hwnd_))
            UpdateWindow(true);
        break;
    }
    case WM_GETMINMAXINFO:
    {
        UIDialog* dlg = GetDialog();
        MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(v_lparam);
        info->ptMinTrackSize.x = dlg->GetMinWidth();
        info->ptMinTrackSize.y = dlg->GetMinHeight();
        info->ptMaxSize.x = info->ptMaxTrackSize.x = dlg->GetMaxWidth();
        info->ptMaxSize.y = info->ptMaxTrackSize.y = dlg->GetMaxHeight();
        break;
    }
    case WM_SYSCOMMAND:
    {
        if (v_wparam == SC_MINIMIZE)
            OnMinimize();
        else if (v_wparam == SC_MAXIMIZE)
            OnMaximize();
        else if (v_wparam == SC_RESTORE)
            OnRestore();
    }
    }

    return CallWindowProc(DefWindowProc, hwnd_, v_msg, v_wparam, v_lparam);
}

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

bool UIWindow::SetIcon(UINT v_res) {
    HICON icon = (HICON)::LoadImage(UISystem::GetInstance(),
                                    MAKEINTRESOURCE(v_res),
                                    IMAGE_ICON,
                                    ::GetSystemMetrics(SM_CXICON),
                                    ::GetSystemMetrics(SM_CYICON),
                                    LR_DEFAULTCOLOR);
    HICON iconsm = (HICON)::LoadImage(UISystem::GetInstance(),
                                      MAKEINTRESOURCE(v_res),
                                      IMAGE_ICON,
                                      ::GetSystemMetrics(SM_CXSMICON),
                                      ::GetSystemMetrics(SM_CYSMICON),
                                      LR_DEFAULTCOLOR);
    if (!icon || !iconsm) {
        UIHandleError(kLL_Warning, kEC_IDInvalid, _T("Icon id \"%u\" invalid!"),
                      v_res);
        return false;
    }
    SendWindowMessage(WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendWindowMessage(WM_SETICON, ICON_SMALL, (LPARAM)iconsm);
    return true;
}

UIRect UIWindow::GetWindowPos() const {
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

bool UIWindow::SetWindowPos(const UIRect& v_rect) {
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
    // Attribute will be change at WM_SIZE
    return ::SetWindowPos(hwnd_, v_insertafter, v_x, v_y,
                          v_width, v_height, v_flags | SWP_NOREDRAW);
}

bool UIWindow::CenterWindow() {
    UIRect newpos;
    int screenwidth = UIUtils::GetWorkAreaSize().width();
    int screenheight = UIUtils::GetWorkAreaSize().height();
    int width = rect_.right - rect_.left;
    int height = rect_.bottom - rect_.top;
    newpos.left = (screenwidth - width) / 2;
    newpos.top = (screenheight - height) / 2;
    newpos.right = newpos.left + width;
    newpos.bottom = newpos.top + height;
    return SetWindowPos(newpos);
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
                           WS_POPUP,
                           CW_USEDEFAULT, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
                           UISystem::GetInstance(), this);

    if (hwnd_ == nullptr || !IsWindow(hwnd_))
        return nullptr;

    return hwnd_;
}

}    // namespace DuiMini
