/** @file
 * Low-level zip caller.
 * Directly use miniz to unzip.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_UTILS_UIUNZIP_H_
#define DUI_UTILS_UIUNZIP_H_

#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include <miniz/miniz.h>

namespace DuiMini {
/**
 * Basic pack to make miniz ez to use.
 */
class DUIMINI_API UIUnzip {
public:
    UIUnzip();
    ~UIUnzip();

public:
    /**
     * Open zip file.
     * @param   path: zip file path
     * @return  true for success
     */
    bool OpenZip(const char* path);

    /**
     * Open zip file in memory.
     * @param	buffer: memory buffer
     * @param   size: buffer size
     * @return	true for success
     * @warning You cant free buffer before Closing the zip, otherwise you may
     * get error when reading files.
     */
    bool OpenZip(void* buffer, size_t size);

    /**
     * Check if inited successfully.
     * @return	true for success
     */
    bool IsInited() const;

    /**
     * Close zip file.
     * @return	true for success
     */
    void CloseZip();

    /**
     * Get uncompress file size.
     * @param	path: file path, relative to zip root
     * @return	uncompressed file size, -1 for error
     * @see     GetFileIndex, GetFile
     */
    long GetFileSize(const char* path);

    /**
     * Unzip file.
     * @param	path: file path, relative to zip root
     * @param	buffer: file data buffer
     * @param	size: buffer size
     * @return	true for success
     * @note    you must allocate and free space by your self
     * @see     GetFileIndex, GetFileSize
     */
    bool GetFile(const char* path, void* buffer, long size);

private:
    mz_zip_archive fp_;
    bool inited_ = false;
};

}  // namespace DuiMini

#endif  // !DUI_UTILS_UIUNZIP_H_
