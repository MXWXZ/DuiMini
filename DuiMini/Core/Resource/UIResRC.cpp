/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#include "stdafx.h"
#include "UIResRC.h"

namespace DuiMini {
UIResRC::UIResRC() {}

UIResRC::UIResRC(LPCTSTR v_info) {
    SetResInfo(v_info);
}

UIResRC::~UIResRC() {}

void UIResRC::SetResInfo(LPCTSTR v_info) {
    resid_ = _ttoi(v_info);
    UIResZip::SetResInfo(_T(""));
}

CUStr UIResRC::GetResInfo() const {
    return CUStr(resid_);
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
    fullpath_ = tmpfile;

    return UIResZip::OpenZip();
}

}  // namespace DuiMini

