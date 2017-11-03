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
#include "DuiMini.h"
#include "Core/Resource/UIResFile.h"
#include "Core/Resource/UIResZip.h"
#include "Core/Resource/UIResRC.h"
#include "UIResource.h"

namespace DuiMini {
IUIRes* UIResource::resclass_ = new UIResFile(DEFAULT_RESFOLDER);
Restype UIResource::restype_ = kRestype_File;

UIResource::~UIResource() {
    delete resclass_;
    resclass_ = NULL;
}

void UIResource::SetResType(Restype type) {
    restype_ = type;
    if (resclass_ != NULL)
        delete resclass_;
    switch (type) {
    case kRestype_File:
        resclass_ = new UIResFile();
        break;
    case kRestype_Package:
        resclass_ = new UIResZip();
        break;
    case kRestype_RC:
        resclass_ = new UIResRC();
        break;
    default:
        break;
    }
}

long UIResource::GetFileSize(LPCTSTR path) {
    int ret = resclass_->GetFileSize(path);
    if (ret < 0)
        HandleError();
    return ret;
}

BYTE* UIResource::GetFile(LPCTSTR path, BYTE* buf, long size) {
    if (!resclass_->GetFile(path, buf, size))
        HandleError();
    return buf;
}

void UIResource::SetResInfo(LPCTSTR info) {
    resclass_->SetResInfo(info);
}

LPCTSTR UIResource::GetResInfo() {
    return resclass_->GetResInfo();
}


////////////////////////////////////////

UIXmlLoader::UIXmlLoader() {
    buf = NULL;
}

UIXmlLoader::UIXmlLoader(LPCTSTR path) {
    buf = NULL;
    Loadxml(path);
}

UIXmlLoader::~UIXmlLoader() {
    delete[]buf;
    buf = NULL;
}

bool UIXmlLoader::IsValid() const {
    if (buf != NULL)
        return true;
    else
        return false;
}

void UIXmlLoader::Loadxml(LPCTSTR path) {
    if (buf != NULL)
        delete[]buf;
    long buflen = UIResource::GetFileSize(path);
    buf = new BYTE[buflen + 1];
    UIResource::GetFile(path, buf, buflen);
    buf[buflen] = '\0';
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buf, -1, NULL, 0);
    LPWSTR str = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buf, -1, str, len);
    delete[]buf;
    buf = reinterpret_cast<BYTE*>(str);
    doc.parse<0>((LPWSTR)buf);
#else
    doc.parse<0>((LPSTR)buf);
#endif  // _UNICODE
}

xmlnode UIXmlLoader::GetRoot() const {
    if (IsValid())
        return doc.first_node();
    else
        return NULL;
}

}   // namespace DuiMini
