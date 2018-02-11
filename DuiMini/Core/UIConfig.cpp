/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/01/24
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIConfig.h"

namespace DuiMini {
UIAttrSet UIConfig::dlg_;
SKINID    UIConfig::shownskin_ = 0;
LANGID    UIConfig::shownlang_ = 0;
FONTID    UIConfig::shownfont_ = 0;
UIAttrSet UIConfig::lang_;
UIAttrSet UIConfig::skin_;
UIAttrSet UIConfig::font_;
UIAttrSet UIConfig::res_id_;
UIAttrSet UIConfig::lang_str_;

#define CFG_BeginAttr  UIAttr _now
#define CFG_EndAttr(x) x.AddAttr(_now)
#define CFG_AddAttrStatic(x, y) _now[x] = y
#define CFG_AddAttr(x) _now[x] = tmp.GetAttrValue(x)
#define CFG_AddAttrDef(x, y) _now[x] = tmp.GetAttrValue(x, y)
#define CFG_CmpAttr(x, y) _now[x] == y

void UIConfig::LoadConfig(LPCTSTR v_relativepath/* = DEFAULT_RESFILE*/) {
    UIXmlLoader config(v_relativepath);
    for (xmlnode node = config.GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        // style config
        if (tmp.CmpNodeName(_T("style"))) {
            // skin config
            if (tmp.CmpAttrValue(_T("type"), _T("skin"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("name"));
                CFG_AddAttr(_T("value"));
                CFG_AddAttrDef(_T("default"), 0);
                CFG_AddAttrDef(_T("system"), 0);
                if (CFG_CmpAttr(_T("system"), _T("1")))
                    CFG_AddAttrStatic(_T("default"), _T("0"));
                CFG_EndAttr(skin_);
                if (CFG_CmpAttr(_T("system"), _T("0")) &&
                    CFG_CmpAttr(_T("default"), _T("1")))
                    SetShownSkin(skin_.GetSize());
            }

            // font config
            if (tmp.CmpAttrValue(_T("type"), _T("font"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("lang"));
                CFG_AddAttr(_T("name"));
                CFG_AddAttr(_T("font"));
                CFG_AddAttr(_T("size"));
                CFG_AddAttrDef(_T("bold"), 0);
                CFG_AddAttrDef(_T("italic"), 0);
                CFG_AddAttrDef(_T("underline"), 0);
                CFG_AddAttrDef(_T("strikeout"), 0);
                CFG_AddAttrDef(_T("default"), 0);
                CFG_EndAttr(font_);
                if (CFG_CmpAttr(_T("default"), _T("1")) &&
                    CFG_CmpAttr(_T("lang"), lang_[shownlang_][_T("lang")]))
                    SetShownFont(font_.GetSize());
            }
        }

        // res config
        if (tmp.CmpNodeName(_T("res"))) {
            // dlg config
            if (tmp.CmpAttrValue(_T("type"), _T("dlg"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("name"));
                CFG_AddAttr(_T("file"));
                CFG_EndAttr(dlg_);
            }
            // lang config
            if (tmp.CmpAttrValue(_T("type"), _T("lang"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("lang"));
                CFG_AddAttr(_T("file"));
                CFG_AddAttrDef(_T("default"), 0);
                CFG_EndAttr(lang_);
                if (CFG_CmpAttr(_T("default"), _T("1")))
                    SetShownLang(lang_.GetSize());
            }
        }
    }
}

LANGID UIConfig::GetShownLang() {
    return shownlang_;
}

FONTID UIConfig::GetShownFont() {
    return shownfont_;
}

SKINID UIConfig::GetShownSkin() {
    return shownskin_;
}

// TODO
void UIConfig::SetShownLang(LANGID v_id) {
    lang_str_.Clear();
    UIXmlLoader file(lang_[v_id - 1][_T("file")]);
    for (xmlnode node = file.GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        CFG_BeginAttr;
        CFG_AddAttr(_T("name"));
        CFG_AddAttr(_T("value"));
        CFG_EndAttr(lang_str_);
    }
    shownlang_ = v_id;
}

void UIConfig::SetShownFont(FONTID v_id) {
    shownfont_ = v_id;
}

void UIConfig::SetShownSkin(SKINID v_id) {
    res_id_.Clear();
    UIXmlLoader file(skin_[v_id - 1][_T("value")] + _T("\\resid.xml"));
    for (xmlnode node = file.GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        CFG_BeginAttr;
        CFG_AddAttr(_T("type"));
        CFG_AddAttr(_T("name"));
        CFG_AddAttr(_T("file"));
        CFG_EndAttr(res_id_);
    }
    shownskin_ = v_id;
}

UIAttr* UIConfig::FindDlg(LPCTSTR v_name) {
    int ret = dlg_.FindNextAttr(0, _T("name"), v_name);
    if (ret != -1)
        return &dlg_[ret];
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config dlg name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindDlgFile(LPCTSTR v_name) {
    UIAttr* tmp = FindDlg(v_name);
    if (tmp)
        return tmp->GetValue(_T("file"));
    else
        return CUStr();
}

UIAttr* UIConfig::FindResid(LPCTSTR v_name) {
    int ret = res_id_.FindNextAttr(0, _T("name"), v_name);
    if (ret != -1)
        return &res_id_[ret];
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config resid name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindResidFile(LPCTSTR v_name) {
    UIAttr* resid = FindResid(v_name);
    if (resid)
        return resid->GetValue(_T("file"));
    else
        return CUStr();
}

CUStr UIConfig::GetStrPath(LPCTSTR v_str) {
    CUStr str = v_str;
    int len = str.GetLength();
    if (len == 0)
        return CUStr();
    if (str[0] == '[' && str[len - 1] == ']')
        return FindResidFile(str.Mid(1, len - 2));
    else
        return str;
}

UIAttr* UIConfig::FindLangMap(LPCTSTR v_name) {
    int ret = lang_str_.FindNextAttr(0, _T("name"), v_name);
    if (ret != -1)
        return &lang_str_[ret];
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config langstr name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindLangMapValue(LPCTSTR v_name) {
    UIAttr* langstr = FindLangMap(v_name);
    if (!langstr)
        return CUStr();
    else
        return langstr->GetValue(_T("value"));
}

CUStr UIConfig::TranslateStr(LPCTSTR v_str) {
    UStr str = v_str;
    int len = str.GetLength();
    if (len == 0)
        return CUStr();
    if (str[0] == '[' && str[len - 1] == ']')
        return FindLangMapValue(str.Mid(1, len - 2));
    else if(str[0]=='\\' && str[1]=='[' && str[len - 1] == ']')
        return str.Mid(1, len - 1);
    else
        return str;
}
}   // namespace DuiMini
