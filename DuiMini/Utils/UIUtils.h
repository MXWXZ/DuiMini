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
    explicit UIString(const TCHAR v_ch);
    explicit UIString(const int v_digit);
    UIString(const UIString& v_src);
    UIString(LPCTSTR v_str, int v_len = -1);
    ~UIString();

public:
    void Empty();
    int GetLength() const;
    bool IsEmpty() const;
    TCHAR GetAt(int v_index) const;
    void Append(LPCTSTR v_str);
    void Assign(LPCTSTR v_str, int v_len = -1);
    LPCTSTR GetData() const;
    int Str2Int() const;

    void SetAt(int v_index, TCHAR v_ch);
    operator LPCTSTR() const;

    TCHAR operator[] (int v_index) const;
    const UIString& operator=(const TCHAR v_ch);
    const UIString& operator=(LPCTSTR v_str);
    UIString operator+(LPCTSTR v_str) const;
    const UIString& operator+=(LPCTSTR v_str);
    const UIString& operator+=(const TCHAR v_ch);

    bool operator == (LPCTSTR v_str) const;
    bool operator != (LPCTSTR v_str) const;
    bool operator <= (LPCTSTR v_str) const;
    bool operator <  (LPCTSTR v_str) const;
    bool operator >= (LPCTSTR v_str) const;
    bool operator >  (LPCTSTR v_str) const;

    int Compare(LPCTSTR v_str) const;
    int CompareNoCase(LPCTSTR v_str) const;

    void MakeUpper();
    void MakeLower();

    UIString Left(int v_len) const;
    UIString Mid(int v_pos, int v_len) const;
    UIString Right(int v_len) const;

    int Find(TCHAR v_ch, int v_pos = 0) const;
    int Find(LPCTSTR v_str, int v_pos = 0) const;
    int Replace(LPCTSTR v_str_from, LPCTSTR v_str_to);

    int __cdecl Format(LPCTSTR v_str, ...);

protected:
    tstring buffer_ = _T("");
};
typedef UIString UStr;
typedef const UIString CUStr;

////////////////////////////////////////

typedef std::map<UStr, UStr> SSMap;
typedef std::map<UStr, UStr>::iterator SSMapIt;
typedef std::map<UStr, UStr>::const_iterator SSMapCIt;
class DUIMINI_API UIAttr {
public:
    UIAttr();
    ~UIAttr();

public:
    SSMapIt GetBegin();
    SSMapIt GetEnd();

    /**
     * Get attribute value
     * @return   value, empty string for not find
     * Warning!This function will NOT check if v_name is valid, if not, it will
     * add an empty string value.
     */
    UStr& operator[] (LPCTSTR v_name);

    /**
     * SAFELY Get attribute value
     * @return   value, empty string for not find
     * This function will check if v_name is valid and will NOT add anything
     */
    CUStr GetValue(LPCTSTR v_name) const;

private:
    SSMap attribute_;
};

typedef const UIAttr CUIAttr;

////////////////////////////////////////

typedef std::map<int, UIAttr> IAMap;
typedef std::map<int, UStr>::iterator IAMapIt;
typedef std::map<int, UStr>::const_iterator IAMapCIt;
class DUIMINI_API UIAttrSet {
public:
    UIAttrSet();
    ~UIAttrSet();

public:
    /**
     * WARNING!Make sure v_pos is valid!
     * ONLY use this to modify or get UIAttr value,
     * DO NOT use this to add new value!!!  
     */
    UIAttr& operator[] (const int v_pos);

    /**
     * SAFELY get value
     */
    CUIAttr GetValue(const int v_pos);

    void AddAttr(const UIAttr &v_value);
    int GetSize() const;
    void Clear();

    /**
     * Find attribute name and value
     * @param    int v_start:start pos(include)
     * @param    LPCTSTR v_attr:attribute name
     * @param    LPCTSTR v_value:attribute value, stay empty for anything
     *                           existing. 
     * @return   -1 for not find,otherwise is the positon
     */
    int FindNextAttr(int v_start, LPCTSTR v_attr, LPCTSTR v_value = _T(""));

private:
    IAMap attribute_set_;
    int size_ = 0;
};

////////////////////////////////////////

class DUIMINI_API UIXmlNode {
public:
    UIXmlNode();
    explicit UIXmlNode(const xmlnode v_node);
    ~UIXmlNode();

public:
    void SetNode(const xmlnode v_node);
    CUStr GetAttrValue(LPCTSTR v_name, LPCTSTR v_default = _T("")) const;
    CUStr GetAttrValue(LPCTSTR v_name, const int v_default) const;
    bool CmpAttrValue(LPCTSTR v_name, LPCTSTR v_value) const;
    bool CmpNodeName(LPCTSTR v_name) const;

private:
    xmlnode node_ = nullptr;
};

////////////////////////////////////////

struct DUIMINI_API UIFont {
    UStr name_;
    UStr lang_;
    UStr font_;
    UINT size_;
    bool bold_;
    bool italic_;
    bool underline_;
    bool strikeout_;
};

////////////////////////////////////////

class DUIMINI_API UIPtrArray {
public:
    explicit UIPtrArray(UINT v_size = 0);
    ~UIPtrArray();

public:
    void Empty();
    void Resize(UINT v_size);
    bool IsEmpty() const;
    int Find(LPVOID v_index) const;
    bool Add(LPVOID v_data);
    bool SetAt(UINT v_index, LPVOID v_data);
    bool InsertAt(UINT v_index, LPVOID v_data);
    bool Remove(UINT v_index);
    UINT GetSize() const;
    LPVOID* GetData();

    LPVOID GetAt(UINT v_index) const;
    LPVOID operator[] (UINT v_index) const;

protected:
    LPVOID* ptrvoid_ = nullptr;
    UINT count_ = 0;
    UINT allocated_ = 0;
};

////////////////////////////////////////

class DUIMINI_API UIUtils {
public:
    /**
    * Get current path
    * @return   current dir
    * the path does NOT include the \\ and file name at the end
    * e.g. C:\\windows\\system32
    */
    static CUStr GetCurrentDir();

    /**
     * Get formated time string
     * @param    LPCTSTR v_str:time format string (%Y %m %d %H %M %S)
     * @return   formated time string
     */
    static CUStr GetTimeStr(LPCTSTR v_str);
};

}   // namespace DuiMini
