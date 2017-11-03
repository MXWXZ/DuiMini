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
    * @param    LPCTSTR info:path or sth.
    */
    virtual void SetResInfo(LPCTSTR info) = 0;

    /**
    * Get resource information
    * @return    res info set before
    */
    virtual LPCTSTR GetResInfo() = 0;

    /**
    * Get resource file size
    * @param    LPCTSTR path: relative path
    * @return   -1 when file can't access,otherwise is the file size
    */
    virtual long GetFileSize(LPCTSTR path) = 0;

    /**
    * Get resource file
    * @param    LPCTSTR path: relative path
    * @param    BYTE* buf: buffer
    * @param    long size: buffer size
    * @return   true if succeed
    */
    virtual bool GetFile(LPCTSTR path, BYTE* buf, long size) = 0;
};
}   // namespace DuiMini
