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
class UIWindow;
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

    UIControl* GetCtrlRoot();

private:
    UIControl* _Parse(xmlnode v_root, UIControl* v_parent = nullptr);
    UIWindow* basewnd_ = nullptr;
    UIControl* ctrl_root_ = nullptr;
    xmlnode xml_root_ = nullptr;
};
}    // namespace DuiMini
