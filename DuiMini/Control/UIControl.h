/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
#define ATTR_MAP_BEGIN           virtual void BeforeSetAttribute() {
#define DEFAULT_ATTR(attr, def)     SetAttribute(attr, def);
#define PARENT_ATTR(parentclass)    parentclass::BeforeSetAttribute();
#define ATTR_MAP_END             }

#define STATE_FUNC_START(attr, param)            \
    LPCTSTR _attrstr = attr;                     \
    BOOL &_myparam = param;                      \
    bool ret = GetAttribute(_attrstr).Str2LL();  \
    if (_myparam >= 0) {
#define STATE_FUNC_END                           \
        SetAttribute(_attrstr, UStr(_myparam));  \
    }                                            \
    return ret;
#define INIT_STATE(x) x(x(STAY))

#define DEFAULT_MSGFUNC(func) virtual bool func(const UIEvent& v_event) { return true; }
#define OVERRIDE_MSGFUNC(func) bool func(const UIEvent& v_event) override;

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
    bool VisibleCtrl(BOOL v_visible = TRUE);
    /**
    * background
    * @param    BOOL v_bg:TRUE/FALSE Attach/Detach, STAY not change state
    * @return   former state
    */
    bool AttachBackground(BOOL v_bg);

    void SetAlpha(ALPHA v_alpha);
    ALPHA GetAlpha() const;
    void SetBorderSize(long v_border);
    long GetBorderSize() const;
    void SetBorderColor(LPCTSTR v_color);
    UIColor GetBorderColor() const;
    void SetToolTip(LPCTSTR v_str);
    CUStr GetToolTip() const;
    void SetToolTipWidth(long v_width);
    long GetToolTipWidth() const;

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
        DEFAULT_ATTR(_T("visible"), _T("1"))
        DEFAULT_ATTR(_T("alpha"), _T("255"))
        DEFAULT_ATTR(_T("bordercolor"), _T("black"))
        DEFAULT_ATTR(_T("bordersize"), _T("0"))
        DEFAULT_ATTR(_T("tooltip"), _T(""))
        DEFAULT_ATTR(_T("tooltipwidth"), _T("300"))
        ATTR_MAP_END
    virtual void SetAttribute(LPCTSTR v_name, LPCTSTR v_value);
    virtual void AfterSetAttribute();   // Init others which based on attribute
    virtual CUStr GetAttribute(LPCTSTR v_name) const;

    virtual void Paint(bool v_background = false);

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
    DEFAULT_MSGFUNC(OnSkinChange)
    // language change
    virtual bool OnLangChange(const UIEvent &v_event);

    DEFAULT_MSGFUNC(OnMouseEnter)
    DEFAULT_MSGFUNC(OnMouseLeave)
    DEFAULT_MSGFUNC(OnMouseMove)
    DEFAULT_MSGFUNC(OnLButtonDown)
    DEFAULT_MSGFUNC(OnLButtonUp)
    DEFAULT_MSGFUNC(OnLButtonClick)
    DEFAULT_MSGFUNC(OnLButtonDBClick)
    DEFAULT_MSGFUNC(OnRButtonDown)
    DEFAULT_MSGFUNC(OnRButtonUp)
    DEFAULT_MSGFUNC(OnRButtonClick)
    DEFAULT_MSGFUNC(OnRButtonDBClick)
    DEFAULT_MSGFUNC(OnDisable)
    DEFAULT_MSGFUNC(OnActive)
    DEFAULT_MSGFUNC(OnVisible)
    DEFAULT_MSGFUNC(OnInvisible)

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
    long ParsePosStr(LPCTSTR v_str, StrLoc v_loc,
                     UIRect* v_parentrect = nullptr) const;

    // Parse entire str
    UIRect ParsePosStr(LPCTSTR v_str,
                       UIRect* v_parentrect = nullptr) const;

    // return 'v_cnt'th item of v_str divided by ','
    CUStr DivideStr(LPCTSTR v_str, unsigned short v_cnt) const;

protected:
    UIControl* parent_ = nullptr;               // control parent
    UIWindow* basewnd_ = nullptr;               // attatch the window
    UIAttr attr_;                               // attribute
    UIRect rect_;                               // control rect
    MsgHandleFun msgmap_[kWM_End_] = { 0 };     // message map
};
}   // namespace DuiMini
