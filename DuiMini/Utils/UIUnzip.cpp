/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIUnzip.h"

namespace DuiMini {
/************************************************************************
打开文件函数
LPCTSTR path：文件全路径
返回值：打开的ZFile指针
************************************************************************/
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

/************************************************************************
关闭文件函数
ZFile fp：待关闭的文件指针
************************************************************************/
void UIUnzip::CloseZip(ZFile fp) {
    unzClose(fp);
    fp = NULL;
}

/************************************************************************
定位文件函数
ZFile fp：打开的文件指针
LPCTSTR path：相对压缩文件路径（如abc/123.txt）
返回值：-1：文件不存在或已损坏，否则为文件大小
注：相对路径请最好用/分隔，本函数自动将\\转换为/（zlib只识别/）
************************************************************************/
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

/************************************************************************
解压函数
ZFile fp：打开的文件指针
BYTE* data：接收数据的缓冲区（请调用LocateZipItem获得大小并自行申请空间）
注：本函数需在LocateZipItem后使用，函数不检查空间是否足够
************************************************************************/
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
