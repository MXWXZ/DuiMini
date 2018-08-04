/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/08/01
 */
#include "stdafx.h"
#include "UIUtils.h"

namespace DuiMini {
CUStr UIUtils::GetCurrentDir() {
    TCHAR path[MAX_PATH] = { _T('\0') };
    GetCurrentDirectory(MAX_PATH, path);
    return CUStr(path);
}

CUStr UIUtils::GetTimeStr(LPCTSTR v_str) {
    time_t tm;
    time(&tm);
    TCHAR tmpstr[64];
    _tcsftime(tmpstr, sizeof(tmpstr), v_str, localtime(&tm));
    return CUStr(tmpstr);
}

UIRect UIUtils::GetScreenSize() {
    return UIRect(0, 0, GetSystemMetrics(SM_CXSCREEN),
                  GetSystemMetrics(SM_CYSCREEN));
}

UIRect UIUtils::GetWorkAreaSize() {
    UIRect ret;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &(ret.rect()), 0);
    return ret;
}

shared_ptr_tchar UIUtils::SafeTStr(size_t v_len) {
    return shared_ptr_tchar(new TCHAR[v_len]);
}

shared_ptr_char UIUtils::SafeStr(size_t v_len) {
    return shared_ptr_char(new char[v_len]);
}

shared_ptr_wchar UIUtils::SafeWStr(size_t v_len) {
    return shared_ptr_wchar(new wchar_t[v_len]);
}

shared_ptr_byte UIUtils::SafeBYTE(size_t v_len) {
    return shared_ptr_byte(new BYTE[v_len]);
}

shared_ptr_wchar UIUtils::Convert2WStr(LPCSTR v_str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, v_str, -1, NULL, 0);
    auto ret = SafeWStr(len);
    MultiByteToWideChar(CP_UTF8, 0, v_str, -1, ret.get(), len);
    return ret;
}

shared_ptr_wchar UIUtils::Convert2WStr(LPCWSTR v_str) {
    int len = wcslen(v_str);
    auto ret = SafeWStr(len);
    wcscpy_s(ret.get(), len, v_str);
    return ret;
}

shared_ptr_char UIUtils::Convert2Str(LPCWSTR v_str) {
    int len = WideCharToMultiByte(CP_ACP, 0, v_str, -1, NULL, 0, NULL, NULL);
    auto ret = SafeStr(len);
    WideCharToMultiByte(CP_ACP, 0, v_str, -1, ret.get(), len, NULL, NULL);
    return ret;
}

shared_ptr_char UIUtils::Convert2Str(LPCSTR v_str) {
    int len = strlen(v_str);
    auto ret = SafeStr(len);
    strcpy_s(ret.get(), len, v_str);
    return ret;
}

shared_ptr_tchar UIUtils::Convert2TStr(LPCSTR v_str) {
#ifdef _UNICODE
    return Convert2WStr(v_str);
#else
    return Convert2Str(v_str);
#endif
}

shared_ptr_tchar UIUtils::Convert2TStr(LPCWSTR v_str) {
#ifdef _UNICODE
    return Convert2WStr(v_str);
#else
    return Convert2Str(v_str);
#endif
}

////////////////////////////////////////

UIString::UIString() {}

UIString::UIString(const LL v_digit) {
    buffer_ = tostring(v_digit);
}

UIString::UIString(LPCTSTR v_str, size_t v_len /*= -1*/) {
    Assign(v_str, v_len);
}

UIString::UIString(const UIString& v_src) {
    buffer_ = v_src.buffer_;
}

UIString::UIString(UIString&& v_src) {
    buffer_ = move(v_src.buffer_);
}

UIString::~UIString() {}

void UIString::Append(LPCTSTR v_str) {
    buffer_.append(v_str);
}

void UIString::Assign(LPCTSTR v_str, size_t v_len /*= -1*/) {
    if (v_len == size_t(-1))
        buffer_.assign(v_str);
    else
        buffer_.assign(v_str, v_len);
}

bool UIString::IsEmpty() const {
    return buffer_.empty();
}

void UIString::Empty() {
    buffer_.clear();
}

size_t UIString::GetLength() const {
    return buffer_.length();
}

void UIString::SetAt(size_t v_index, TCHAR v_ch) {
    buffer_[v_index] = v_ch;
}

TCHAR UIString::GetAt(size_t v_index) const {
    return buffer_[v_index];
}

shared_ptr_char UIString::CreateStr() const {
    return UIUtils::Convert2Str(buffer_.c_str());
}

shared_ptr_wchar UIString::CreateWStr() const {
    return UIUtils::Convert2WStr(buffer_.c_str());
}

LPCTSTR UIString::GetData() const {
    return buffer_.c_str();
}

LL UIString::Str2LL() const {
    return std::stoll(buffer_.c_str(), nullptr, 10);
}

double UIString::Str2Double() const {
    return std::stod(buffer_.c_str());
}

UIString UIString::Str2Hex() const {
    UIString ret;
    size_t len = buffer_.size();
    TCHAR buf[10];
    for (size_t i = 0; i < len; ++i) {
        if (buffer_[i] >= 256 || buffer_[i] < 0)
            break;
        _stprintf(buf, _T("%X"), (unsigned char)buffer_[i]);
        ret += buf;
    }
    return ret;
}

UIString UIString::Int2Hex() const {
    TCHAR buf[64];
    _i64tot(Str2LL(), buf, 16);
    return UIString(buf).ToUpper();
}

UIString UIString::Hex2Str() const {
    UIString ret;
    size_t len = buffer_.size();
    if (len % 2)
        --len;
    TCHAR buf[3] = { 0 };
    for (size_t i = 0; i < len; i+=2) {
        buf[0] = buffer_[i];
        buf[1] = buffer_[i + 1];
        buf[2] = '\0';
        ret += UIString(std::stoll(buf, nullptr, 16));
    }
    return ret;
}

UIString::operator LPCTSTR() const {
    return GetData();
}

TCHAR UIString::operator[] (int v_index) const {
    return GetAt(v_index);
}

UIString& UIString::operator=(const TCHAR v_ch) {
    buffer_ = v_ch;
    return *this;
}

UIString& UIString::operator=(LPCTSTR v_str) {
    Assign(v_str);
    return *this;
}

UIString& UIString::operator=(UIString& v_str) {
    buffer_ = v_str.buffer_;
    return *this;
}

UIString& UIString::operator=(UIString&& v_str) {
    buffer_ = move(v_str.buffer_);
    return *this;
}

UIString UIString::operator+(LPCTSTR v_str) const {
    UIString tmp = *this;
    tmp.Append(v_str);
    return tmp;
}

UIString& UIString::operator+=(LPCTSTR v_str) {
    Append(v_str);
    return *this;
}

UIString& UIString::operator+=(const TCHAR v_ch) {
    TCHAR v_str[] = { v_ch, _T('\0') };
    Append(v_str);
    return *this;
}

bool UIString::operator == (LPCTSTR v_str) const { return (Compare(v_str) == 0); }
bool UIString::operator != (LPCTSTR v_str) const { return (Compare(v_str) != 0); }
bool UIString::operator <= (LPCTSTR v_str) const { return (Compare(v_str) <= 0); }
bool UIString::operator <  (LPCTSTR v_str) const { return (Compare(v_str) < 0); }
bool UIString::operator >= (LPCTSTR v_str) const { return (Compare(v_str) >= 0); }
bool UIString::operator >  (LPCTSTR v_str) const { return (Compare(v_str) > 0); }


int UIString::Compare(LPCTSTR v_str) const {
    return buffer_.compare(v_str);
}

int UIString::CompareNoCase(LPCTSTR v_str) const {
    return _tcsicmp(buffer_.c_str(), v_str);
}

void UIString::MakeUpper() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::toupper);
}

void UIString::MakeLower() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::tolower);
}

UIString UIString::ToUpper() const {
    UIString ret = *this;
    ret.MakeUpper();
    return ret;
}

UIString UIString::ToLower() const {
    UIString ret = *this;
    ret.MakeLower();
    return ret;
}

UIString UIString::Left(size_t v_len) const {
    return Mid(0, v_len);
}

UIString UIString::Mid(size_t v_pos, size_t v_len) const {
    return UIString(buffer_.substr(v_pos, v_len).c_str());
}

UIString UIString::Right(size_t v_len) const {
    LL pos = GetLength() - v_len;
    if (pos < 0) {
        pos = 0;
        v_len = GetLength();
    }
    return Mid(pos, v_len);
}

LL UIString::Find(TCHAR v_ch, size_t v_pos /*= 0*/) const {
    size_t ret = buffer_.find(v_ch, v_pos);
    return (ret == tstring::npos) ? (LL)-1 : ret;
}

LL UIString::Find(LPCTSTR v_str, size_t v_pos /*= 0*/) const {
    size_t ret = buffer_.find(v_str, v_pos);
    return (ret == tstring::npos) ? (LL)-1 : ret;
}

size_t UIString::Replace(LPCTSTR v_str_from, LPCTSTR v_str_to) {
    size_t cnt = 0;
    size_t steplen = _tcslen(v_str_to);
    for (tstring::size_type pos(0); pos != tstring::npos;
         pos += steplen) {
        if ((pos = buffer_.find(v_str_from, pos)) != tstring::npos) {
            buffer_.replace(pos, _tcslen(v_str_from), v_str_to);
            ++cnt;
        } else {
            break;
        }
    }
    return cnt;
}

int UIString::Format(LPCTSTR v_str, ...) {
    LPTSTR tmp = nullptr;
    va_list argList;
    int len;
    va_start(argList, v_str);
    len = _vsntprintf(NULL, 0, v_str, argList);
    tmp = reinterpret_cast<TCHAR*>(malloc((len + 1) * sizeof(TCHAR)));
    ZeroMemory(tmp, (len + 1) * sizeof(TCHAR));
    int ret = _vsntprintf(tmp, len + 1, v_str, argList);
    va_end(argList);
    Assign(tmp);
    free(tmp);
    return ret;
}

////////////////////////////////////////

UIRect::UIRect() {}

UIRect::UIRect(long v_left, long v_top, long v_right, long v_bottom) {
    SetRect(v_left, v_top, v_right, v_bottom);
}

UIRect::UIRect(const RECT &v_rect)
    :rect_(v_rect) {}

UIRect::UIRect(const UIRect &v_src) {
    rect_ = v_src.rect_;
}

UIRect::~UIRect() {}

void UIRect::SetRect(long v_left, long v_top, long v_right, long v_bottom) {
    left = v_left;
    top = v_top;
    right = v_right;
    bottom = v_bottom;
}

const UIRect& UIRect::operator=(const RECT& v_rect) {
    rect_ = v_rect;
    return *this;
}

const UIRect& UIRect::operator=(const UIRect& v_src) {
    rect_ = v_src.rect_;
    return *this;
}

bool UIRect::operator==(const RECT& v_rect) const {
    return (rect_.left == v_rect.left &&
            rect_.top == v_rect.top &&
            rect_.right == v_rect.right &&
            rect_.bottom == v_rect.bottom);
}

bool UIRect::operator!=(const RECT& v_rect) const {
    return !(*this == v_rect);
}

UIRect::operator RECT() {
    return rect();
}

RECT& UIRect::rect() {
    return rect_;
}

long UIRect::width() const {
    return right - left;
}

long UIRect::height() const {
    return bottom - top;
}

////////////////////////////////////////

UIEvent::UIEvent() {}

UIEvent::UIEvent(WindowMessage v_msg) :msg_(v_msg) {}

UIEvent::UIEvent(WPARAM v_wparam, LPARAM v_lparam)
    :wparam_(v_wparam), lparam_(v_lparam) {}

UIEvent::UIEvent(WindowMessage v_msg, WPARAM v_wparam, LPARAM v_lparam)
    :msg_(v_msg), wparam_(v_wparam), lparam_(v_lparam) {}

UIEvent::~UIEvent() {}

UIEvent::operator WindowMessage() const {
    return GetMsg();
}

bool UIEvent::SetMsgFromWinMsg(UINT v_winmsg) {
    bool ret = true;
    // TODO: Add new Msg
    switch (v_winmsg) {
    case WM_MOUSEMOVE:
        msg_ = kWM_MouseMove;
        break;
    case WM_LBUTTONDOWN:
        msg_ = kWM_LButtonDown;
        break;
    case WM_LBUTTONUP:
        msg_ = kWM_LButtonUp;
        break;
    case WM_RBUTTONDOWN:
        msg_ = kWM_RButtonDown;
        break;
    case WM_RBUTTONUP:
        msg_ = kWM_RButtonUp;
        break;
    case WM_LBUTTONDBLCLK:
        msg_ = kWM_LButtonDBClick;
        break;
    case WM_RBUTTONDBLCLK:
        msg_ = kWM_RButtonDBClick;
        break;
    case WM_MOUSELEAVE:
        msg_ = kWM_MouseLeave;
        break;
    default:
        ret = false;
        break;
    }
    return ret;
}

void UIEvent::SetPos(POINT v_pt) {
    lparam_ = MAKELPARAM(v_pt.x, v_pt.y);
}

POINT UIEvent::GetPos() const {
    POINT ret;
    ret.x = GET_X_LPARAM(lparam_);
    ret.y = GET_Y_LPARAM(lparam_);
    return ret;
}

////////////////////////////////////////

UIColor::UIColor() {}

UIColor::UIColor(const UIColor &v_color) {
    SetColor(v_color.a, v_color.r, v_color.g, v_color.b);
}

UIColor::UIColor(LPCTSTR v_colorstr) {
    UStr str(v_colorstr);
    if (str == _T("black"))
        str = _T("#000000");
    else if (str == _T("white"))
        str = _T("#FFFFFF");
    else if (str == _T("red"))
        str = _T("#FF0000");
    else if (str == _T("green"))
        str = _T("#00FF00");
    else if (str == _T("blue"))
        str = _T("#0000FF");
    else if (str == _T("yellow"))
        str = _T("#FFFF00");
    else if (str == _T("cyan"))
        str = _T("#00FFFF");
    else if (str == _T("purple"))
        str = _T("#FF00FF");
    else if (str == _T("gray"))
        str = _T("#C0C0C0");
    else if (str == _T("transparent"))
        str = _T("#00000000");
    if (str.GetLength() == 9)
        SetColor((ALPHA)str.Mid(1, 2).Hex2Str().Str2LL(),
                 (COLOR)str.Mid(3, 2).Hex2Str().Str2LL(),
                 (COLOR)str.Mid(5, 2).Hex2Str().Str2LL(),
                 (COLOR)str.Mid(7, 2).Hex2Str().Str2LL());
    else
        SetColor(255, (COLOR)str.Mid(1, 2).Hex2Str().Str2LL(),
                 (COLOR)str.Mid(3, 2).Hex2Str().Str2LL(),
                 (COLOR)str.Mid(5, 2).Hex2Str().Str2LL());
}

UIColor::UIColor(COLOR v_r, COLOR v_g, COLOR v_b) {
    SetColor(255, v_r, v_g, v_b);
}

UIColor::UIColor(ALPHA v_a, COLOR v_r, COLOR v_g, COLOR v_b) {
    SetColor(v_a, v_r, v_g, v_b);
}

UIColor::~UIColor() {}

const UIColor& UIColor::operator=(const UIColor &v_color) {
    SetColor(v_color.a, v_color.r, v_color.g, v_color.b);
    return *this;
}

void UIColor::SetColor(ALPHA v_a, COLOR v_r, COLOR v_g, COLOR v_b) {
    a_ = v_a;
    r_ = v_r;
    g_ = v_g;
    b_ = v_b;
}

CUStr UIColor::GetColorStr() const {
    return UStr(_T("#")) + UStr(a_).Int2Hex() + UStr(r_).Int2Hex() +
        UStr(g_).Int2Hex() + UStr(b_).Int2Hex();
}

}   // namespace DuiMini
