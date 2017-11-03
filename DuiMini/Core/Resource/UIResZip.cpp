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
#include "DuiMini.h"
#include "UIResZip.h"

namespace DuiMini {
UIResZip::UIResZip() {
    zipcache_ = NULL;
}

UIResZip::UIResZip(LPCTSTR info) {
    zipcache_ = NULL;
    SetResInfo(info);
}

UIResZip::~UIResZip() {
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
}

void UIResZip::SetResInfo(LPCTSTR info) {
    fullpath_ = info;
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
}

LPCTSTR UIResZip::GetResInfo() {
    return fullpath_.GetData();
}

long UIResZip::GetFileSize(LPCTSTR path) {
    if (zipcache_ == NULL)
        if (OpenZip() == NULL)
            return -1;
    long ret = UIUnzip::LocateZipItem(zipcache_, path);
    if (ret == -1)
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" in \"%s\" can't access!"),
                              path, fullpath_.GetData());
    return ret;
}

bool UIResZip::GetFile(LPCTSTR path, BYTE* buf, long size) {
    if (zipcache_ == NULL)
        if (OpenZip() == NULL)
            return false;
    if (!UIUnzip::UnZipData(zipcache_, buf)) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" in \"%s\" can't access!"),
                              path, fullpath_.GetData());
        return false;
    }
    return true;
}

ZFile UIResZip::OpenZip() {
    zipcache_ = UIUnzip::OpenZip(fullpath_);
    if (zipcache_ == NULL)
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" can't access!"),
                              fullpath_.GetData());
    return zipcache_;
}

}  // namespace DuiMini

