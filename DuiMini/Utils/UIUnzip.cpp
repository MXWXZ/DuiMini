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
#include "DuiMini.h"
#include "UIUnzip.h"

namespace DuiMini {
ZFile UIUnzip::OpenZip(LPCTSTR path) {
#ifdef _UNICODE
    int len = WideCharToMultiByte(CP_ACP, 0, path, -1, NULL, 0, NULL, NULL);
    LPSTR str = new char[len];
    WideCharToMultiByte(CP_ACP, 0, path, -1, str, len, NULL, NULL);
#else
    LPCSTR str = path;
#endif
    ZFile fp = unzOpen64(str);
    if (fp != NULL) {
        unz_global_info64 zGlobalInfo;
        if (unzGetGlobalInfo64(fp, &zGlobalInfo) != UNZ_OK)
            CloseZip(fp);
    }
#ifdef _UNICODE
    delete[]str;
#endif
    return fp;
}

void UIUnzip::CloseZip(ZFile fp) {
    unzClose(fp);
    fp = NULL;
}

long UIUnzip::LocateZipItem(ZFile fp, LPCTSTR path) {
    UStr formatpath = path;
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
    if (unzLocateFile(fp, str, 0) == UNZ_OK) {
        unz_file_info64 zFileInfo;
        const int buf = 256;
        char* name = new char[buf];
        if (unzGetCurrentFileInfo64(fp, &zFileInfo, name,
                                    buf, NULL, 0, NULL, 0) == UNZ_OK)
            ret = static_cast<long>(zFileInfo.uncompressed_size);
    }
#ifdef _UNICODE
    delete[]str;
#endif
    return ret;
}

bool UIUnzip::UnZipData(ZFile fp, BYTE* data) {
    if (unzOpenCurrentFile(fp) != UNZ_OK)return false;
    int err, pos = 0;
    do {
        err = unzReadCurrentFile(fp, data + pos, 255);
        if (err < 0)return false;
        pos += err;
    } while (err > 0);
    unzCloseCurrentFile(fp);
    return true;
}

}   // namespace DuiMini
