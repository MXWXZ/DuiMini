// ****************************************
// Copyright (c) 2017-2050
// All rights reserved.
//
// Author:MXWXZ
// Date:2017/09/05
//
// Description:Unzip class(use zlib)
// ****************************************
#pragma once

namespace DuiMini {
// ****************************************
// unzip interface class
// ****************************************
class DUIMINI_API UIUnzip {
public:
    // ****************************************
    // Open zip file
    // -param    LPCTSTR path: The full path of file
    // -return   opened ZFile pointer
    // ****************************************
    static ZFile OpenZip(LPCTSTR path);

    // ****************************************
    // Close zip file
    // -param    ZFile fp: file pointer you want to close
    // ****************************************
    static void CloseZip(ZFile fp);

    // ****************************************
    // Locate file in zip
    // -param    ZFile fp: opened file pointer
    // -param    LPCTSTR path: relative path (e.g. abc/123.txt)
    // -return   -1 when file do not exist or damaged,otherwise is the file size
    // WARNING: Please better to use '/' to divide in relative path,this function
    // will AUTOMATICALLY turn '\\' to '/' (zlib ONLY allows '/')
    // ****************************************
    static long LocateZipItem(ZFile fp, LPCTSTR path);

    // ****************************************
    // Unzip file
    // -param    ZFile fp:opened file pointer
    // -param    BYTE* data: buffer to recive data(please call 'LocateZipItem' to get the
    //           size and apply for memory space)
    // -return   false - fail     true - succeed
    // WARNING: this function MUST be used after calling 'LocateZipItem' and
    // WILL NOT check if there is enough space in the buffer.
    // ****************************************
    static bool UnZipData(ZFile fp, BYTE* data);
};

}   // namespace DuiMini
