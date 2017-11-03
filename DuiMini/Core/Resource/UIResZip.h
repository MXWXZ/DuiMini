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
    explicit UIResZip(LPCTSTR info);
    ~UIResZip();

    void SetResInfo(LPCTSTR info) override;
    LPCTSTR GetResInfo() override;
    long GetFileSize(LPCTSTR path) override;
    bool GetFile(LPCTSTR path, BYTE* buf, long size) override;

private:
    ZFile OpenZip();

private:
    UStr fullpath_;
    ZFile zipcache_;
};
}  // namespace DuiMini
