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
#include "DuiMini.h"
#include "UIUtils.h"

namespace DuiMini {
UIString::UIString() {
    buffer_ = _T("");
}

UIString::UIString(const TCHAR ch) {
    buffer_ = ch;
}

UIString::UIString(const int val) {
    TCHAR buf[64];
    _itot(val, buf, 10);
    buffer_ = buf;
}

UIString::UIString(LPCTSTR str, int len /*= -1*/) {
    Assign(str, len);
}

UIString::UIString(const UIString& src) {
    buffer_ = src.buffer_;
}

UIString::~UIString() {}

int UIString::GetLength() const {
    return buffer_.length();
}

UIString::operator LPCTSTR() const {
    return GetData();
}

void UIString::Append(LPCTSTR str) {
    buffer_.append(str);
}

void UIString::Assign(LPCTSTR str, int len /*= -1*/) {
    if (len == -1)
        buffer_.assign(str);
    else
        buffer_.assign(str, len);
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

TCHAR UIString::GetAt(int index) const {
    return buffer_[index];
}

TCHAR UIString::operator[] (int index) const {
    return GetAt(index);
}

const UIString& UIString::operator=(LPCTSTR str) {
    Assign(str);
    return *this;
}

const UIString& UIString::operator=(const TCHAR ch) {
    buffer_ = ch;
    return *this;
}

UIString UIString::operator+(LPCTSTR str) const {
    UIString tmp = *this;
    tmp.Append(str);
    return tmp;
}

const UIString& UIString::operator+=(LPCTSTR str) {
    Append(str);
    return *this;
}

const UIString& UIString::operator+=(const TCHAR ch) {
    TCHAR str[] = { ch, _T('\0') };
    Append(str);
    return *this;
}

bool UIString::operator == (LPCTSTR str) const { return (Compare(str) == 0); }
bool UIString::operator != (LPCTSTR str) const { return (Compare(str) != 0); }
bool UIString::operator <= (LPCTSTR str) const { return (Compare(str) <= 0); }
bool UIString::operator <  (LPCTSTR str) const { return (Compare(str) < 0); }
bool UIString::operator >= (LPCTSTR str) const { return (Compare(str) >= 0); }
bool UIString::operator >  (LPCTSTR str) const { return (Compare(str) > 0); }

void UIString::SetAt(int index, TCHAR ch) {
    buffer_[index] = ch;
}

int UIString::Compare(LPCTSTR str) const {
    return buffer_.compare(str);
}

int UIString::CompareNoCase(LPCTSTR str) const {
    return _tcsicmp(buffer_.c_str(), str);
}

void UIString::MakeUpper() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::toupper);
}

void UIString::MakeLower() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::tolower);
}

UIString UIString::Left(int len) const {
    return UIString(buffer_.c_str(), len);
}

UIString UIString::Mid(int pos, int len) const {
    return UIString(buffer_.substr(pos, len).c_str());
}

UIString UIString::Right(int len) const {
    int pos = GetLength() - len;
    if (pos < 0) {
        pos = 0;
        len = GetLength();
    }
    return Mid(pos, len);
}

int UIString::Find(TCHAR ch, int pos /*= 0*/) const {
    return buffer_.find(ch, pos);
}

int UIString::Find(LPCTSTR str, int pos /*= 0*/) const {
    return buffer_.find(str, pos);
}

int UIString::Replace(LPCTSTR str_from, LPCTSTR str_to) {
    int cnt = 0;
    for (tstring::size_type pos(0); pos != tstring::npos; pos += _tcslen(str_to)) {
        if ((pos = buffer_.find(str_from, pos)) != tstring::npos) {
            buffer_.replace(pos, _tcslen(str_from), str_to);
            ++cnt;
        }
        else
            break;
    }
    return cnt;
}

int UIString::Format(LPCTSTR str, ...) {
    LPTSTR tmp = NULL;
    va_list argList;
    int len;
    va_start(argList, str);
    len = _vsntprintf(NULL, 0, str, argList);
    tmp = reinterpret_cast<TCHAR*>(malloc((len + 1) * sizeof(TCHAR)));
    ZeroMemory(tmp, (len + 1) * sizeof(TCHAR));
    int ret = _vsntprintf(tmp, len + 1, str, argList);
    va_end(argList);
    Assign(tmp);
    free(tmp);
    return ret;
}

}   // namespace DuiMini
