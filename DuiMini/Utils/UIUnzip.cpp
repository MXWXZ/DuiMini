/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIUnzip.h"

namespace DuiMini {
ZFile UIUnzip::OpenZip(LPCTSTR v_fullpath) {
#ifdef _UNICODE
    int len = WideCharToMultiByte(CP_ACP, 0, v_fullpath, -1, NULL,
                                  0, NULL, NULL);
    LPSTR str = new char[len];
    WideCharToMultiByte(CP_ACP, 0, v_fullpath, -1, str, len, NULL, NULL);
#else
    LPCSTR str = v_fullpath;
#endif
    ZFile fp = unzOpen64(str);
    if (fp) {
        unz_global_info64 zGlobalInfo;
        if (unzGetGlobalInfo64(fp, &zGlobalInfo) != UNZ_OK)
            CloseZip(fp);
    }
#ifdef _UNICODE
    delete[]str;
    str = nullptr;
#endif
    return fp;
}

bool UIUnzip::CloseZip(ZFile v_fp) {
    if (unzClose(v_fp) != UNZ_OK)
        return false;
    v_fp = nullptr;
    return true;
}

long UIUnzip::LocateZipItem(ZFile v_fp, LPCTSTR v_relativepath) {
    UStr formatpath = v_relativepath;
    formatpath.Replace(_T("\\"), _T("/"));
    LPCTSTR tmppath = formatpath.GetData();
#ifdef _UNICODE
    int len = WideCharToMultiByte(CP_ACP, 0, tmppath, -1, NULL, 0, NULL, NULL);
    LPSTR str = new char[len];
    WideCharToMultiByte(CP_ACP, 0, tmppath, -1, str, len, NULL, NULL);
#else
    LPCSTR str = tmppath;
#endif
    long ret = -1;
    if (unzLocateFile(v_fp, str, 0) == UNZ_OK) {
        unz_file_info64 zFileInfo;
        const int buf = 256;
        char* name = new char[buf];
        if (unzGetCurrentFileInfo64(v_fp, &zFileInfo, name,
                                    buf, NULL, 0, NULL, 0) == UNZ_OK)
            ret = static_cast<long>(zFileInfo.uncompressed_size);
    }
#ifdef _UNICODE
    delete[]str;
    str = nullptr;
#endif
    return ret;
}

bool UIUnzip::UnZipData(ZFile v_fp, BYTE* v_buffer) {
    if (unzOpenCurrentFile(v_fp) != UNZ_OK)
        return false;
    int err, pos = 0;
    do {
        err = unzReadCurrentFile(v_fp, v_buffer + pos, 255);
        if (err < 0)
            return false;
        pos += err;
    } while (err > 0);
    if (unzCloseCurrentFile(v_fp) != UNZ_OK)
        return false;
    return true;
}

}   // namespace DuiMini
