/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:
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

LPCTSTR UIResZip::GetResInfo() const {
    return fullpath_.GetData();
}

long UIResZip::GetFileSize(LPCTSTR v_path) {
    if (!zipcache_)
        if (!OpenZip())
            return -1;
    long ret = UIUnzip::LocateZipItem(zipcache_, v_path);
    if (ret == -1)
        UISetError(kError, kFileFail,
                   _T("File \"%s\" in \"%s\" can't access!"),
                   v_path, fullpath_.GetData());
    return ret;
}

bool UIResZip::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    if (!zipcache_)
        if (!OpenZip())
            return false;
    if (!UIUnzip::UnZipData(zipcache_, v_buffer)) {
        UISetError(kError, kFileFail,
                   _T("File \"%s\" in \"%s\" can't access!"),
                   v_path, fullpath_.GetData());
        return false;
    }
    return true;
}

ZFile UIResZip::OpenZip() {
    zipcache_ = UIUnzip::OpenZip(fullpath_);
    if (!zipcache_)
        UISetError(kError, kFileFail,
                   _T("File \"%s\" can't access!"),
                   fullpath_.GetData());
    return zipcache_;
}

}  // namespace DuiMini

