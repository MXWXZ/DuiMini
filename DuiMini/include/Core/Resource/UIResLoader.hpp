/** @file
 * Raw resource loader exposed to user.
 * This loader will return the resource in binary form.
 *
 * @author  MXWXZ
 * @date    2019/03/08
 */
#ifndef DUI_CORE_RESOURCE_UIRESLOADER_HPP_
#define DUI_CORE_RESOURCE_UIRESLOADER_HPP_

#include "UIDefine.h"
#include "Core/UIInterface.h"
#include "Utils/UIXmlParse.hpp"

namespace DuiMini {
class UIRawLoader : public IUILoadFile {
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

class UIXmlLoader : public IUILoadFile {
public:
    bool LoadFile(const void* buffer, long size) override {
        return doc_.load_buffer(buffer, size);
    }

    UIXmlNode GetRoot() const { return UIXmlNode(doc_.first_child()); }

protected:
    xmldoc doc_;
};
}  // namespace DuiMini

#endif  // !DUI_CORE_RESOURCE_UIRESLOADER_HPP_
