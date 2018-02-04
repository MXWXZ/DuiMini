/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/01/28
 *
 * @Description:
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIImage :public UIControl {
public:
    UIImage();
    virtual ~UIImage();

public:
    bool SetFile(LPCTSTR v_path);

public:
    void BeforeSetAttribute() override;

    LPVOID GetInterface(LPCTSTR v_name) override;
    void Paint() override;

public:
    // virtual void Event(TEventUI& event);

protected:
    void LoadResAttr() override;

protected:
    UIRenderImage *img_ = nullptr;
};
}   // namespace DuiMini
