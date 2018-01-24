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
    kGDIPlus,
};

class DUIMINI_API UIRenderImage {
public:
    UIRenderImage();
    explicit UIRenderImage(LPCTSTR v_path);
    ~UIRenderImage();

    bool Load(LPCTSTR v_path);
    bool Release();
    void* GetInterface();

private:
    IUIRenderImage* renderimg_ = nullptr;
};

class DUIMINI_API UIRender {
public:
    UIRender();
    explicit UIRender(UIWindow* v_parent);
    ~UIRender();

    /**
     * You ONLY need to call these ONCE at the beginning and the end of the
     * program.
     */
    static bool Init();
    static bool Init(RenderMode v_mode);
    // Release will be automatically called by UISystem::Cleanup
    static bool Release();

    static RenderMode SetRenderMode(RenderMode v_mode);
    static RenderMode GetRenderMode();

    UIWindow* SetParent(UIWindow* v_parent);
    bool Paint();

private:
    static IUIRender* SelectRender(IUIRender** v_pointer);

    IUIRender* render_ = nullptr;
    static RenderMode render_mode_;
};
}    // namespace DuiMini
