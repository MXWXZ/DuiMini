/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
*/
#pragma once

namespace DuiMini {
class DUIMINI_API UIResFile :public IUIRes {
public:
    UIResFile();
    UIResFile(LPCTSTR v_info);
    virtual ~UIResFile();

    void SetResInfo(LPCTSTR v_info) override;
    CUStr GetResInfo() const override;
    FILESIZE GetFileSize(LPCTSTR v_path) override;
    bool GetFile(LPCTSTR v_path, BYTE* v_buffer, FILESIZE v_size) override;

protected:
    UStr folderpath_;
};
}  // namespace DuiMini
