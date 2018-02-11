/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/01/28
 *
 * @Description:
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIImage :public UIControl {
public:
    UIImage();
    virtual ~UIImage();

public:
    bool SetFile(LPCTSTR v_path);
    CUStr GetFile() const;

public:
    ATTR_MAP_BEGIN
        DEFAULT_ATTR(_T("file"), _T(""));
        PARENT_ATTR(UIControl)
        ATTR_MAP_END

    LPVOID GetInterface(LPCTSTR v_name) override;
    void Paint() override;

protected:
    void OnSkinChange(SKINID v_former, SKINID v_new) override;

protected:
    UIRenderImage *img_ = nullptr;
};
}   // namespace DuiMini
