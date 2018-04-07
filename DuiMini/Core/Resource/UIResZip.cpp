/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#include "stdafx.h"
#include "UIResZip.h"

namespace DuiMini {
UIResZip::UIResZip() {}

UIResZip::UIResZip(LPCTSTR v_info) {
    SetResInfo(v_info);
}

UIResZip::~UIResZip() {
    if (zipcache_)
        UIUnzip::CloseZip(zipcache_);
}

void UIResZip::SetResInfo(LPCTSTR v_info) {
    fullpath_ = v_info;
    if (zipcache_)
        UIUnzip::CloseZip(zipcache_);
}

CUStr UIResZip::GetResInfo() const {
    return fullpath_;
}

long UIResZip::GetFileSize(LPCTSTR v_path) {
    if (!zipcache_)
        if (!OpenZip())
            return -1;
    FILESIZE ret = UIUnzip::LocateZipItem(zipcache_, v_path);
    if (ret == -1)
        UISetError(kEL_Fatal, kEC_FileFail,
                   ErrorMsg_FileFail(v_path));
    return ret;
}

bool UIResZip::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    if (!zipcache_)
        if (!OpenZip())
            return false;
    if (!UIUnzip::UnZipData(zipcache_, v_buffer))
        UISetError(kEL_Fatal, kEC_FileFail,
                   ErrorMsg_FileFail(v_path));
    return true;
}

ZFile UIResZip::OpenZip() {
    zipcache_ = UIUnzip::OpenZip(fullpath_);
    if (!zipcache_)
        UISetError(kEL_Fatal, kEC_FileFail,
                   ErrorMsg_FileFail(fullpath_.GetData()));
    return zipcache_;
}

}  // namespace DuiMini

