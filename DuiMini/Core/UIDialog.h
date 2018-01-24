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
    ~UIDialog();

    LPVOID GetInterface(LPCTSTR v_name) override;
    void DoPaintBackground(IUIRender* v_render);
    void AfterSetAttribute() override;
    
    void LoadBackground();      // Load after SetAttribute

private:
    UIRenderImage *bgimg_ = nullptr;
};
}   // namespace DuiMini
