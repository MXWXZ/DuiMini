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
    explicit UIResRC(LPCTSTR v_info);
    ~UIResRC();

    LPCTSTR SetResInfo(LPCTSTR v_info) override;
    LPCTSTR GetResInfo() const override;
    long GetFileSize(LPCTSTR v_path) override;
    bool GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) override;

private:
    ZFile OpenZip();

private:
    UINT resid_;
    UStr tmpfullpath_;
    ZFile zipcache_ = nullptr;
};
}  // namespace DuiMini
