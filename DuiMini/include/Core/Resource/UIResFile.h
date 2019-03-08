/** @file
 * Load resource in plain file style.
 *
 * @author  MXWXZ
 * @date    2019/03/08
 */
#ifndef DUI_CORE_RESOURCE_UIRESFILE_H_
#define DUI_CORE_RESOURCE_UIRESFILE_H_

#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include "Core/UIInterface.h"

namespace DuiMini {
class DUIMINI_API UIResFile : public IUIRes {
public:
    UIResFile();
    UIResFile(const char* info);
    virtual ~UIResFile();

    bool SetResInfo(const char* info) override;
    UIStr GetResInfo() const override;
    bool GetFile(const char* path, void* buffer, long size) override;
    long GetFileSize(const char* path) override;

protected:
    UIStr path_;
};
}  // namespace DuiMini

#endif  // !DUI_CORE_RESOURCE_UIRESFILE_H_
