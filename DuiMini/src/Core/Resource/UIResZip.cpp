/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/10
 */
#include "Core/Resource/UIResZip.h"

namespace DuiMini {
UIResZip::UIResZip() {}

UIResZip::UIResZip(const char* info) { SetResInfo(info); }

UIResZip::~UIResZip() { zipcache_.CloseZip(); }

bool UIResZip::SetResInfo(const char* info) {
    zippath_ = info;
    return zipcache_.OpenZip(zippath_.GetData());
}

UIStr UIResZip::GetResInfo() const { return zippath_; }

bool UIResZip::GetFile(const char* path, void* buffer, long size) {
    return zipcache_.GetFile(path, buffer, size);
}

long UIResZip::GetFileSize(const char* path) {
    return zipcache_.GetFileSize(path);
}

}  // namespace DuiMini
