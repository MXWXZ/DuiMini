/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once
#include "thirdpart/zlib/unzip.h"        // zlib 1.2.11
#include "thirdpart/zlib/iowin32.h"
#ifdef _WIN64
#pragma comment(lib, "thirdpart/zlib/zlib_x64.lib")
#else
#pragma comment(lib, "thirdpart/zlib/zlib_x86.lib")
#endif

namespace DuiMini {

typedef unzFile ZFile;

class DUIMINI_API UIUnzip {
public:
    /**
     * Open zip file
     * @param    LPCTSTR v_fullpath: MUST be full path of file
     * @return   opened ZFile pointer
     */
    static ZFile OpenZip(LPCTSTR v_fullpath);

    /**
     * Close zip file
     * @param    ZFile v_fp:ZFile pointer want to close
     * @return   true for succeed
     * ZFile pointer will be set to nullptr if succeed closed
     */
    static bool CloseZip(ZFile v_fp);

    /**
     * Locate file in zip
     * @param    LPCTSTR v_relativepath: relative path (e.g. abc/123.txt)
     * @return   -1 when file can't access,otherwise is the file size
     * WARNING: Please better to use '/' to divide in relative path,
     * this function will AUTOMATICALLY turn '\\' to '/' (zlib ONLY allows '/')
     */
    static FILESIZE LocateZipItem(ZFile v_fp, LPCTSTR v_relativepath);

    /**
     * Unzip file
     * @param    BYTE* v_buffer: buffer to recive data(please call
     * [LocateZipItem] to get the size and apply for memory space)
     * WARNING: this function MUST be used after calling [LocateZipItem] and
     * will NOT check if there is enough space in the buffer.
     */
    static bool UnZipData(ZFile v_fp, BYTE* v_buffer);
};

}   // namespace DuiMini
