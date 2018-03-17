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
UIResItem UIResource::res_item_;

UIResource::~UIResource() {
    delete resclass_;
    resclass_ = nullptr;
    UIResItemIt &itend = res_item_.end();
    for (UIResItemIt it = res_item_.begin(); it != itend; ++it)
        delete *it;
    res_item_.clear();
}

LPVOID UIResource::LoadRes(FileType v_type, LPCTSTR v_path, bool* v_result/* = nullptr*/) {
    UIResItemIt &itend = res_item_.end();
    for (UIResItemIt it = res_item_.begin(); it != itend; ++it)
        if ((*it)->path_ == v_path) {
            ++((*it)->using_);
            if (v_result)
                *v_result = true;
            return (*it)->res_;
        }

    bool res = false;
    LoadedRes *tmp = new LoadedRes;
    tmp->path_ = v_path;
    tmp->type_ = v_type;
    tmp->using_ = 1;
    switch (v_type) {
    case kFT_XML:
        tmp->res_ = reinterpret_cast<LPVOID>(new UIXmlLoader(v_path));
        res = true;
        break;
    case kFT_PIC:
        UIRenderImage* obj = new UIRenderImage;
        res = obj->Load(v_path);
        tmp->res_ = reinterpret_cast<LPVOID>(obj);
        break;
    }
    if (v_result)
        *v_result = res;
    res_item_.push_back(tmp);
    return tmp->res_;
}

void UIResource::ReleaseResByName(LPCTSTR v_path) {
    UIResItemIt &itend = res_item_.end();
    for (UIResItemIt it = res_item_.begin(); it != itend; ++it)
        if ((*it)->path_ == v_path) {
            --((*it)->using_);
            if ((*it)->using_ > 0)
                break;
            delete *it;
            res_item_.erase(it);
            break;
        }
}

void UIResource::ReleaseRes(LPVOID v_res) {
    UIResItemIt &itend = res_item_.end();
    for (UIResItemIt it = res_item_.begin(); it != itend; ++it)
        if ((*it)->res_ == v_res) {
            --((*it)->using_);
            if ((*it)->using_ > 0)
                break;
            delete *it;
            res_item_.erase(it);
            break;
        }
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
    BYTE *tmp = new BYTE[buflen + 1];
    UIResource::GetFile(v_path, tmp, buflen);
    tmp[buflen] = '\0';
#ifdef _UNICODE
    int len = GetStr2WStrLen((LPCSTR)tmp);
    LPWSTR wtmp = new wchar_t[len];
    Str2WStr((LPCSTR)tmp, wtmp, len);
    delete[]tmp;
    buffer_ = reinterpret_cast<TBYTE*>(wtmp);
#else
    buffer_ = tmp;
#endif  // _UNICODE
    doc_.parse<0>((LPTSTR)buffer_);
}

xmlnode UIXmlLoader::GetRoot() const {
    return doc_.first_node();
}

}   // namespace DuiMini
