/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIUtils.h"

namespace DuiMini {
UIString::UIString() : str_(buffer_) {
    buffer_[0] = _T('\0');
}

UIString::UIString(const TCHAR ch) : str_(buffer_) {
    buffer_[0] = ch;
    buffer_[1] = _T('\0');
}

UIString::UIString(LPCTSTR str, int len) : str_(buffer_) {
    assert(!IsBadStringPtr(str, -1) || str == NULL);
    buffer_[0] = _T('\0');
    Assign(str, len);
}

UIString::UIString(const UIString& src) : str_(buffer_) {
    buffer_[0] = _T('\0');
    Assign(src.str_);
}

UIString::~UIString() {
    if (str_ != buffer_)
        free(str_);
}

UIString UIString::ToString() {
    return str_;
}

int UIString::GetLength() const {
    return static_cast<int>(_tcslen(str_));
}

UIString::operator LPCTSTR() const {
    return str_;
}

void UIString::Append(LPCTSTR str) {
    int len = GetLength() + static_cast<int>(_tcslen(str));
    if (len >= kMax_String_Length) {
        if (str_ == buffer_) {
            str_ = static_cast<LPTSTR>(malloc((len + 1) * sizeof(TCHAR)));
            _tcscpy(str_, buffer_);
            _tcscat(str_, str);
        } else {
            str_ = static_cast<LPTSTR>
                (realloc(str_, (len + 1) * sizeof(TCHAR)));
            _tcscat(str_, str);
        }
    } else {
        if (str_ != buffer_) {
            free(str_);
            str_ = buffer_;
        }
        _tcscat(buffer_, str);
    }
}

void UIString::Assign(LPCTSTR str, int len) {
    if (str == NULL)
        str = _T("");
    len = (len < 0 ? static_cast<int>(_tcslen(str)) : len);
    if (len < kMax_String_Length) {
        if (str_ != buffer_) {
            free(str_);
            str_ = buffer_;
        }
    } else if (len > GetLength() || str_ == buffer_) {
        if (str_ == buffer_) str_ = NULL;
        str_ = static_cast<LPTSTR>(realloc(str_, (len + 1) * sizeof(TCHAR)));
    }
    _tcsncpy(str_, str, len);
    str_[len] = _T('\0');
}

bool UIString::IsEmpty() const {
    return str_[0] == _T('\0');
}

void UIString::Empty() {
    if (str_ != buffer_) free(str_);
    str_ = buffer_;
    buffer_[0] = _T('\0');
}

LPCTSTR UIString::GetData() const {
    return str_;
}

TCHAR UIString::GetAt(int index) const {
    return str_[index];
}

TCHAR UIString::operator[] (int index) const {
    return str_[index];
}

const UIString& UIString::operator=(const UIString& src) {
    Assign(src);
    return *this;
}

const UIString& UIString::operator=(LPCTSTR str) {
    if (str) {
        assert(!IsBadStringPtr(str, -1));
        Assign(str);
    } else {
        Empty();
    }
    return *this;
}

const UIString& UIString::operator=(const TCHAR ch) {
    Empty();
    buffer_[0] = ch;
    buffer_[1] = _T('\0');
    return *this;
}

UIString UIString::operator+(const UIString& src) const {
    UIString sTemp = *this;
    sTemp.Append(src);
    return sTemp;
}

UIString UIString::operator+(LPCTSTR str) const {
    if (str) {
        assert(!IsBadStringPtr(str, -1));
        UIString tmp = *this;
        tmp.Append(str);
        return tmp;
    }

    return *this;
}

const UIString& UIString::operator+=(const UIString& src) {
    Append(src);
    return *this;
}

const UIString& UIString::operator+=(LPCTSTR str) {
    if (str) {
        assert(!IsBadStringPtr(str, -1));
        Append(str);
    }

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
    assert(index >= 0 && index < GetLength());
    str_[index] = ch;
}

int UIString::Compare(LPCTSTR str) const {
    return _tcscmp(str_, str);
}

int UIString::CompareNoCase(LPCTSTR str) const {
    return _tcsicmp(str_, str);
}

void UIString::MakeUpper() {
    _tcsupr(str_);
}

void UIString::MakeLower() {
    _tcslwr(str_);
}

UIString UIString::Left(int len) const {
    if (len < 0)
        len = 0;
    if (len > GetLength())
        len = GetLength();
    return UIString(str_, len);
}

UIString UIString::Mid(int pos, int len) const {
    if (len < 0)
        len = GetLength() - pos;
    if (pos + len > GetLength())
        len = GetLength() - pos;
    if (len <= 0)
        return UIString();
    return UIString(str_ + pos, len);
}

UIString UIString::Right(int len) const {
    int pos = GetLength() - len;
    if (pos < 0) {
        pos = 0;
        len = GetLength();
    }
    return UIString(str_ + pos, len);
}

int UIString::Find(TCHAR ch, int pos /*= 0*/) const {
    assert(pos >= 0 && pos <= GetLength());
    if (pos != 0 && (pos < 0 || pos >= GetLength()))
        return -1;
    LPCTSTR tmp = _tcschr(str_ + pos, ch);
    if (tmp == NULL)
        return -1;
    return static_cast<int>(tmp - str_);
}

int UIString::Find(LPCTSTR str, int pos /*= 0*/) const {
    assert(!IsBadStringPtr(str, -1));
    assert(pos >= 0 && pos <= GetLength());
    if (pos != 0 && (pos < 0 || pos > GetLength()))
        return -1;
    LPCTSTR tmp = _tcsstr(str_ + pos, str);
    if (tmp == NULL)
        return -1;
    return static_cast<int>(tmp - str_);
}

int UIString::ReverseFind(TCHAR ch) const {
    LPCTSTR tmp = _tcsrchr(str_, ch);
    if (tmp == NULL)
        return -1;
    return static_cast<int>(tmp - str_);
}

int UIString::Replace(LPCTSTR str_from, LPCTSTR str_to) {
    UIString tmp;
    int count = 0;
    int pos = Find(str_from);
    if (pos < 0)
        return 0;
    int chfrom = static_cast<int>(_tcslen(str_from));
    int chto = static_cast<int>(_tcslen(str_to));
    while (pos >= 0) {
        tmp = Left(pos);
        tmp += str_to;
        tmp += Mid(pos + chfrom);
        Assign(tmp);
        pos = Find(str_from, pos + chto);
        count++;
    }
    return count;
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
