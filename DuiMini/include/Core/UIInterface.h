/** @file
 * UI class global interface.
 * Define all interface UI class use.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_CORE_UIINTERFACE_H_
#define DUI_CORE_UIINTERFACE_H_

#include <stdint.h>
#include <map>
#include "UIDefine.h"
#include "Utils/UIUtils.h"

namespace DuiMini {
/**
 * All resource load style should base on this class.
 */
class DUIMINI_API IUIRes {
public:
    /**
     * Set resource information.
     * Called when setting the resource path or id or sth.
     * @param	info: path or sth.
     * @return  true for success
     * @see     GetResInfo
     */
    virtual bool SetResInfo(const char* info) = 0;

    /**
     * Get resource information.
     * @return   res info set before
     * @see      SetResInfo
     */
    virtual UIStr GetResInfo() const = 0;

    /**
     * Get resource file.
     * @param	path: relative path
     * @param	buffer: file data buffer
     * @param	size: buffer size
     * @return	true for success
     */
    virtual bool GetFile(const char* path, void* buffer, long size) = 0;

    /**
     * Get file size.
     * @param	path: relative path
     * @return  file size, (size_t)-1 for error
     */
    virtual long GetFileSize(const char* path) = 0;
};

/**
 * All resloader should base on this class.
 */
class DUIMINI_API IUILoadFile {
public:
    /**
     * Load file res.
     * @param	buffer: file data buffer
     * @param	size: buffer size
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
