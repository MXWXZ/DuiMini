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
    // search cached res
    for (auto& i : res_item_) {
        if (i->path_ == v_path) {
            ++(i->using_);      // finded, using count+1
            return i->res_;
        }
    }

    // not find, new res
    shared_ptr<LoadedRes> tmp(new LoadedRes);
    tmp->path_ = v_path;
    tmp->type_ = v_type;
    tmp->using_ = 1;
    switch (v_type) {
    case kFT_XML:
        tmp->res_ = (LPVOID)(new UIXmlLoader(v_path));
        break;
    case kFT_PIC:
        UIRenderImage* obj = new UIRenderImage;
        obj->Load(v_path);
        tmp->res_ = (LPVOID)obj;
        break;
    }
    if (tmp->res_)
        res_item_.push_back(tmp);
    return tmp->res_;
}

void UIResource::ReleaseResByName(LPCTSTR v_path) {
    for (auto i = res_item_.begin(); i != res_item_.end();++i) {
        if ((*i)->path_ == v_path) {
            --((*i)->using_);
            if ((*i)->using_ > 0)
                break;
            res_item_.erase(i);
            break;
        }
    }
}

void UIResource::ReleaseRes(LPVOID v_res) {
    for (auto i = res_item_.begin(); i != res_item_.end(); ++i) {
        if ((*i)->res_ == v_res) {
            --((*i)->using_);
            if ((*i)->using_ > 0)
                break;
            res_item_.erase(i);
            break;
        }
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
    assert(resclass_);
    FILESIZE ret;
    if (UStr(v_path).Find(_T(":")) != -1) {  // full path
        FILE* fp;
        _tfopen_s(&fp, v_path, _T("rb"));
        if (!fp)
            ErrorMsg_FileFail(v_path);
        fseek(fp, 0, SEEK_END);
        ret = ftell(fp);
        fclose(fp);
    } else {
        ret = resclass_->GetFileSize(v_path);
        if (ret == FILESIZE(-1))
            ErrorMsg_FileFail(v_path);
    }
    return ret;
}

void UIResource::GetFile(LPCTSTR v_path, BYTE* v_buffer, FILESIZE v_size) {
    assert(resclass_);
    if (UStr(v_path).Find(_T(":")) != -1) {
        FILE* fp;
        fp = _tfopen(v_path, _T("rb"));
        if (!fp)
            ErrorMsg_FileFail(v_path);
        fread(v_buffer, 1, v_size, fp);
        fclose(fp);
    } else {
        if (!resclass_->GetFile(v_path, v_buffer, v_size))
            ErrorMsg_FileFail(v_path);
    }
}

void UIResource::SetResInfo(LPCTSTR v_info) {
    assert(resclass_);
    resclass_->SetResInfo(v_info);
}

CUStr UIResource::GetResInfo() {
    assert(resclass_);
    return resclass_->GetResInfo();
}
}   // namespace DuiMini
