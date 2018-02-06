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
/**
 * Resource kind interface
 */
class DUIMINI_API IUIRes {
public:
    virtual ~IUIRes() {}

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
    virtual LPCTSTR GetResInfo() const = 0;

    /**
    * Get resource file size
    * @param    LPCTSTR v_path: relative path
    * @return   -1 when file can't access,otherwise is the file size
    */
    virtual long GetFileSize(LPCTSTR v_path) = 0;

    /**
    * Get resource file
    * @param    LPCTSTR v_path: relative path
    * @param    BYTE* v_buf: buffer
    * @param    long v_size: buffer size
    * @return   true if succeed
    */
    virtual bool GetFile(LPCTSTR v_path, BYTE* v_buf, long v_size) = 0;
};

/**
 * Container interface
 */
class DUIMINI_API UIControl;
class DUIMINI_API IUIContainer {
public:
    virtual UIControl* GetItem(UINT v_index) const = 0;
    virtual UINT GetCount() const = 0;
    virtual bool Add(UIControl* v_ctrl) = 0;
    virtual bool Remove(UIControl* v_ctrl) = 0;
    virtual void RemoveAll() = 0;
};

/**
 * Render interface
 */
class DUIMINI_API UIWindow;
class DUIMINI_API UIRenderImage;
class DUIMINI_API IUIRender {
public:
    virtual bool GlobalInit() = 0;
    virtual bool GlobalRelease() = 0;
    virtual bool Paint(UIWindow* v_wnd) = 0;

    // For buffering drawing, renew background buffer, NO SYNC SCREEN
    virtual bool RedrawBackground() = 0;

    virtual bool DrawImage(UIRenderImage* v_img, int v_left, int v_top,
                           int v_width, int v_height) = 0;
};

class DUIMINI_API IUIRenderImage {
public:
    virtual bool Load(LPCTSTR v_path) = 0;
    virtual bool Release() = 0;
    virtual void* GetInterface() const = 0;
    virtual UINT GetWidth() const = 0;
    virtual UINT GetHeight() const = 0;
};
}   // namespace DuiMini
