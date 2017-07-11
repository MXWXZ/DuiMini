/************************************************************************
Copyright (c) 2017 MXWXZ
Unzip class(use zlib)
************************************************************************/
#pragma once
#ifndef DUIMINI_UTILS_UIUNZIP_H_
#define DUIMINI_UTILS_UIUNZIP_H_

namespace DuiMini {
class DUIMINI_API UIUnzip {
 public:
    static ZFile OpenZip(LPCTSTR path);
    static void CloseZip(ZFile fp);
    static long LocateZipItem(ZFile fp, LPCTSTR path);
    static bool UnZipData(ZFile fp, BYTE* data);
};

}   // namespace DuiMini

#endif  // DUIMINI_UTILS_UIUNZIP_H_
