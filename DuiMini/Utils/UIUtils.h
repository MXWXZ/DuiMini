/************************************************************************
Copyright (c) 2017 MXWXZ
Public utils class
************************************************************************/
#pragma once
#ifndef DUIMINI_UTILS_UIUTILS_H_
#define DUIMINI_UTILS_UIUTILS_H_

namespace DuiMini {
class DUIMINI_API UIString {
 public:
    UIString();
    explicit UIString(const TCHAR ch);
    UIString(const UIString& src);
    UIString(LPCTSTR str, int len = -1);    // NOLINT
    ~UIString();
    UIString ToString();

    void Empty();
    int GetLength() const;
    bool IsEmpty() const;
    TCHAR GetAt(int index) const;
    void Append(LPCTSTR str);
    void Assign(LPCTSTR str, int len = -1);
    LPCTSTR GetData() const;

    void SetAt(int index, TCHAR ch);
    operator LPCTSTR() const;

    TCHAR operator[] (int index) const;
    const UIString& operator=(const UIString& src);
    const UIString& operator=(const TCHAR ch);
    const UIString& operator=(LPCTSTR str);
    UIString operator+(const UIString& src) const;
    UIString operator+(LPCTSTR str) const;
    const UIString& operator+=(const UIString& src);
    const UIString& operator+=(LPCTSTR str);
    const UIString& operator+=(const TCHAR ch);

    bool operator == (LPCTSTR str) const;
    bool operator != (LPCTSTR str) const;
    bool operator <= (LPCTSTR str) const;
    bool operator <  (LPCTSTR str) const;
    bool operator >= (LPCTSTR str) const;
    bool operator >  (LPCTSTR str) const;

    int Compare(LPCTSTR str) const;
    int CompareNoCase(LPCTSTR str) const;

    void MakeUpper();
    void MakeLower();

    UIString Left(int len) const;
    UIString Mid(int pos, int len = -1) const;
    UIString Right(int len) const;

    int Find(TCHAR ch, int pos = 0) const;
    int Find(LPCTSTR str, int pos = 0) const;
    int ReverseFind(TCHAR ch) const;
    int Replace(LPCTSTR str_from, LPCTSTR str_to);

    int __cdecl Format(LPCTSTR str, ...);

 protected:
    LPTSTR str_;
    TCHAR buffer_[kMax_String_Length + 1];
};
typedef UIString UStr;
typedef const UIString CUStr;

}   // namespace DuiMini

#endif  // DUIMINI_UTILS_UIUTILS_H_

