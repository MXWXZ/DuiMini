/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIUnzip.h"

namespace DuiMini {
/************************************************************************
Open zip file
LPCTSTR path: The full path of file
ret value: opened ZFile pointer
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
Close zip file
ZFile fp: file pointer you want to close
************************************************************************/
void UIUnzip::CloseZip(ZFile fp) {
    unzClose(fp);
    fp = NULL;
}

/************************************************************************
Locate file in zip
ZFile fp: opened file pointer
LPCTSTR path: relative path (e.g. abc/123.txt)
ret value: -1 when file do not exist or damaged
           otherwise is the file size
WARNING: Please better to use '/' to divide in relative path,this function
         will AUTOMATICALLY turn '\\' to '/' (zlib ONLY allows '/')
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
Unzip file
ZFile fp:opened file pointer
BYTE* data: buffer to recive data(please call 'LocateZipItem' to get the
            size and apply for memory space).
ret value: false - fail     true - succeed
WARNING: this function MUST be used after calling 'LocateZipItem' and 
         WILL NOT check if there is enough space in the buffer.
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
