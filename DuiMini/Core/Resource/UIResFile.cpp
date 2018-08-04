/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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

CUStr UIResFile::GetResInfo() const {
    return folderpath_;
}

FILESIZE UIResFile::GetFileSize(LPCTSTR v_path) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), v_path);

    FILE* fp;
    _tfopen_s(&fp, fullpath, _T("rb"));
    if (!fp)
        return FILESIZE(-1);
    fseek(fp, 0, SEEK_END);
    FILESIZE size = ftell(fp);
    fclose(fp);
    return size;
}

bool UIResFile::GetFile(LPCTSTR v_path, BYTE* v_buffer, FILESIZE v_size) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), v_path);

    FILE* fp;
    _tfopen_s(&fp, fullpath, _T("rb"));
    if (!fp)
        return false;
    fread(v_buffer, 1, v_size, fp);
    fclose(fp);
    return true;
}

}  // namespace DuiMini

