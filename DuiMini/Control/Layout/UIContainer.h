/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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
    void Paint(bool v_background = false) override;
    void SetBaseWindow(UIWindow* v_basewnd) override;
    LPVOID GetInterface(LPCTSTR v_name) override;
    UIControl* FindCtrlFromPT(POINT v_pt) override;
    UIControl* FindCtrlFromName(LPCTSTR v_name) override;
    UIRect UpdatePos() override;

    bool Event(const UIEvent& v_event) override;

protected:
    UIPtrArray item_;
};
}   // namespace DuiMini
