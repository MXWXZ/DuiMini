/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "Core/Resource/UIResFile.h"
#include "Core/Resource/UIResZip.h"
#include "Core/Resource/UIResRC.h"
#include "UIResource.h"

namespace DuiMini {
IUIRes* UIResource::resclass_ = new UIResFile(DEFAULT_RESFOLDER);
ResType UIResource::restype_ = kRT_File;

UIResource::~UIResource() {
    delete resclass_;
    resclass_ = nullptr;
}

void UIResource::SetResType(ResType v_type) {
    restype_ = v_type;
    delete resclass_;
    switch (v_type) {
    case kRT_File:
        resclass_ = new UIResFile();
        break;
    case kRT_Package:
        resclass_ = new UIResZip();
        break;
    case kRT_RC:
        resclass_ = new UIResRC();
        break;
    }
}

ResType UIResource::GetResType() {
    return restype_;
}

long UIResource::GetFileSize(LPCTSTR v_path) {
    if (!resclass_)
        return 0;
    int ret = 0;
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        fp = _tfopen(v_path, _T("rb"));
        if (!fp)
            UIHandleError(kLL_Error, kEC_FileFail,
                          _T("File \"%s\" can't access!"),
                          v_path);
        fseek(fp, 0, SEEK_END);
        ret = ftell(fp);
        fclose(fp);
    } else {
        ret = resclass_->GetFileSize(v_path);
        if (ret < 0)
            UIHandleError();
    }
    return ret;
}

BYTE* UIResource::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    if (!resclass_)
        return nullptr;
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        fp = _tfopen(v_path, _T("rb"));
        if (!fp) {
            UIHandleError(kLL_Error, kEC_FileFail,
                          _T("File \"%s\" can't access!"),
                          v_path);
            return nullptr;
        }
        fread(v_buffer, 1, v_size, fp);
        fclose(fp);
    } else {
        if (!resclass_->GetFile(v_path, v_buffer, v_size))
            UIHandleError();
    }
    return v_buffer;
}

void UIResource::SetResInfo(LPCTSTR v_info) {
    if (!resclass_)
        return;
    resclass_->SetResInfo(v_info);
}

LPCTSTR UIResource::GetResInfo() {
    if (!resclass_)
        return _T("");
    return resclass_->GetResInfo();
}


////////////////////////////////////////

UIXmlLoader::UIXmlLoader() {}

UIXmlLoader::UIXmlLoader(LPCTSTR v_path) {
    buffer_ = nullptr;
    Loadxml(v_path);
}

UIXmlLoader::~UIXmlLoader() {
    delete[]buffer_;
    buffer_ = nullptr;
}

void UIXmlLoader::Loadxml(LPCTSTR v_path) {
    delete[]buffer_;
    long buflen = UIResource::GetFileSize(v_path);
    buffer_ = new BYTE[buflen + 1];
    UIResource::GetFile(v_path, buffer_, buflen);
    buffer_[buflen] = '\0';
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buffer_, -1, NULL, 0);
    LPWSTR str = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buffer_, -1, str, len);
    delete[]buffer_;
    buffer_ = reinterpret_cast<BYTE*>(str);
    doc_.parse<0>((LPWSTR)buffer_);
#else
    doc_.parse<0>((LPSTR)buffer_);
#endif  // _UNICODE
}

xmlnode UIXmlLoader::GetRoot() const {
    return doc_.first_node();
}

}   // namespace DuiMini
