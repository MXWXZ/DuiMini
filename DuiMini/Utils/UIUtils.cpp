/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
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
    UIRect ret;
    ret.right = GetSystemMetrics(SM_CXSCREEN);
    ret.bottom = GetSystemMetrics(SM_CYSCREEN);
    return ret;
}

UIRect UIUtils::GetWorkAreaSize() {
    UIRect ret;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &(ret.rect()), 0);
    return ret;
}

UIAttr* UIUtils::FindNextCFGItem(UICFGItem &v_item, UINT v_start,
                                  LPCTSTR v_name, LPCTSTR v_value) {
    if (v_start >= v_item.size())
        return nullptr;
    UICFGItemIt &itend = v_item.end();
    for (UICFGItemIt it = v_item.begin() + v_start; it != itend; ++it)
        if (CmpStr((*it)[v_name], v_value))
            return &(*it);
    return nullptr;
}

////////////////////////////////////////

UIXmlNode::UIXmlNode() {}

UIXmlNode::UIXmlNode(const xmlnode v_node) {
    SetNode(v_node);
}

UIXmlNode::~UIXmlNode() {}

void UIXmlNode::SetNode(const xmlnode v_node) {
    node_ = v_node;
}

CUStr UIXmlNode::GetAttrValue(LPCTSTR v_name,
                              LPCTSTR v_default/* = _T("")*/) const {
    xmlattr attr = node_->first_attribute(v_name);
    if (!attr)
        return CUStr(v_default);
    else
        return CUStr(attr->value());
}

CUStr DuiMini::UIXmlNode::GetAttrValue(LPCTSTR v_name,
                                       const int v_default) const {
    return GetAttrValue(v_name, CUStr(v_default));
}

bool UIXmlNode::CmpAttrValue(LPCTSTR v_name, LPCTSTR value) const {
    return GetAttrValue(v_name) == value;
}

bool UIXmlNode::CmpNodeName(LPCTSTR v_name) const {
    return CmpStr(node_->name(), v_name);
}

////////////////////////////////////////

UIPtrArray::UIPtrArray(UINT v_size) {
    allocated_ = v_size;
    ptrvoid_ = reinterpret_cast<LPVOID*>(malloc(v_size * sizeof(LPVOID)));
    ZeroMemory(ptrvoid_, v_size * sizeof(LPVOID));
}

UIPtrArray::~UIPtrArray() {
    if (ptrvoid_ != nullptr)
        free(ptrvoid_);
}

void UIPtrArray::Empty() {
    if (ptrvoid_ != nullptr)
        free(ptrvoid_);
    ptrvoid_ = nullptr;
    count_ = allocated_ = 0;
}

void UIPtrArray::Resize(UINT v_size) {
    Empty();
    ptrvoid_ = reinterpret_cast<LPVOID*>(malloc(v_size * sizeof(LPVOID)));
    ZeroMemory(ptrvoid_, v_size * sizeof(LPVOID));
    allocated_ = v_size;
    count_ = v_size;
}

bool UIPtrArray::IsEmpty() const {
    return count_ == 0;
}

bool UIPtrArray::Add(LPVOID v_data) {
    if (++count_ >= allocated_) {
        allocated_ *= 2;
        if (allocated_ == 0)
            allocated_ = 11;
        ptrvoid_ = reinterpret_cast<LPVOID*>(realloc(ptrvoid_,
                                                allocated_ * sizeof(LPVOID)));
        if (!ptrvoid_)
            return false;
    }
    ptrvoid_[count_ - 1] = v_data;
    return true;
}

bool UIPtrArray::InsertAt(UINT v_index, LPVOID v_data) {
    if (v_index == count_)
        return Add(v_data);
    if (v_index < 0 || v_index > count_)
        return false;
    if (++count_ >= allocated_) {
        allocated_ *= 2;
        if (allocated_ == 0)
            allocated_ = 11;
        ptrvoid_ = reinterpret_cast<LPVOID*>(realloc(ptrvoid_,
                                                allocated_ * sizeof(LPVOID)));
        if (!ptrvoid_)
            return false;
    }
    memmove(&ptrvoid_[v_index + 1],
            &ptrvoid_[v_index], (count_ - v_index - 1) * sizeof(LPVOID));
    ptrvoid_[v_index] = v_data;
    return true;
}

bool UIPtrArray::SetAt(UINT v_index, LPVOID v_data) {
    if (v_index < 0 || v_index >= count_)
        return false;
    ptrvoid_[v_index] = v_data;
    return true;
}

bool UIPtrArray::Remove(UINT v_index) {
    if (v_index < 0 || v_index >= count_)
        return false;
    if (v_index < --count_)
        CopyMemory(ptrvoid_ + v_index,
                   ptrvoid_ + v_index + 1, (count_ - v_index) * sizeof(LPVOID));
    return true;
}

int UIPtrArray::Find(LPVOID v_data) const {
    for (UINT i = 0; i < count_; ++i)
        if (ptrvoid_[i] == v_data)
            return i;
    return -1;
}

UINT UIPtrArray::GetSize() const {
    return count_;
}

LPVOID* UIPtrArray::GetData() {
    return ptrvoid_;
}

LPVOID UIPtrArray::GetAt(UINT v_index) const {
    if (v_index < 0 || v_index >= count_)
        return nullptr;
    return ptrvoid_[v_index];
}

LPVOID UIPtrArray::operator[] (UINT v_index) const {
    if (v_index >= count_)
        return nullptr;
    return ptrvoid_[v_index];
}

////////////////////////////////////////

UIString::UIString() {}

UIString::UIString(const TCHAR v_ch) {
    buffer_ = v_ch;
}

UIString::UIString(const int v_digit) {
    TCHAR buf[64];
    _itot(v_digit, buf, 10);
    buffer_ = buf;
}

UIString::UIString(LPCTSTR v_str, size_t v_len /*= -1*/) {
    Assign(v_str, v_len);
}

UIString::UIString(const UIString& v_src) {
    buffer_ = v_src.buffer_;
}

UIString::~UIString() {}

size_t UIString::GetLength() const {
    return buffer_.length();
}

UIString::operator LPCTSTR() const {
    return GetData();
}

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

LPCTSTR UIString::GetData() const {
    return buffer_.c_str();
}

LL UIString::Str2LL() const {
    return _tcstoll(buffer_.c_str(), nullptr, 10);
}

UIString UIString::Str2Hex() const {
    UIString ret;
    size_t len = buffer_.size();
    TCHAR buf[10];
    for (size_t i = 0; i < len; ++i) {
        if (buffer_[i] >= 256 || buffer_[i] < 0)
            break;
        _stprintf(buf, _T("%X"), static_cast<unsigned char>(buffer_[i]));
        ret += buf;
    }
    return ret;
}

UIString UIString::Int2Hex() const {
    TCHAR buf[64];
    _itot(Str2LL(), buf, 16);
    UIString ret = buf;
    ret.MakeUpper();
    return ret;
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
        ret += UIString(_tcstol(buf, nullptr, 16));
    }
    return ret;
}

TCHAR UIString::GetAt(size_t v_index) const {
    return buffer_[v_index];
}

TCHAR UIString::operator[] (int v_index) const {
    return GetAt(v_index);
}

const UIString& UIString::operator=(LPCTSTR v_str) {
    Assign(v_str);
    return *this;
}

const UIString& UIString::operator=(const TCHAR v_ch) {
    buffer_ = v_ch;
    return *this;
}

UIString UIString::operator+(LPCTSTR v_str) const {
    UIString tmp = *this;
    tmp.Append(v_str);
    return tmp;
}

const UIString& UIString::operator+=(LPCTSTR v_str) {
    Append(v_str);
    return *this;
}

const UIString& UIString::operator+=(const TCHAR v_ch) {
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

void UIString::SetAt(size_t v_index, TCHAR v_ch) {
    buffer_[v_index] = v_ch;
}

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

UIString UIString::Left(size_t v_len) const {
    return UIString(buffer_.c_str(), v_len);
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
    return Mid(static_cast<size_t>(pos), v_len);
}

LL UIString::Find(TCHAR v_ch, size_t v_pos /*= 0*/) const {
    size_t ret = buffer_.find(v_ch, v_pos);
    return ret == tstring::npos ? -1 : (LL)ret;
}

LL UIString::Find(LPCTSTR v_str, size_t v_pos /*= 0*/) const {
    size_t ret = buffer_.find(v_str, v_pos);
    return ret == tstring::npos ? -1 : (LL)ret;
}

LL UIString::Replace(LPCTSTR v_str_from, LPCTSTR v_str_to) {
    LL cnt = 0;
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

UIRect::UIRect(const RECT &v_rect) {
    rect_ = v_rect;
}

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

WindowMessage UIEvent::GetMsg() const {
    return msg_;
}

WPARAM UIEvent::GetWParam() const {
    return wparam_;
}

LPARAM UIEvent::GetLParam() const {
    return lparam_;
}

void UIEvent::GetMsg(WindowMessage v_msg) {
    msg_ = v_msg;
}

void UIEvent::GetWParam(WPARAM v_wparam) {
    wparam_ = v_wparam;
}

void UIEvent::GetLParam(LPARAM v_lparam) {
    lparam_ = v_lparam;
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

UIColor::UIColor() {}

UIColor::UIColor(LPCTSTR v_colorstr) {
    UStr str(v_colorstr);
    SetColor((ALPHA)str.Mid(1, 2).Hex2Str().Str2LL(),
             (COLOR)str.Mid(3, 2).Hex2Str().Str2LL(),
             (COLOR)str.Mid(5, 2).Hex2Str().Str2LL(),
             (COLOR)str.Mid(7, 2).Hex2Str().Str2LL());
}

UIColor::UIColor(COLOR v_r, COLOR v_g, COLOR v_b) {
    SetColor(255, v_r, v_g, v_b);
}

UIColor::UIColor(ALPHA v_a, COLOR v_r, COLOR v_g, COLOR v_b) {
    SetColor(v_a, v_r, v_g, v_b);
}

UIColor::~UIColor() {}

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
