/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/10
 */
#ifndef DUI_CORE_UIINTERFACE_H_
#define DUI_CORE_UIINTERFACE_H_

#include <stdint.h>
#include <map>
#include "UIDefine.h"
#include "Utils/UIUtils.h"

namespace DuiMini {
/**
 * All resource loader should base on this class
 */
class DUIMINI_API IUIRes {
public:
    /**
     * Set resource information
     * Called when setting the resource path or id or sth.
     * @param	const char * info: path or sth.
     * @return  true for success
     * @see      GetResInfo
     */
    virtual bool SetResInfo(const char* info) = 0;

    /**
     * Get resource information
     * @return   res info set before
     * @see      SetResInfo
     */
    virtual UIStr GetResInfo() const = 0;

    /**
     * Get resource file
     * @param	const char* path: relative path
     * @param	void * buffer: file data buffer
     * @param	long size: buffer size
     * @return	true for success
     */
    virtual bool GetFile(const char* path, void* buffer, long size) = 0;

    /**
     * Get file size
     * @param	const char* path: relative path
     * @return  file size, (size_t)-1 for error
     */
    virtual long GetFileSize(const char* path) = 0;
};

/**
 * All class need to load file should base on this class.
 */
class DUIMINI_API IUILoadFile {
public:
    /**
     * Load file res
     * @param	void* buffer: file data buffer
     * @param	long size: buffer size
     * @return	true for success
     */
    virtual bool LoadFile(const void* buffer, long size) = 0;
    virtual void SetPath(const char* path) { path_ = path; }
    virtual UIStr GetPath() const { return path_; }

protected:
    UIStr path_;
};
}  // namespace DuiMini

#endif  // !DUI_CORE_UIINTERFACE_H_
