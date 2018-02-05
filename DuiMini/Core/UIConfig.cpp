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
UIAttrSet UIConfig::cfg_dlg_;
UINT   UIConfig::cfg_shownskin_ = 0;
UINT   UIConfig::cfg_shownlang_ = 0;
UINT   UIConfig::cfg_shownfont_ = 0;
UIAttrSet UIConfig::cfg_lang_;
UIAttrSet UIConfig::cfg_skin_;
UIAttrSet UIConfig::cfg_font_;
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
                CFG_EndAttr(cfg_skin_);
                if (CFG_CmpAttr(_T("system"), _T("0")) &&
                    CFG_CmpAttr(_T("default"), _T("1")))
                    SetShownSkin(cfg_skin_.GetSize() - 1);
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
                CFG_EndAttr(cfg_font_);
                if (CFG_CmpAttr(_T("default"), _T("1")) &&
                    CFG_CmpAttr(_T("lang"), cfg_lang_[cfg_shownlang_][_T("lang")]))
                    SetShownFont(cfg_font_.GetSize() - 1);
            }
        }

        // res config
        if (tmp.CmpNodeName(_T("res"))) {
            // dlg config
            if (tmp.CmpAttrValue(_T("type"), _T("dlg"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("name"));
                CFG_AddAttr(_T("file"));
                CFG_EndAttr(cfg_dlg_);
            }
            // lang config
            if (tmp.CmpAttrValue(_T("type"), _T("lang"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("lang"));
                CFG_AddAttr(_T("file"));
                CFG_AddAttrDef(_T("default"), 0);
                CFG_EndAttr(cfg_lang_);
                if (CFG_CmpAttr(_T("default"), _T("1")))
                    SetShownLang(cfg_lang_.GetSize() - 1);
            }
        }
    }
}

UIAttrSet* UIConfig::GetLang() {
    return &cfg_lang_;
}

UIAttrSet* UIConfig::GetFont() {
    return &cfg_font_;
}

UIAttrSet* UIConfig::GetSkin() {
    return &cfg_skin_;
}

UIAttrSet* UIConfig::GetDlg() {
    return &cfg_dlg_;
}

UIAttrSet* UIConfig::GetResid() {
    return &res_id_;
}

UIAttrSet* UIConfig::GetLangstr() {
    return &lang_str_;
}

UINT UIConfig::GetCFGShownLang() {
    return cfg_shownlang_;
}

UINT UIConfig::GetCFGShownFont() {
    return cfg_shownfont_;
}

UINT UIConfig::GetCFGShownSkin() {
    return cfg_shownskin_;
}

// TODO
UINT UIConfig::SetShownLang(UINT v_id) {
    lang_str_.Clear();
    UIXmlLoader file(cfg_lang_[v_id][_T("file")]);
    for (xmlnode node = file.GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        CFG_BeginAttr;
        CFG_AddAttr(_T("name"));
        CFG_AddAttr(_T("value"));
        CFG_EndAttr(lang_str_);
    }
    cfg_shownlang_ = v_id;
    return cfg_shownlang_;
}

UINT UIConfig::SetShownFont(UINT v_id) {
    cfg_shownfont_ = v_id;
    return cfg_shownfont_;
}

UINT UIConfig::SetShownSkin(UINT v_id) {
    res_id_.Clear();
    UIXmlLoader file(cfg_skin_[v_id][_T("value")] + _T("\\resid.xml"));
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
    cfg_shownskin_ = v_id;
    return cfg_shownskin_;
}

UIAttr* UIConfig::FindDlg(LPCTSTR v_name) {
    int ret = cfg_dlg_.FindNextAttr(0, _T("name"), v_name);
    if (ret != -1)
        return &cfg_dlg_[ret];
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config dlg name %s invalid!"), v_name);
    return nullptr;
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
    if (!resid)
        return CUStr();
    else
        return resid->GetValue(_T("file"));
}

CUStr UIConfig::GetStrFile(LPCTSTR v_str) {
    CUStr str = v_str;
    int len = str.GetLength();
    if (len == 0)
        return CUStr();
    if (str[0] == '[' && str[len - 1] == ']')
        return FindResidFile(str.Mid(1, len - 2));
    else
        return str;
}

UIAttr* UIConfig::FindLangstr(LPCTSTR v_name) {
    int ret = lang_str_.FindNextAttr(0, _T("name"), v_name);
    if (ret != -1)
        return &lang_str_[ret];
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config langstr name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindLangstrValue(LPCTSTR v_name) {
    UIAttr* langstr = FindLangstr(v_name);
    if (!langstr)
        return CUStr();
    else
        return langstr->GetValue(_T("value"));
}

CUStr UIConfig::GetStrStr(LPCTSTR v_str) {
    UStr str = v_str;
    int len = str.GetLength();
    if (len == 0)
        return CUStr();
    if (str[0] == '[' && str[len - 1] == ']')
        return FindLangstrValue(str.Mid(1, len - 2));
    else if(str[0]=='\\' && str[1]=='[' && str[len - 1] == ']')
        return str.Mid(1, len - 1);
    else
        return str;
}
}   // namespace DuiMini
