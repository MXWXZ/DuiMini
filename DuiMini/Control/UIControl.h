/**
* Copyright (c) 2017-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2017/11/28
*
* @Description:
*/
#pragma once

namespace DuiMini {
class UIWindow;
class DUIMINI_API UIControl {
public:
    UIControl();
    virtual ~UIControl();

public:
    RECT SetPos(LPCTSTR v_pos);
    RECT GetPos() const;
    void Invalidate() const;
    CUStr GetAttribute(LPCTSTR v_name) const;

public:
    // Attribute
    /**
     * DO NOT call it manually! If you must do, call AfterSetAttribute()
     * to prevent some strange act.
     */
    virtual void BeforeSetAttribute();  // Init attribute
    virtual void SetAttribute(LPCTSTR v_name, LPCTSTR v_value);
    virtual void AfterSetAttribute();   // Init others which based on attribute

    virtual void DoPaint(HWND v_hwnd, IUIRender* v_render) = 0;

    // Parent&Base
    virtual void SetParent(UIControl* v_parent);
    virtual UIControl* GetParent() const;
    virtual void SetBaseWindow(UIWindow* v_basewnd);
    virtual UIWindow* GetBaseWindow() const;
    virtual LPVOID GetInterface(LPCTSTR v_name);

    RECT UpdatePos();   // Update pos from attribute

    /**
     * fint ctrl cover pt
     * @param    POINT v_pt:point
     * @return   if v_pt is in the ctrl return pointer, otherwise nullptr
     */
    virtual UIControl* FindCtrlFromPT(POINT v_pt);

public:
    // Event
    // virtual void Event(TEventUI& event);
    virtual void OnChangeSkin();      // skin changed
    virtual void OnChangeLanguage();  // language changed

protected:
    enum StrLoc {
        left, top, right, bottom
    };
    /**
     * Parse str to pos
     * @param    LPCTSTR v_str: pos str. e.g. |10
     * @param    StrLoc v_loc: pos location
     * @return   real pos value
     */
    virtual int GetPosFromStr(LPCTSTR v_str, StrLoc v_loc) const;

protected:
    UIControl* parent_ = nullptr;        // control parent
    UIWindow* basewnd_ = nullptr;        // attatch the window
    UIAttr attr_;                        // attribute
    RECT rect_{ 0, 0, 0, 0 };            // control rect
};
}   // namespace DuiMini
