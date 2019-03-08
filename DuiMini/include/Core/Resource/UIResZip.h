/** @file
 * Load resource in zip style.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_CORE_RESOURCE_UIRESZIP_H_
#define DUI_CORE_RESOURCE_UIRESZIP_H_

#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include "Utils/UIUnzip.h"
#include "Core/UIInterface.h"

namespace DuiMini {
class DUIMINI_API UIResZip : public IUIRes {
public:
    UIResZip();
    UIResZip(const char* info);
    virtual ~UIResZip();

    bool SetResInfo(const char* info) override;
    UIStr GetResInfo() const override;
    bool GetFile(const char* path, void* buffer, long size) override;
    long GetFileSize(const char* path) override;

protected:
    UIStr zippath_;
    UIUnzip zipcache_;
};
}  // namespace DuiMini

#endif  // !DUI_CORE_RESOURCE_UIRESZIP_H_
