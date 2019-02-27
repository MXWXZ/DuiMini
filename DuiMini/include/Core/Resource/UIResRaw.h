/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/24
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
