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
UIAttr UISystem::cfg_lang_;
UStr   UISystem::defaultskin_ = _T("default");
UIAttr UISystem::cfg_skin_;
UIAttr UISystem::cfg_sysskin_;

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

void DuiMini::UISystem::LoadConfig(LPCTSTR path/* = DEFAULT_RESFILE*/) {
    UIXmlLoader config(path);
    for (xmlnode node = config.GetRoot()->first_node();
         node != NULL;
         node = node->next_sibling()) {
        UIXmlNode tmp(node);
        // style config
        if (tmp.CmpNodeName(_T("style"))) {
            // skin config
            if (tmp.CmpAttrValue(_T("type"), _T("skin")))
                if (tmp.CmpAttrValue(_T("system"), _T("1")))
                    cfg_sysskin_[tmp.GetAttrValue(_T("name"))] =
                    tmp.GetAttrValue(_T("value"));
                else
                    cfg_skin_[tmp.GetAttrValue(_T("name"))] =
                    tmp.GetAttrValue(_T("value"));
        }

        // res config
        if (tmp.CmpNodeName(_T("res"))) {
            // lang config
            if (tmp.CmpAttrValue(_T("type"), _T("lang")))
                cfg_lang_[tmp.GetAttrValue(_T("name"))] =
                tmp.GetAttrValue(_T("file"));
        }
    }
}

}   // namespace DuiMini
