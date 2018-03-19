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
    UIString(LPCTSTR v_str, size_t v_len = -1);
    ~UIString();

public:
    void Empty();
    size_t GetLength() const;
    bool IsEmpty() const;
    TCHAR GetAt(size_t v_index) const;
    void Append(LPCTSTR v_str);
    void Assign(LPCTSTR v_str, size_t v_len = -1);
    LPCTSTR GetData() const;
    LL Str2LL() const;
    UIString Str2Hex() const;
    UIString Int2Hex() const;
    UIString Hex2Str() const;


    void SetAt(size_t v_index, TCHAR v_ch);
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

    UIString Left(size_t v_len) const;
    UIString Mid(size_t v_pos, size_t v_len) const;
    UIString Right(size_t v_len) const;

    LL Find(TCHAR v_ch, size_t v_pos = 0) const;
    LL Find(LPCTSTR v_str, size_t v_pos = 0) const;
    LL Replace(LPCTSTR v_str_from, LPCTSTR v_str_to);

    int __cdecl Format(LPCTSTR v_str, ...);

private:
    tstring buffer_ = _T("");
};
typedef UIString UStr;
typedef const UIString CUStr;

////////////////////////////////////////

typedef std::map<UStr, UStr> UIAttr;
typedef std::map<UStr, UStr>::iterator UIAttrIt;
typedef std::map<UStr, UStr>::const_iterator CUIAttrIt;
typedef std::vector<UIAttr> UICFGItem;
typedef std::vector<UIAttr>::iterator UICFGItemIt;
typedef std::vector<UIAttr>::const_iterator CUICFGItemIt;

////////////////////////////////////////

class DUIMINI_API UIEvent {
public:
    UIEvent();
    UIEvent(WindowMessage v_msg);
    UIEvent(WPARAM v_wparam, LPARAM v_lparam);
    UIEvent(WindowMessage v_msg, WPARAM v_wparam, LPARAM v_lparam);
    ~UIEvent();

public:
    operator WindowMessage() const;
    WindowMessage GetMsg() const;
    WPARAM GetWParam() const;
    LPARAM GetLParam() const;
    void GetMsg(WindowMessage v_msg);
    void GetWParam(WPARAM v_wparam);
    void GetLParam(LPARAM v_lparam);

    bool SetMsgFromWinMsg(UINT v_winmsg);

    void SetPos(POINT v_pt);
    POINT GetPos() const;

private:
    WindowMessage msg_ = kWM_Start_;
    WPARAM wparam_ = NULL;
    LPARAM lparam_ = NULL;
};

////////////////////////////////////////

class DUIMINI_API UIRect {
public:
    UIRect();
    UIRect(long v_left, long v_top, long v_right, long v_bottom);
    explicit UIRect(const RECT& v_rect);
    UIRect(const UIRect& v_src);
    ~UIRect();

public:
    void SetRect(long v_left, long v_top, long v_right, long v_bottom);

    const UIRect& operator=(const RECT& v_rect);
    const UIRect& operator=(const UIRect& v_src);
    bool operator == (const RECT& v_rect) const;
    bool operator != (const RECT& v_rect) const;

    operator RECT();

    RECT& rect();
    long width() const;
    long height() const;
    long &left = rect_.left;
    long &top = rect_.top;
    long &right = rect_.right;
    long &bottom = rect_.bottom;

private:
    RECT rect_{ 0,0,0,0 };
};

////////////////////////////////////////

class DUIMINI_API UIColor {
public:
    UIColor();
    UIColor(LPCTSTR v_colorstr);
    UIColor(COLOR v_r, COLOR v_g, COLOR v_b);
    UIColor(ALPHA v_a, COLOR v_r, COLOR v_g, COLOR v_b);
    ~UIColor();

public:
    void SetColor(ALPHA v_a, COLOR v_r, COLOR v_g, COLOR v_b);
    CUStr GetColorStr() const;
    ALPHA &a = a_;
    COLOR &r = r_;
    COLOR &g = g_;
    COLOR &b = b_;

private:
    ALPHA a_ = 255;
    COLOR r_ = 0;
    COLOR g_ = 0;
    COLOR b_ = 0;
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

    /**
     * Get full screen size 
     * @return   size rect
     */
    static UIRect GetScreenSize();

    /**
     * Get work area(without taskbar) size
     * @return   size rect
     */
    static UIRect GetWorkAreaSize();

    /**
     * Find next CFG item with v_name=v_value
     * @return   nullptr for not find
     */
    static UIAttr* FindNextCFGItem(UICFGItem &v_item, UINT v_start,
                                   LPCTSTR v_name, LPCTSTR v_value);
};

}   // namespace DuiMini
