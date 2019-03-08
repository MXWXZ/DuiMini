/** @file
 * Load resource in Raw style embedded in executable file.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#pragma once
#include "Core/Resource/UIResZip.h"

namespace DuiMini {
class DUIMINI_API UIResRaw : public UIResZip {
public:
    bool SetResInfo(const char* info) override;

protected:
    std::shared_ptr<unsigned char> zipbuf_;
};
}  // namespace DuiMini
