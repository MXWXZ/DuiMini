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
#include "UIResRC.h"

namespace DuiMini {
UIResRC::UIResRC() {}

UIResRC::UIResRC(LPCTSTR v_info) {
    SetResInfo(v_info);
}

UIResRC::~UIResRC() {
    if (zipcache_)
        UIUnzip::CloseZip(zipcache_);
}

void UIResRC::SetResInfo(LPCTSTR v_info) {
    resid_ = _ttoi(v_info);
    tmpfullpath_ = _T("");
    if (zipcache_)
        UIUnzip::CloseZip(zipcache_);
}

LPCTSTR UIResRC::GetResInfo() const {
    return UStr(static_cast<int>(resid_));
}

long UIResRC::GetFileSize(LPCTSTR v_path) {
    if (!zipcache_)
        if (!OpenZip())
            return -1;
    long ret = UIUnzip::LocateZipItem(zipcache_, v_path);
    if (ret == -1)
        UISetError(kLL_Error, kEC_FileFail,
                   _T("File \"%s\" in \"%s\" can't access!"),
                   v_path, tmpfullpath_.GetData());
    return ret;
}

bool UIResRC::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    if (!zipcache_)
        if (!OpenZip())
            return false;
    if (!UIUnzip::UnZipData(zipcache_, v_buffer)) {
        UISetError(kLL_Error, kEC_FileFail,
                   _T("File \"%s\" in \"%s\" can't access!"),
                   v_path, tmpfullpath_.GetData());
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
    if (!fp) {
        UISetError(kLL_Error, kEC_FileFail,
                   _T("Temp v_path permission denied!"));
        return nullptr;
    }
    fwrite(file, (UINT)SizeofResource(UISystem::GetInstance(),
                                      srcsys), 1, fp);
    fclose(fp);
    UnlockResource(globalsys);
    FreeResource(globalsys);
    tmpfullpath_ = tmpfile;

    zipcache_ = UIUnzip::OpenZip(tmpfullpath_);
    if (!zipcache_)
        UISetError(kLL_Error, kEC_FileFail,
                   _T("File \"%s\" can't access!"),
                   tmpfullpath_.GetData());
    return zipcache_;
}

}  // namespace DuiMini

