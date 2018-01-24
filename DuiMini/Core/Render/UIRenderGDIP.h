/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/15
 *
 * @Description:
 */
#pragma once
#include "gdiplus.h"
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")

namespace DuiMini {
class DUIMINI_API UIRenderGDIP :public IUIRender {
public:
    UIRenderGDIP();
    ~UIRenderGDIP();

    bool Init() override;
    bool Release() override;
    bool Paint() override;

    bool DrawImage(UIRenderImage* v_img, int v_left, int v_top,
                   int v_width, int v_height) override;

private:
    HDC background_ = NULL;         // background DC
    HBITMAP bg_bitmap_ = NULL;      // bitmap on DC
    Gdiplus::Graphics* graph_ = nullptr;
    static ULONG_PTR gdiplus_token;
};

class DUIMINI_API UIRenderImageGDIP :public IUIRenderImage {
public:
    UIRenderImageGDIP();
    explicit UIRenderImageGDIP(LPCTSTR v_path);
    ~UIRenderImageGDIP();

    bool Load(LPCTSTR v_path) override;
    bool Release() override;
    void* GetInterface() override;

private:
    Gdiplus::Image* img_ = nullptr;
};
}    // namespace DuiMini