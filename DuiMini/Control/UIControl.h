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

#define STATE_FUNC_START(attr, param)            \
    LPCTSTR _attrstr = attr;                     \
    BOOL &_myparam = param;                      \
    bool ret = GetAttribute(_attrstr).Str2Int(); \
    if (_myparam >= 0) {
#define STATE_FUNC_END                           \
        SetAttribute(_attrstr, UStr(_myparam));  \
    }                                            \
    return ret;

class DUIMINI_API UIControl {
public:
    UIControl();
    virtual ~UIControl();

public:
    CUStr GetName() const;
    void SetPos(LPCTSTR v_pos);     // v_pos must have 4 param
    UIRect GetPos() const;
    long GetWidth() const;
    long GetHeight() const;

    bool DisableCtrl(BOOL v_disable = TRUE);
    /**
    * background
    * @param    BOOL v_bg:TRUE/FALSE Attach/Detach, STAY not change state
    * @return   former state
    */
    bool AttachBackground(BOOL v_bg);

public:
    // Attribute
    ATTR_MAP_BEGIN
        DEFAULT_ATTR(_T("name"), _T("Static"))
        DEFAULT_ATTR(_T("pos"), _T("0,0"))
        DEFAULT_ATTR(_T("width"), _T("0"))
        DEFAULT_ATTR(_T("height"), _T("0"))
        DEFAULT_ATTR(_T("size"), _T("0,0"))
        DEFAULT_ATTR(_T("background"), _T("0"))
        DEFAULT_ATTR(_T("disable"), _T("0"))
        ATTR_MAP_END
        virtual void SetAttribute(LPCTSTR v_name, LPCTSTR v_value);
    virtual void AfterSetAttribute();   // Init others which based on attribute
    virtual CUStr GetAttribute(LPCTSTR v_name) const;

    virtual void Paint(bool v_background = false) = 0;

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

    virtual UIRect UpdatePos();   // Update pos from attribute

public:
    /**
    * Event
    * Call base class function at the first if you override them
    */
    virtual bool Event(const UIEvent& v_event);

    // Msg handler bind
    void SetMsgHandler(WindowMessage v_msg, MsgHandleFun v_func);
    MsgHandleFun GetMsgHandler(WindowMessage v_msg) const;

protected:
    // TODO: Add new Msg

    // Skin change
    virtual bool OnSkinChange(const UIEvent& v_event) { return true; }
    // language change
    virtual bool OnLangChange(const UIEvent& v_event) { return true; }

    virtual bool OnMouseEnter(const UIEvent& v_event) { return true; }
    virtual bool OnMouseLeave(const UIEvent& v_event) { return true; }
    virtual bool OnMouseMove(const UIEvent& v_event) { return true; }
    virtual bool OnLButtonDown(const UIEvent& v_event) { return true; }
    virtual bool OnLButtonUp(const UIEvent& v_event) { return true; }
    virtual bool OnLButtonClick(const UIEvent& v_event) { return true; }
    virtual bool OnLButtonDBClick(const UIEvent& v_event) { return true; }
    virtual bool OnRButtonDown(const UIEvent& v_event) { return true; }
    virtual bool OnRButtonUp(const UIEvent& v_event) { return true; }
    virtual bool OnRButtonClick(const UIEvent& v_event) { return true; }
    virtual bool OnRButtonDBClick(const UIEvent& v_event) { return true; }
    virtual bool OnDisable(const UIEvent& v_event) { return true; }
    virtual bool OnActive(const UIEvent& v_event) { return true; }

    enum StrLoc {
        left, top, right, bottom
    };
    /**
     * Parse str to pos(one section)
     * @param    LPCTSTR v_str: pos str. e.g. |10
     * @param    StrLoc v_loc: pos location
     * @param    UIRect* v_parentrect:parent rect, nullptr for auto
     * @return   real pos value
     */
    int ParsePosStr(LPCTSTR v_str, StrLoc v_loc,
                    UIRect* v_parentrect = nullptr) const;

    // Parse entire str
    UIRect ParsePosStr(LPCTSTR v_str,
                       UIRect* v_parentrect = nullptr) const;

protected:
    UIControl* parent_ = nullptr;        // control parent
    UIWindow* basewnd_ = nullptr;        // attatch the window
    UIAttr attr_;                        // attribute
    UIRect rect_;                        // control rect
    MsgHandleFun msgmap_[kWM_End_] = { 0 };     // message map
};
}   // namespace DuiMini
