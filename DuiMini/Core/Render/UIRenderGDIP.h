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

    void GlobalInit() override;
    void GlobalRelease() override;
    void Paint(UIWindow* v_wnd) override;
    void RedrawBackground() override;
    void DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                   const UIRect& v_srcrect, ALPHA v_alpha = 255,
                   ImageMode v_mode = kIM_Extrude) override;
    void DrawString(LPCTSTR v_text, const UIFont &v_font,
                    const UIStringFormat &v_format, const UIRect &v_rect) override;
    void DrawRect(const UIRect &v_rect, const UIColor &v_color,
                  long v_border) override;
    void DrawFillRect(const UIRect &v_rect, const UIColor &v_color) override;

private:
    HDC background_ = NULL;         // background DC
    HGDIOBJ tmpobj_ = NULL;         // tmp object
    HBITMAP bg_bitmap_ = NULL;      // bitmap on DC
    shared_ptr<Gdiplus::Graphics> graph_;    // always null after used
    static ULONG_PTR gdiplus_token;
};

class DUIMINI_API UIRenderImageGDIP :public IUIRenderImage {
public:
    UIRenderImageGDIP();
    UIRenderImageGDIP(LPCTSTR v_path);
    ~UIRenderImageGDIP();

    void Load(LPCTSTR v_path) override;
    LPVOID GetInterface() const override;
    UINT GetWidth() const override;
    UINT GetHeight() const override;

private:
    shared_ptr<Gdiplus::Image> img_ = nullptr;
};
}    // namespace DuiMini
