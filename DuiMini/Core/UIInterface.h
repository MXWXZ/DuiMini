/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:UI interface define
 */
#pragma once

namespace DuiMini {
class DUIMINI_API IUIRes {
public:
    /**
    * Set resource information
    * Called when setting the resource path or id or sth.
    * @param    LPCTSTR v_info:path or sth.
    */
    virtual void SetResInfo(LPCTSTR v_info) = 0;

    /**
    * Get resource information
    * @return    res info set before
    */
    virtual CUStr GetResInfo() const = 0;

    /**
    * Get resource file size
    * @param    LPCTSTR v_path: relative path
    * @return   FILESIZE(-1) when file can't access, otherwise is file size
    */
    virtual FILESIZE GetFileSize(LPCTSTR v_path) = 0;

    /**
    * Get resource file
    * @param    LPCTSTR v_path: relative path
    * @param    BYTE* v_buf: buffer
    * @param    FILESIZE v_size: buffer size
    * @param    true for success
    */
    virtual bool GetFile(LPCTSTR v_path, BYTE* v_buf, FILESIZE v_size) = 0;
};

/**
 * Container interface
 */
class DUIMINI_API UIControl;
class DUIMINI_API IUIContainer {
public:
    virtual UIControl* GetItem(UINT v_index) const = 0;
    virtual UINT GetCount() const = 0;
    virtual void Add(UIControl* v_ctrl) = 0;
    virtual bool Remove(UIControl* v_ctrl) = 0;
    virtual void RemoveAll() = 0;
};

/**
 * Render interface
 */
class DUIMINI_API UIWindow;
class DUIMINI_API UIRenderImage;
struct DUIMINI_API UIFont;
struct DUIMINI_API UIStringFormat;
class DUIMINI_API UIRect;
// image mode
enum ImageMode {
    kIM_Extrude,
    kIM_Tile
};
class DUIMINI_API IUIRender {
public:
    virtual void GlobalInit() = 0;
    virtual void GlobalRelease() = 0;
    virtual void Paint(UIWindow* v_wnd) = 0;

    // For buffering drawing, renew background buffer, NO SYNC FRONT SCREEN
    virtual void RedrawBackground() = 0;

    virtual void DrawImage(UIRenderImage* v_img, const UIRect &v_destrect,
                           const UIRect &v_srcrect, ALPHA v_alpha = 255,
                           ImageMode v_mode = kIM_Extrude) = 0;
    virtual void DrawString(LPCTSTR v_text, const UIFont &v_font,
                            const UIStringFormat &v_format,
                            const UIRect &v_rect) = 0;
    virtual void DrawRect(const UIRect &v_rect, const UIColor &v_color,
                          long v_border) = 0;
    virtual void DrawFillRect(const UIRect &v_rect, const UIColor &v_color) = 0;
};

class DUIMINI_API IUIRenderImage {
public:
    virtual void Load(LPCTSTR v_path) = 0;
    virtual LPVOID GetInterface() const = 0;
    virtual UINT GetWidth() const = 0;
    virtual UINT GetHeight() const = 0;
};
}   // namespace DuiMini
