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

namespace DuiMini {
enum RenderMode {
    kRM_GDIPlus,
};

class DUIMINI_API UIRenderImage {
public:
    UIRenderImage();
    explicit UIRenderImage(LPCTSTR v_path);
    ~UIRenderImage();

    bool Load(LPCTSTR v_path);
    bool Release();
    void* GetInterface() const;
    UINT GetWidth() const;
    UINT GetHeight() const;

private:
    IUIRenderImage* renderimg_ = nullptr;
};

class DUIMINI_API UIRender {
public:
    UIRender();
    ~UIRender();

    /**
     * You ONLY need to call these ONCE at the beginning and the end of the
     * program.
     */
    static bool GlobalInit();
    static bool GlobalInit(RenderMode v_mode);
    // Release will be automatically called by UISystem::Cleanup
    static bool GlobalRelease();

    static void SetRenderMode(RenderMode v_mode);
    static RenderMode GetRenderMode();

    bool Paint(UIWindow* v_wnd);
    bool RedrawBackground();
    bool DrawImage(UIRenderImage* v_img, const UIRect& v_destrect);
    bool DrawImage(UIRenderImage* v_img, const UIRect& v_destrect,
                   const UIRect& v_srcrect);
    bool DrawString(LPCTSTR v_text, const UIFont &v_font,
                    const UIRect& v_rect);

private:
    static IUIRender* SelectRender(IUIRender** v_pointer);

    IUIRender* render_ = nullptr;
    static RenderMode render_mode_;
};
}    // namespace DuiMini
