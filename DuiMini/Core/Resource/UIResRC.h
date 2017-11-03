/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:for rc res
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIResRC :public IUIRes {
public:
    UIResRC();
    explicit UIResRC(LPCTSTR info);
    ~UIResRC();

    void SetResInfo(LPCTSTR info) override;
    LPCTSTR GetResInfo() override;
    long GetFileSize(LPCTSTR path) override;
    bool GetFile(LPCTSTR path, BYTE* buf, long size) override;

private:
    ZFile OpenZip();

private:
    UINT resid_;
    UStr tmpfullpath_;
    ZFile zipcache_;
};
}  // namespace DuiMini
