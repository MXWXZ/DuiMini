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
    explicit UIResFile(LPCTSTR info);

    void SetResInfo(LPCTSTR info) override;
    LPCTSTR GetResInfo() override;
    long GetFileSize(LPCTSTR path) override;
    bool GetFile(LPCTSTR path, BYTE* buf, long size) override;

private:
    UStr folderpath_;
};
}  // namespace DuiMini
