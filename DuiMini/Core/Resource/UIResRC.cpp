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
#include "UIResRC.h"

namespace DuiMini {
UIResRC::UIResRC() {
    zipcache_ = NULL;
}

UIResRC::UIResRC(LPCTSTR info) {
    zipcache_ = NULL;
    SetResInfo(info);
}

UIResRC::~UIResRC() {
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
}

void UIResRC::SetResInfo(LPCTSTR info) {
    resid_ = _ttoi(info);
    tmpfullpath_ = _T("");
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
}

LPCTSTR UIResRC::GetResInfo() {
    return UStr(static_cast<int>(resid_)).GetData();
}

long UIResRC::GetFileSize(LPCTSTR path) {
    if (zipcache_ == NULL)
        if (OpenZip() == NULL)
            return -1;
    long ret = UIUnzip::LocateZipItem(zipcache_, path);
    if (ret == -1)
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" in \"%s\" can't access!"),
                              path, tmpfullpath_.GetData());
    return ret;
}

bool UIResRC::GetFile(LPCTSTR path, BYTE* buf, long size) {
    if (zipcache_ == NULL)
        if (OpenZip() == NULL)
            return false;
    if (!UIUnzip::UnZipData(zipcache_, buf)) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" in \"%s\" can't access!"),
                              path, tmpfullpath_.GetData());
        return false;
    }
    return true;
}

ZFile UIResRC::OpenZip() {
    HRSRC srcsys = FindResource(UISystem::GetInstance(),
                                MAKEINTRESOURCE(resid_), RESOURCE_KIND);
    HGLOBAL globalsys = LoadResource(UISystem::GetInstance(), srcsys);
    LPVOID file = LockResource(globalsys);
    TCHAR tmppath[MAX_PATH];
    GetTempPath(MAX_PATH, tmppath);
    TCHAR tmpfile[MAX_PATH];
    GetTempFileName(tmppath, _T("~ui"), 563, tmpfile);

    FILE* fp;
    _tfopen_s(&fp, tmpfile, _T("wb"));
    if (fp == NULL) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("Temp path permission denied!"));
        return NULL;
    }
    fwrite(file, (UINT)SizeofResource(UISystem::GetInstance(),
                                      srcsys), 1, fp);
    fclose(fp);
    UnlockResource(globalsys);
    FreeResource(globalsys);
    tmpfullpath_ = tmpfile;

    zipcache_ = UIUnzip::OpenZip(tmpfullpath_);
    if (zipcache_ == NULL)
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" can't access!"),
                              tmpfullpath_.GetData());
    return zipcache_;
}

}  // namespace DuiMini

