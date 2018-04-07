/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#include "stdafx.h"
#include "Core/Resource/UIResFile.h"
#include "Core/Resource/UIResZip.h"
#include "Core/Resource/UIResRC.h"
#include "UIResource.h"

namespace DuiMini {
shared_ptr<IUIRes> UIResource::resclass_(new UIResFile(DEFAULT_RESFOLDER));
ResType UIResource::restype_ = kRT_File;
UIResItem UIResource::res_item_;

LPVOID UIResource::LoadRes(FileType v_type, LPCTSTR v_path) {
    UIResItemIt &itend = res_item_.end();
    for (UIResItemIt it = res_item_.begin(); it != itend; ++it)
        if ((*it)->path_ == v_path) {
            ++((*it)->using_);
            return (*it)->res_;
        }

    shared_ptr<LoadedRes> tmp(new LoadedRes);
    tmp->path_ = v_path;
    tmp->type_ = v_type;
    tmp->using_ = 1;
    switch (v_type) {
    case kFT_XML:
        tmp->res_ = (LPVOID)(new UIXmlLoader(v_path));  // load failed will exit
        break;
    case kFT_PIC:
        UIRenderImage* obj = new UIRenderImage;
        if (obj->Load(v_path))
            tmp->res_ = (LPVOID)obj;
        break;
    }
    if (tmp->res_)
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
            res_item_.erase(it);
            break;
        }
}

void UIResource::SetResType(ResType v_type) {
    restype_ = v_type;
    switch (v_type) {
    case kRT_File:
        resclass_ = make_shared<UIResFile>();
        break;
    case kRT_Package:
        resclass_ = make_shared<UIResZip>();
        break;
    case kRT_RC:
        resclass_ = make_shared<UIResRC>();
        break;
    }
}

ResType UIResource::GetResType() {
    return restype_;
}

FILESIZE UIResource::GetFileSize(LPCTSTR v_path) {
    if (!resclass_)
        return -1;
    int ret = -1;
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        _tfopen_s(&fp, v_path, _T("rb"));
        if (!fp)
            UISetError(kEL_Fatal, kEC_FileFail,
                       ErrorMsg_FileFail(v_path));
        fseek(fp, 0, SEEK_END);
        ret = ftell(fp);
        fclose(fp);
    } else {
        ret = resclass_->GetFileSize(v_path);
    }
    return ret;
}

bool UIResource::GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) {
    if (!resclass_)
        return false;
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        fp = _tfopen(v_path, _T("rb"));
        if (!fp)
            UISetError(kEL_Fatal, kEC_FileFail,
                       ErrorMsg_FileFail(v_path));
        fread(v_buffer, 1, v_size, fp);
        fclose(fp);
    } else {
        return resclass_->GetFile(v_path, v_buffer, v_size);
    }
    return true;
}

void UIResource::SetResInfo(LPCTSTR v_info) {
    if (!resclass_)
        return;
    resclass_->SetResInfo(v_info);
}

CUStr UIResource::GetResInfo() {
    if (!resclass_)
        return CUStr();
    return resclass_->GetResInfo();
}
}   // namespace DuiMini
