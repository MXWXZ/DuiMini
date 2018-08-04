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

FILESIZE UIResZip::GetFileSize(LPCTSTR v_path) {
    if (!zipcache_)
        if (!OpenZip())
            return FILESIZE(-1);
    return UIUnzip::LocateZipItem(zipcache_, v_path);
}

bool UIResZip::GetFile(LPCTSTR v_path, BYTE* v_buffer, FILESIZE v_size) {
    if (!zipcache_)
        if (!OpenZip())
            return false;
    return UIUnzip::UnZipData(zipcache_, v_buffer);
}

ZFile UIResZip::OpenZip() {
    zipcache_ = UIUnzip::OpenZip(fullpath_);
    return zipcache_;
}

}  // namespace DuiMini

