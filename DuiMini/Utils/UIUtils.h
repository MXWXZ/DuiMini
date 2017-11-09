/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:Public utils class
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIString {
 public:
    UIString();
    explicit UIString(const TCHAR ch);
    explicit UIString(const int val);
    UIString(const UIString& src);
    UIString(LPCTSTR str, int len = -1);
    ~UIString();

    void Empty();
    int GetLength() const;
    bool IsEmpty() const;
    TCHAR GetAt(int index) const;
    void Append(LPCTSTR str);
    void Assign(LPCTSTR str, int len = -1);
    LPCTSTR GetData() const;
    int Str2Int();

    void SetAt(int index, TCHAR ch);
    operator LPCTSTR() const;

    TCHAR operator[] (int index) const;
    const UIString& operator=(const TCHAR ch);
    const UIString& operator=(LPCTSTR str);
    UIString operator+(LPCTSTR str) const;
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
    UIString Mid(int pos, int len) const;
    UIString Right(int len) const;

    int Find(TCHAR ch, int pos = 0) const;
    int Find(LPCTSTR str, int pos = 0) const;
    int Replace(LPCTSTR str_from, LPCTSTR str_to);

    int __cdecl Format(LPCTSTR str, ...);

 protected:
    tstring buffer_;
};
typedef UIString UStr;
typedef const UIString CUStr;

////////////////////////////////////////

typedef std::map<UStr, UStr> SSMap;
typedef std::pair<UStr, UStr> SSPair;
typedef std::map<UStr, UStr>::iterator SSMapIt;
class DUIMINI_API UIAttr {
public:
    UStr& operator[] (CUStr name);
    bool IsExist(LPCTSTR name);
    SSMapIt GetBegin();
    SSMapIt GetEnd();

private:
    SSMap attr_;
};

////////////////////////////////////////

class DUIMINI_API UIXmlNode {
public:
    explicit UIXmlNode(xmlnode node);
    void SetNode(xmlnode node);
    CUStr GetAttrValue(LPCTSTR name);
    bool CmpAttrValue(LPCTSTR name, LPCTSTR value);
    bool CmpNodeName(LPCTSTR name);

private:
    xmlnode node_;
};

////////////////////////////////////////

class DUIMINI_API UIUtils {
public:
    /**
    * Get the current path
    * @return   current dir
    * the path does NOT include the \\ and file name at the end
    * e.g. C:\\windows\\system32
    * WARNING!return value is temporary object and should be transfer to
    * another UStr object if you want to use it later
    */
    static CUStr GetCurrentDir();

    /**
     * Get formated time string
     * @param    LPCTSTR str:time format string (%Y %m %d %H %M %S)
     * @return   formated time string
     */
    static CUStr GetTimeStr(LPCTSTR str);
};

}   // namespace DuiMini
