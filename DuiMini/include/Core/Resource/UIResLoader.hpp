/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/26
 */
#ifndef DUI_CORE_RESOURCE_UIRESLOADER_HPP_
#define DUI_CORE_RESOURCE_UIRESLOADER_HPP_

#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include "Core/UIInterface.h"
#include "Core/Resource/UIResource.h"

namespace DuiMini {
class DUIMINI_API UIRawLoader : public IUILoadFile {
public:
    const void* GetFile() const { return buffer_; }
    long GetFileSize() const { return buffersize_; }
    bool LoadFile(const void* buffer, long size) override {
        buffer_ = buffer;
        buffersize_ = size;
        return true;
    }

protected:
    const void* buffer_;
    long buffersize_;
};
}  // namespace DuiMini

#endif  // !DUI_CORE_RESOURCE_UIRESLOADER_HPP_
