/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIResZip :public IUIRes {
public:
    UIResZip();
    UIResZip(LPCTSTR v_info);
    virtual ~UIResZip();

    void SetResInfo(LPCTSTR v_info) override;
    CUStr GetResInfo() const override;
    FILESIZE GetFileSize(LPCTSTR v_path) override;
    bool GetFile(LPCTSTR v_path, BYTE* v_buffer, FILESIZE v_size) override;

protected:
    virtual ZFile OpenZip();

protected:
    UStr fullpath_;
    ZFile zipcache_ = nullptr;
};
}  // namespace DuiMini
