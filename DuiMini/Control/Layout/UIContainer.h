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
class DUIMINI_API UIContainer : public UIControl, public IUIContainer {
public:
    UIContainer();
    virtual ~UIContainer();

public:
    UIControl* GetItem(UINT v_index) const override;
    UINT GetCount() const override;
    bool Add(UIControl* v_ctrl) override;
    bool Remove(UIControl* v_ctrl) override;
    void RemoveAll() override;

public:
    void DoPaint(HWND v_hwnd, IUIRender* v_render) override;
    UIControl* FindCtrlFromPT(POINT v_pt) override;
    void SetBaseWindow(UIWindow* v_basewnd) override;
    LPVOID GetInterface(LPCTSTR v_name) override;
    void AfterSetAttribute() override;

protected:
    UIPtrArray item_;
};
}   // namespace DuiMini