/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIText.h"

namespace DuiMini {
UIText::UIText() {}

UIText::~UIText() {}

CUStr UIText::GetText() const {
    return GetAttribute(_T("text"));
}

void UIText::SetText(LPCTSTR v_text) {
    SetAttribute(_T("text"), UITranslateStr(v_text));
}

void UIText::SetFont(const UIFont &font) {
    UIControl::SetAttribute(_T("font"), font.name_); // prevent recursion
    SetAttribute(_T("fontname"), font.font_);
    SetAttribute(_T("fontsize"), UStr(font.size_));
    SetAttribute(_T("fontbold"), UStr(font.bold_));
    SetAttribute(_T("fontitalic"), UStr(font.italic_));
    SetAttribute(_T("fontunderline"), UStr(font.underline_));
    SetAttribute(_T("fontstrikeout"), UStr(font.strikeout_));
}

void UIText::SetColor(LPCTSTR v_color) {
    SetAttribute(_T("color"), v_color);
}

UIColor UIText::GetColor() const {
    return UIColor(GetAttribute(_T("color")));
}

void UIText::SetTrimming(LPCTSTR v_trimming) {
    SetAttribute(_T("trimming"), v_trimming);
}

StringTrimming UIText::GetTrimming() const {
    UStr trimming = GetAttribute(_T("trimming"));
    if (trimming == _T("none"))
        return kST_None;
    if (trimming == _T("ch"))
        return kST_Ch;
    if (trimming == _T("word"))
        return kST_Word;
    if (trimming == _T("dotch"))
        return kST_DotCh;
    if (trimming == _T("dotword"))
        return kST_DotWord;
    if (trimming == _T("dotmid"))
        return kST_DotMid;
    return kST_None;
}

bool UIText::AutoWrap(BOOL v_autowrap/* = TRUE*/) {
    STATE_FUNC_START(_T("autowrap"), v_autowrap)
        STATE_FUNC_END
}

bool UIText::Vertical(BOOL v_vertical) {
    STATE_FUNC_START(_T("vertical"), v_vertical)
        STATE_FUNC_END
}

void UIText::SetAlign(LPCTSTR v_align) {
    SetAttribute(_T("align"), v_align);
}

StringAlign UIText::GetAlign() const {
    UStr trimming = GetAttribute(_T("align"));
    if (trimming == _T("lt"))
        return kSA_LT;
    if (trimming == _T("mt"))
        return kSA_MT;
    if (trimming == _T("rt"))
        return kSA_RT;
    if (trimming == _T("lm"))
        return kSA_LM;
    if (trimming == _T("mm"))
        return kSA_MM;
    if (trimming == _T("rm"))
        return kSA_RM;
    if (trimming == _T("lb"))
        return kSA_LB;
    if (trimming == _T("mb"))
        return kSA_MB;
    if (trimming == _T("rb"))
        return kSA_RB;
    return kSA_LT;
}

LPVOID UIText::GetInterface(LPCTSTR v_name) {
    if (CmpStr(v_name, CTRLNAME_TEXT))
        return this;
    return UIControl::GetInterface(v_name);
}

void UIText::Paint(bool v_background/* = false*/) {
    if (!basewnd_)
        return;
    UIStringFormat format;
    format.color_ = GetColor();
    format.trimming_ = GetTrimming();
    format.autowrap_ = AutoWrap(STAY);
    format.vertical_ = Vertical(STAY);
    format.align_ = GetAlign();
    format.color_.a *= (double)GetAlpha() / 255;
    basewnd_->GetRender()->DrawString(GetText(), font_, format, rect_);
    UIControl::Paint(v_background);
}

void UIText::SetAttribute(LPCTSTR v_name, LPCTSTR v_value) {
    if (CmpStr(v_name, _T("font")))
        SetFont(UIConfig::FindFontValue(v_value));
    UIControl::SetAttribute(v_name, v_value);
}

void UIText::AfterSetAttribute() {
    UIControl::AfterSetAttribute();
    font_.font_= GetAttribute(_T("fontname"));
    font_.size_ = (USHORT)GetAttribute(_T("fontsize")).Str2LL();
    font_.bold_ = GetAttribute(_T("fontbold")).Str2LL();
    font_.italic_ = GetAttribute(_T("fontitalic")).Str2LL();
    font_.underline_ = GetAttribute(_T("fontunderline")).Str2LL();
    font_.strikeout_ = GetAttribute(_T("fontstrikeout")).Str2LL();
}

bool UIText::OnLangChange(const UIEvent& v_event) {
    SetText(GetText());
    return UIControl::OnLangChange(v_event);
}

}   // namespace DuiMini
