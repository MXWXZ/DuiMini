/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/04
 *
 * @Description:
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIDialog;
class DUIMINI_API UIDlgBuilder {
public:
    UIDlgBuilder();
    ~UIDlgBuilder();

public:
    /**
     * [ER]Init from xmlnode and release the current one
     * @param    xmlnode v_root:xml root
     * @return   first ctrl
     */
    UIControl* Init(xmlnode v_root, UIWindow* v_wnd);

    /**
     * Create control
     * @param    UIControl* v_ctrl:allocated ctrl pointer
     * @param    UIWindow* v_wnd:base window
     * @param    UIControl* v_parent:parent ctrl
     * @return   created ctrl pointer
     * After this function, you can use SetAttribute to set the attr
     * when you finish, call FinishCreateControl;
     */
    UIControl* CreateControl(UIControl* v_ctrl, UIWindow* v_wnd,
                             UIControl* v_parent = nullptr);

    /**
     * Finish create control
     * @param    UIControl* v_ctrl:created ctrl pointer
     * @return   finish created ctrl pointer
     */
    void FinishCreateControl(UIControl* v_ctrl);

    UIDialog* GetCtrlRoot();

private:
    UIControl* Parse(UIWindow* v_wnd, xmlnode v_root,
                      UIControl* v_parent = nullptr);
    UIDialog* ctrl_root_ = nullptr;
    xmlnode xml_root_ = nullptr;
};
}    // namespace DuiMini
