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
#include "UIResFile.h"

namespace DuiMini {
UIResFile::UIResFile() {}

UIResFile::~UIResFile() {}

UIResFile::UIResFile(LPCTSTR v_info) {
    SetResInfo(v_info);
}

void UIResFile::SetResInfo(LPCTSTR v_info) {
    folderpath_ = v_info;
}

LPCTSTR UIResFile::GetResInfo() const {
    return folderpath_.GetData();
}

long UIResFile::GetFileSize(LPCTSTR v_path) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), v_path);

    FILE* fp;
    fp = _tfopen(fullpath, _T("rb"));
    if (!fp) {
        UISetError(kLL_Error, kEC_FileFail,
                   _T("File \"%s\" can't access!"),
                   fullpath.GetData());
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

bool UIResFile::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), v_path);

    FILE* fp;
    fp = _tfopen(fullpath, _T("rb"));
    if (!fp) {
        UISetError(kLL_Error, kEC_FileFail,
                   _T("File \"%s\" can't access!"),
                   fullpath.GetData());
        return false;
    }
    fread(v_buffer, 1, v_size, fp);
    fclose(fp);
    return true;
}

}  // namespace DuiMini

