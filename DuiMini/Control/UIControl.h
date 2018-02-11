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
#define ATTR_MAP_BEGIN virtual void BeforeSetAttribute() {
#define DEFAULT_ATTR(attr, def) SetAttribute(attr, def);
#define PARENT_ATTR(parentclass) parentclass::BeforeSetAttribute();
#define ATTR_MAP_END }

class DUIMINI_API UIControl {
public:
    UIControl();
    virtual ~UIControl();

public:
    RECT SetPos(LPCTSTR v_pos);     // v_pos must have 4 param
    RECT GetPos() const;

public:
    // Attribute
    ATTR_MAP_BEGIN
        DEFAULT_ATTR(_T("name"), _T("Static"))
        DEFAULT_ATTR(_T("pos"), _T("0,0"))
        DEFAULT_ATTR(_T("width"), _T("0"))
        DEFAULT_ATTR(_T("height"), _T("0"))
        DEFAULT_ATTR(_T("size"), _T("0,0"))
        ATTR_MAP_END
    virtual void SetAttribute(LPCTSTR v_name, LPCTSTR v_value);
    virtual void AfterSetAttribute();   // Init others which based on attribute
    virtual CUStr GetAttribute(LPCTSTR v_name) const;

    virtual void Paint() = 0;

    // Parent&Base
    virtual void SetParent(UIControl* v_parent);
    virtual UIControl* GetParent() const;
    virtual void SetBaseWindow(UIWindow* v_basewnd);
    virtual UIWindow* GetBaseWindow() const;
    virtual LPVOID GetInterface(LPCTSTR v_name);

    /**
     * Check if point in control rect
     * @param    POINT v_pt:point
     * @return   if ctrl contains v_pt ret true.
     */
    bool PtInRect(POINT v_pt);

    /**
     * fint ctrl cover pt
     * @param    POINT v_pt:point
     * @return   if v_pt is in the ctrl return pointer, otherwise nullptr
     * This function will return the deepest control pointer contains v_pt.
     */
    virtual UIControl* FindCtrlFromPT(POINT v_pt);

    virtual UIControl* FindCtrlFromName(LPCTSTR v_name); // find ctrl with name

    virtual RECT UpdatePos();   // Update pos from attribute

public:
    /**
    * Event
    * Call base class function at the first if you override them
    */
    virtual bool Event(WindowMessage v_msg,
                       WPARAM v_wparam, LPARAM v_lparam);

    // Msg handler bind
    void SetMsgHandler(WindowMessage v_msg, MsgHandleFun v_func);
    MsgHandleFun GetMsgHandler(WindowMessage v_msg) const;

    bool SetIndependent(BOOL v_independent = TRUE);

protected:
    // Skin change
    virtual void OnSkinChange(SKINID v_former, SKINID v_new);
    // language change
    virtual void OnLangChange(LANGID v_former, LANGID v_new);

    enum StrLoc {
        left, top, right, bottom
    };
    /**
     * Parse str to pos
     * @param    LPCTSTR v_str: pos str. e.g. |10
     * @param    StrLoc v_loc: pos location
     * @param    UIControl* v_parent:parent ctrl, nullptr for auto recognize
     * @return   real pos value
     */
    virtual int GetPosFromStr(LPCTSTR v_str, StrLoc v_loc,
                              UIControl* v_parent = nullptr) const;

protected:
    bool independent_ = true;            // independent ctrl
    UIControl* parent_ = nullptr;        // control parent
    UIWindow* basewnd_ = nullptr;        // attatch the window
    UIAttr attr_;                        // attribute
    RECT rect_{ 0, 0, 0, 0 };            // control rect
    MsgHandleFun msgmap_[kWM_End_] = { 0 };     // message map
};
}   // namespace DuiMini
