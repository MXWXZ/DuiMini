/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UIText :public UIControl {
public:
    UIText();
    virtual ~UIText();

public:
    CUStr GetText() const;
    void SetText(LPCTSTR v_text);
    void SetFont(const UIFont &font);

public:
    ATTR_MAP_BEGIN
        UIFont &nowfont = UIConfig::GetFontStyle();
        DEFAULT_ATTR(_T("text"), _T(""))
        DEFAULT_ATTR(_T("font"), nowfont.name_)
        DEFAULT_ATTR(_T("fontname"), nowfont.font_)
        DEFAULT_ATTR(_T("fontsize"), UStr(nowfont.size_))
        DEFAULT_ATTR(_T("fontbold"), UStr(nowfont.bold_))
        DEFAULT_ATTR(_T("fontitalic"), UStr(nowfont.italic_))
        DEFAULT_ATTR(_T("fontunderline"), UStr(nowfont.underline_))
        DEFAULT_ATTR(_T("fontstrikeout"), UStr(nowfont.strikeout_))
        PARENT_ATTR(UIControl)
        DEFAULT_ATTR(_T("background"), _T("1"))
        ATTR_MAP_END

    LPVOID GetInterface(LPCTSTR v_name) override;
    void Paint(bool v_background = false) override;
    void SetAttribute(LPCTSTR v_name, LPCTSTR v_value) override;
    void AfterSetAttribute() override;

protected:
    OVERRIDE_MSGFUNC(OnLangChange)

protected:
    UIFont font_;
};
}   // namespace DuiMini
