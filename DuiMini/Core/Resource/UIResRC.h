/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#pragma once
#include "Core/Resource/UIResZip.h"

namespace DuiMini {
class DUIMINI_API UIResRC :public UIResZip {
public:
    UIResRC();
    UIResRC(LPCTSTR v_info);
    virtual ~UIResRC();

    void SetResInfo(LPCTSTR v_info) override;
    CUStr GetResInfo() const override;

protected:
    ZFile OpenZip() override;

protected:
    UINT resid_;
};
}  // namespace DuiMini
