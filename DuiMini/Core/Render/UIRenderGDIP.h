/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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

    bool GlobalInit() override;
    bool GlobalRelease() override;
    bool Paint(UIWindow* v_wnd) override;
    bool RedrawBackground() override;
    bool DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                   const UIRect& v_srcrect) override;
    bool DrawString(LPCTSTR v_text, const UIFont &v_font,
                    const UIFontFormat &v_format, UIRect &v_rect) override;

private:
    HDC background_ = NULL;         // background DC
    HGDIOBJ tmpobj_ = NULL;         // tmp object
    HBITMAP bg_bitmap_ = NULL;      // bitmap on DC
    Gdiplus::Graphics* graph_ = nullptr;    // always nullptr after used
    static ULONG_PTR gdiplus_token;
};

class DUIMINI_API UIRenderImageGDIP :public IUIRenderImage {
public:
    UIRenderImageGDIP();
    explicit UIRenderImageGDIP(LPCTSTR v_path);
    ~UIRenderImageGDIP();

    bool Load(LPCTSTR v_path) override;
    bool Release() override;
    LPVOID GetInterface() const override;
    long GetWidth() const override;
    long GetHeight() const override;

private:
    Gdiplus::Image* img_ = nullptr;
};
}    // namespace DuiMini
