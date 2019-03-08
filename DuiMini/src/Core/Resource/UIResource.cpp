/**
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include "Core/Resource/UIResFile.h"
#include "Core/Resource/UIResZip.h"
#include "Core/Resource/UIResRaw.h"
#include "Core/Resource/UIResource.h"

namespace DuiMini {
std::shared_ptr<IUIRes> UIResource::resclass_;
ResType UIResource::restype_ = kRT_None;
UIResource::UIResItem UIResource::resitem_;

void UIResource::SetResMode(ResType type, const char* info) {
    restype_ = type;
    switch (type) {
        case kRT_None:
            resclass_ = nullptr;
            return;
        case kRT_File:
            resclass_ = std::make_shared<UIResFile>();
            break;
        case kRT_Package:
            resclass_ = std::make_shared<UIResZip>();
            break;
        case kRT_Raw:
            resclass_ = std::make_shared<UIResRaw>();
            break;
    }
    if (!resclass_->SetResInfo(info))
        UISetError(kEL_Error, "Init resource %s error!", info);
}

UIStr UIResource::GetResInfo() {
    assert(resclass_);
    return resclass_->GetResInfo();
}

bool UIResource::GetFile(const char* path, void* buffer, long size) {
    assert(resclass_);
    return resclass_->GetFile(path, buffer, size);
}

long UIResource::GetFileSize(const char* path) {
    assert(resclass_);
    return resclass_->GetFileSize(path);
}
}  // namespace DuiMini
