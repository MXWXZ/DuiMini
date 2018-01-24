/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:for zip res
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIResZip :public IUIRes {
public:
    UIResZip();
    explicit UIResZip(LPCTSTR v_info);
    ~UIResZip();

    LPCTSTR SetResInfo(LPCTSTR v_info) override;
    LPCTSTR GetResInfo() const override;
    long GetFileSize(LPCTSTR v_path) override;
    bool GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) override;

private:
    ZFile OpenZip();

private:
    UStr fullpath_;
    ZFile zipcache_ = nullptr;
};
}  // namespace DuiMini
