/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIDialog;
class DUIMINI_API UIDlgBuilder {
public:
    UIDlgBuilder();
    ~UIDlgBuilder();

public:
    UIControl* Init(UIXmlNode v_root, UIWindow* v_wnd);

    void Release();

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
     * @return   true for success
     */
    bool FinishCreateControl(UIControl* v_ctrl);

    UIDialog* GetCtrlRoot();

private:
    UIControl* Parse(UIWindow* v_wnd, UIXmlNode v_root,
                     UIControl* v_parent = nullptr);
    shared_ptr<UIDialog> ctrl_root_ = nullptr;
    UIXmlNode xml_root_;
};
}    // namespace DuiMini
