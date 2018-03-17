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
UICFGItem UIConfig::dlg_;
SKINID    UIConfig::shownskin_ = 0;
LANGID    UIConfig::shownlang_ = 0;
FONTID    UIConfig::shownfont_ = 0;
UICFGItem UIConfig::lang_;
UICFGItem UIConfig::skin_;
UICFGItem UIConfig::font_;
UICFGItem UIConfig::sys_res_id_;
UICFGItem UIConfig::res_id_;
UICFGItem UIConfig::lang_str_;

#define CFG_BeginAttr  UIAttr _now
#define CFG_EndAttr(x) x.push_back(_now)
#define CFG_AddAttrStatic(x, y) _now[x] = y
#define CFG_AddAttr(x) _now[x] = tmp.GetAttrValue(x)
#define CFG_AddAttrDef(x, y) _now[x] = tmp.GetAttrValue(x, y)
#define CFG_CmpAttr(x, y) _now[x] == y

void UIConfig::LoadConfig(LPCTSTR v_relativepath/* = DEFAULT_RESFILE*/) {
    UIXmlLoader *config = (UIXmlLoader*)UIResource::LoadRes(kFT_XML, v_relativepath);
    for (xmlnode node = config->GetRoot()->first_node();
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
                if (CFG_CmpAttr(_T("system"), _T("1")))
                    AddSystemSkin(static_cast<SKINID>(skin_.size()));
                if (CFG_CmpAttr(_T("system"), _T("0")) &&
                    CFG_CmpAttr(_T("default"), _T("1")))
                    SetShownSkin(static_cast<SKINID>(skin_.size()));
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
                    SetShownFont(static_cast<FONTID>(font_.size()));
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
                    SetShownLang(static_cast<LANGID>(lang_.size()));
            }
        }
    }
    UIResource::ReleaseRes(config);
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
    lang_str_.clear();
    UIXmlLoader *file = (UIXmlLoader*)UIResource::LoadRes(kFT_XML, lang_[v_id - 1][_T("file")]);
    for (xmlnode node = file->GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        CFG_BeginAttr;
        CFG_AddAttr(_T("name"));
        CFG_AddAttr(_T("value"));
        CFG_EndAttr(lang_str_);
    }
    shownlang_ = v_id;
    UIResource::ReleaseRes(file);
}

void UIConfig::SetShownFont(FONTID v_id) {
    shownfont_ = v_id;
}

void UIConfig::SetShownSkin(SKINID v_id) {
    res_id_.clear();
    UIXmlLoader *file = (UIXmlLoader*)UIResource::LoadRes(kFT_XML, skin_[v_id - 1][_T("value")] + _T("\\resid.xml"));
    for (xmlnode node = file->GetRoot()->first_node();
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
    UIResource::ReleaseRes(file);
}

void UIConfig::AddSystemSkin(SKINID v_id) {
    UIXmlLoader *file = (UIXmlLoader*)UIResource::LoadRes(kFT_XML, skin_[v_id - 1][_T("value")] + _T("\\resid.xml"));
    for (xmlnode node = file->GetRoot()->first_node();
         node != nullptr;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        CFG_BeginAttr;
        CFG_AddAttr(_T("type"));
        CFG_AddAttr(_T("name"));
        CFG_AddAttr(_T("file"));
        CFG_EndAttr(sys_res_id_);
    }
    UIResource::ReleaseRes(file);
}

UIAttr* UIConfig::FindDlg(LPCTSTR v_name) {
    UIAttr* ret = UIUtils::FindNextCFGItem(dlg_, 0, _T("name"), v_name);
    if (ret)
        return ret;
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config dlg name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindDlgFile(LPCTSTR v_name) {
    UIAttr* tmp = FindDlg(v_name);
    return tmp ? (*tmp)[_T("file")] : CUStr();
}

UIAttr* UIConfig::FindResid(LPCTSTR v_name) {
    UIAttr* ret = UIUtils::FindNextCFGItem(res_id_, 0, _T("name"), v_name);
    if (ret)
        return ret;
    ret = UIUtils::FindNextCFGItem(sys_res_id_, 0, _T("name"), v_name);
    if (ret)
        return ret;
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config resid name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindResidFile(LPCTSTR v_name) {
    UIAttr* resid = FindResid(v_name);
    return resid ? (*resid)[_T("file")] : CUStr();
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
    UIAttr* ret = UIUtils::FindNextCFGItem(lang_str_, 0, _T("name"), v_name);
    if (ret)
        return ret;
    UIHandleError(kLL_Warning, kEC_IDInvalid,
                  _T("Config langstr name %s invalid!"), v_name);
    return nullptr;
}

CUStr UIConfig::FindLangMapValue(LPCTSTR v_name) {
    UIAttr* langstr = FindLangMap(v_name);
    return langstr ? (*langstr)[_T("value")] : CUStr();
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
