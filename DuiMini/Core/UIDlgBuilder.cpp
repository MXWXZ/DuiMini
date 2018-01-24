/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/04
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIDlgBuilder.h"

namespace DuiMini {
UIDlgBuilder::UIDlgBuilder() {}

UIDlgBuilder::~UIDlgBuilder() {
    delete ctrlroot_;
    ctrlroot_ = nullptr;
    basewnd_ = nullptr;
    xmlroot_ = nullptr;
}

UIControl* UIDlgBuilder::Init(xmlnode v_root, UIWindow* v_wnd) {
    delete ctrlroot_;
    ctrlroot_ = nullptr;
    xmlroot_ = v_root;
    basewnd_ = v_wnd;
    return _Parse(xmlroot_);
}

UIControl * UIDlgBuilder::GetCtrlRoot() {
    return ctrlroot_;
}

UIControl* UIDlgBuilder::_Parse(xmlnode v_root,
                                UIControl* v_parent/* = nullptr*/) {
    for (xmlnode node = xmlroot_; node != nullptr;
         node = node->next_sibling()) {
        LPCTSTR ctrlname = node->name();
        UINT namelen = _tcslen(ctrlname);
        UIControl* tmpctrl = nullptr;
        IUIContainer* container = nullptr;
        switch (namelen) {
        case 3:
        {
            if (CmpStr(ctrlname, _T("Dlg")))
                tmpctrl = new UIDialog;

            break;
        }
        case 9:
        {
            if (CmpStr(ctrlname, _T("Container")))
                tmpctrl = new UIContainer;

            break;
        }
        }

        // Invalid ctrl name
        if (!tmpctrl) {
            UIHandleError(kWarning, kCtrlKindInvalid,
                          _T("Control Kind \"%s\" invalid"), ctrlname);
            return nullptr;
        }
        // Set basewnd
        tmpctrl->SetBaseWindow(basewnd_);
        // Add children
        if (node->first_node())
            _Parse(node, tmpctrl);
        // Attach to parent (parent must have container attribute)
        if (v_parent != nullptr) {
            if (!container)
                container = reinterpret_cast<IUIContainer*>(v_parent->GetInterface(_T("Container")));
            container->Add(tmpctrl);
            tmpctrl->SetParent(v_parent);
        }
        // Process attributes
        if (node->first_attribute()) {
            for (xmlattr attr = node->first_attribute();
                 attr != nullptr;
                 attr = attr->next_attribute())
                tmpctrl->SetAttribute(attr->name(), attr->value());
            tmpctrl->AfterSetAttribute();
        }

        // Return first item
        if (!ctrlroot_)
            ctrlroot_ = tmpctrl;
    }
    return ctrlroot_;
}
}    // namespace DuiMini
