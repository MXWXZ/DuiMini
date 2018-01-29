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
#include "Control/UIControl.h"
#include "Control/Layout/UIContainer.h"

namespace DuiMini {
class DUIMINI_API UIDialog :public UIContainer {
public:
    UIDialog();
    virtual ~UIDialog();

public:
    virtual bool SetBackground(LPCTSTR v_path);

public:
    LPVOID GetInterface(LPCTSTR v_name) override;

    virtual void PaintBackground();

    void BeforeSetAttribute() override;
    void AfterSetAttribute() override;

protected:
    void LoadResAttr() override;
    void LoadTextAttr() override;

private:
    UIRenderImage *bgimg_ = nullptr;
};
}   // namespace DuiMini
