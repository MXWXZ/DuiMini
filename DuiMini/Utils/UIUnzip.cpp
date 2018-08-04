/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIUnzip.h"

namespace DuiMini {
ZFile UIUnzip::OpenZip(LPCTSTR v_fullpath) {
    auto str = UIUtils::Convert2Str(v_fullpath);
    ZFile fp = unzOpen64(str.get());
    if (fp) {
        unz_global_info64 zGlobalInfo;
        if (unzGetGlobalInfo64(fp, &zGlobalInfo) != UNZ_OK)
            CloseZip(fp);
    }
    return fp;
}

bool UIUnzip::CloseZip(ZFile v_fp) {
    if (unzClose(v_fp) != UNZ_OK)
        return false;
    v_fp = nullptr;
    return true;
}

FILESIZE UIUnzip::LocateZipItem(ZFile v_fp, LPCTSTR v_relativepath) {
    UStr formatpath = v_relativepath;
    formatpath.Replace(_T("\\"), _T("/"));
    auto str = UIUtils::Convert2Str(formatpath);
    FILESIZE ret = FILESIZE(-1);
    if (unzLocateFile(v_fp, str.get(), 0) == UNZ_OK) {
        unz_file_info64 zFileInfo;
        const int size = 256;
        auto name = UIUtils::SafeStr(size);
        if (unzGetCurrentFileInfo64(v_fp, &zFileInfo, name.get(),
                                    size, NULL, 0, NULL, 0) == UNZ_OK)
            ret = zFileInfo.uncompressed_size;
    }
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
