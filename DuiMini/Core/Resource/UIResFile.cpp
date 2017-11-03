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
#include "UIResFile.h"

namespace DuiMini {
UIResFile::UIResFile() {}

UIResFile::UIResFile(LPCTSTR info) {
    SetResInfo(info);
}

void UIResFile::SetResInfo(LPCTSTR info) {
    folderpath_ = info;
}

LPCTSTR UIResFile::GetResInfo() {
    return folderpath_.GetData();
}

long UIResFile::GetFileSize(LPCTSTR path) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), path);

    FILE* fp;
    fp = _tfopen(fullpath, _T("rb"));
    if (fp == NULL) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" can't access!"),
                              fullpath.GetData());
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

bool UIResFile::GetFile(LPCTSTR path, BYTE* buf, long size) {
    UStr fullpath;
    fullpath.Format(_T("%s\\%s"), folderpath_.GetData(), path);

    FILE* fp;
    fp = _tfopen(fullpath, _T("rb"));
    if (fp == NULL) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFail,
                              _T("File \"%s\" can't access!"),
                              fullpath.GetData());
        return false;
    }
    fread(buf, 1, size, fp);
    fclose(fp);
    return true;
}

}  // namespace DuiMini

