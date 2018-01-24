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
    // User interface
    RECT SetPos(LPCTSTR v_pos);
    RECT GetPos() const;
    void Invalidate() const;
    CUStr GetAttribute(LPCTSTR v_name) const;

public:
    // Attribute
    virtual void SetDefaultAttr();
    /**
     * DO NOT call it manually! If you must do, call AfterSetAttribute()
     * to prevent some strange act.
     */
    virtual void SetAttribute(LPCTSTR v_name, LPCTSTR v_value);
    virtual void AfterSetAttribute();

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

    // Event
    //virtual void Event(TEventUI& event);

private:
    enum StrLoc {
        left, top, right, bottom
    };
    /**
     * Parse str to pos
     * @param    LPCTSTR v_str: pos str. e.g. |10
     * @param    StrLoc v_loc: pos location
     * @return   real pos value
     */
    int GetPosFromStr(LPCTSTR v_str, StrLoc v_loc) const; 

protected:
    UIControl* parent_ = nullptr;        // control parent
    UIWindow* basewnd_ = nullptr;        // attatch the window
    UIAttr attr_;                        // attribute
    RECT rect_;                          // control rect
};
}   // namespace DuiMini
