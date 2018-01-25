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
Restype UIResource::restype_ = kFile;

UIResource::~UIResource() {
    delete resclass_;
    resclass_ = nullptr;
}

Restype UIResource::SetResType(Restype v_type) {
    restype_ = v_type;
    if (resclass_)
        delete resclass_;
    switch (v_type) {
    case kFile:
        resclass_ = new UIResFile();
        break;
    case kPackage:
        resclass_ = new UIResZip();
        break;
    case kRC:
        resclass_ = new UIResRC();
        break;
    }
    return restype_;
}

Restype UIResource::GetResType() {
    return restype_;
}

long UIResource::GetFileSize(LPCTSTR v_path) {
    if (!resclass_)
        return 0;
    int ret = 0;
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        fp = _tfopen(v_path, _T("rb"));
        if (!fp) {
            UIHandleError(kError, kFileFail,
                          _T("File \"%s\" can't access!"),
                          v_path);
            return 0;
        }
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
            UIHandleError(kError, kFileFail,
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

LPCTSTR UIResource::SetResInfo(LPCTSTR v_info) {
    if (!resclass_)
        return _T("");
    return resclass_->SetResInfo(v_info);
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
    if (buffer_)
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
