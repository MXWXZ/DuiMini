/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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
    void SetMargin(LPCTSTR v_pos);
    CUStr GetMargin() const;

public:
    ATTR_MAP_BEGIN
        DEFAULT_ATTR(_T("file"), _T(""))
        DEFAULT_ATTR(_T("margin"), _T("0,0,-0,-0"))
        PARENT_ATTR(UIControl)
        ATTR_MAP_END

    LPVOID GetInterface(LPCTSTR v_name) override;
    void Paint(bool v_background = false) override;

protected:
    OVERRIDE_MSGFUNC(OnSkinChange)

protected:
    UIRenderImage *img_ = nullptr;
};
}   // namespace DuiMini
