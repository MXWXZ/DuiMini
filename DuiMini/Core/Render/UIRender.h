/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
enum RenderMode {
    kRM_GDIPlus,    // GDI+
};

class DUIMINI_API UIRenderImage {
public:
    UIRenderImage();
    UIRenderImage(LPCTSTR v_path);
    ~UIRenderImage();

    void Load(LPCTSTR v_path);
    void* GetInterface() const;
    UINT GetWidth() const;
    UINT GetHeight() const;

private:
    shared_ptr<IUIRenderImage> renderimg_ = nullptr;
};

class DUIMINI_API UIRender {
public:
    UIRender();
    ~UIRender();

    /**
     * You ONLY need to call these ONCE at the beginning and the end of the
     * program.
     */
    static void GlobalInit();
    static void GlobalInit(RenderMode v_mode);
    // Release will be automatically called by UISystem::Cleanup
    static void GlobalRelease();

    static void SetRenderMode(RenderMode v_mode) { render_mode_ = v_mode; }
    static RenderMode GetRenderMode() { return render_mode_; }

    void Paint(UIWindow* v_wnd);
    void RedrawBackground();
    void DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                   ALPHA v_alpha = 255, ImageMode v_mode = kIM_Extrude);
    void DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                   const UIRect& v_srcrect, ALPHA v_alpha = 255,
                   ImageMode v_mode = kIM_Extrude);
    void DrawString(LPCTSTR v_text, const UIFont &v_font,
                    const UIStringFormat &v_format, const UIRect &v_rect);
    void DrawRect(const UIRect &v_rect, const UIColor &v_color,
                  long v_border);
    void DrawFillRect(const UIRect &v_rect, const UIColor &v_color);

private:
    static IUIRender* SelectRender(shared_ptr<IUIRender>* v_pointer);

    shared_ptr<IUIRender> render_ = nullptr;
    static RenderMode render_mode_;
};
}    // namespace DuiMini
