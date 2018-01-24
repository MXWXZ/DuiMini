/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/11/02
 *
 * @Description:for file res
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIResFile :public IUIRes {
public:
    UIResFile();
    explicit UIResFile(LPCTSTR v_info);
    ~UIResFile();

    LPCTSTR SetResInfo(LPCTSTR v_info) override;
    LPCTSTR GetResInfo() const override;
    long GetFileSize(LPCTSTR v_path) override;
    bool GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size) override;

private:
    UStr folderpath_;
};
}  // namespace DuiMini
