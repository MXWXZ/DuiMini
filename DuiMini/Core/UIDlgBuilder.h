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

    UIDialog* GetCtrlRoot();

private:
    UIControl* _Parse(UIWindow* v_wnd, xmlnode v_root,
                      UIControl* v_parent = nullptr);
    UIDialog* ctrl_root_ = nullptr;
    xmlnode xml_root_ = nullptr;
};
}    // namespace DuiMini
