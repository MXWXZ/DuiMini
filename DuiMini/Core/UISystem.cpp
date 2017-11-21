/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "DuiMini.h"
#include "UISystem.h"

namespace DuiMini {
HINSTANCE UISystem::instance_;
UINT   UISystem::cfg_shownskin_ = 0;
UINT   UISystem::cfg_shownlang_ = 0;
UINT   UISystem::cfg_shownfont_ = 0;
UIAttrSet UISystem::cfg_lang_;
UIAttrSet UISystem::cfg_skin_;
UIAttrSet UISystem::cfg_font_;

void UISystem::Init(HINSTANCE inst) {
    _tsetlocale(LC_ALL, _T(""));
    SetInstance(inst);
}

void UISystem::Cleanup() {
}

void UISystem::Exit(const int code /*= 0*/) {
    Cleanup();
    exit(code);
}

#define CFG_BeginAttr  UIAttr now
#define CFG_EndAttr(x) x.AddAttr(now)
#define CFG_AddAttr(x) now[x] = tmp.GetAttrValue(x)
#define CFG_AddAttrDef(x, y) now[x] = tmp.GetAttrValue(x, y)
#define CFG_CmpAttr(x, y) now[x] == y

void UISystem::LoadConfig(LPCTSTR path/* = DEFAULT_RESFILE*/) {
    UIXmlLoader config(path);
    for (xmlnode node = config.GetRoot()->first_node();
         node != NULL;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        // style config
        if (tmp.CmpNodeName(_T("style"))) {
            // skin config
            if (tmp.CmpAttrValue(_T("type"), _T("skin"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("name"));
                CFG_AddAttr(_T("value"));
                CFG_AddAttrDef(_T("system"), 0);
                if (CFG_CmpAttr(_T("system"), _T("0"))) {
                    CFG_AddAttrDef(_T("default"), 0);
                    if (CFG_CmpAttr(_T("default"), _T("1")))
                        cfg_shownskin_ = cfg_skin_.GetSize();
                }
                CFG_EndAttr(cfg_skin_);
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
            }
        }

        // res config
        if (tmp.CmpNodeName(_T("res"))) {
            // lang config
            if (tmp.CmpAttrValue(_T("type"), _T("lang"))) {
                CFG_BeginAttr;
                CFG_AddAttr(_T("lang"));
                CFG_AddAttr(_T("file"));
                CFG_AddAttrDef(_T("default"), 0);
                if (CFG_CmpAttr(_T("default"), _T("1")))
                    cfg_shownlang_ = cfg_skin_.GetSize();
                CFG_EndAttr(cfg_lang_);
            }
        }
    }

    // default font set
    UStr langname = cfg_lang_[cfg_shownlang_][_T("lang")];
    cfg_shownfont_ = cfg_font_.FindNextAttr(0, _T("lang"), langname);
    {
        int i = cfg_shownfont_ + 1;
        while ((i = cfg_font_.FindNextAttr(i, _T("default"), _T("1"))) != -1) {
            if (cfg_font_[i][_T("lang")] == langname)
                cfg_shownfont_ = i;
            ++i;
        }
    }
    if (cfg_shownfont_ == -1) {
        UIException::SetError(kLoglevel_Error, kErrorCode_FileFormat,
                              _T("File \"%s\" format error!"), path);
        HandleError();
    }
}

}   // namespace DuiMini
