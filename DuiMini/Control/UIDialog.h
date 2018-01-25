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
    virtual bool ChangeBackground(LPCTSTR v_path);

public:
    LPVOID GetInterface(LPCTSTR v_name) override;

    virtual void DoPaintBackground(IUIRender* v_render);

    void BeforeSetAttribute() override;
    void AfterSetAttribute() override;

public:
    void OnChangeSkin() override;
    void OnChangeLanguage() override;

protected:
    virtual bool LoadBackground(LPCTSTR v_path);

private:
    UIRenderImage *bgimg_ = nullptr;
};
}   // namespace DuiMini
