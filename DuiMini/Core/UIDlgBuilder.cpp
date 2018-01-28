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
    delete ctrl_root_;
    ctrl_root_ = nullptr;
}

UIControl* UIDlgBuilder::Init(xmlnode v_root, UIWindow* v_wnd) {
    delete ctrl_root_;
    ctrl_root_ = nullptr;
    xml_root_ = v_root;
    basewnd_ = v_wnd;
    return _Parse(xml_root_);
}

UIControl* UIDlgBuilder::GetCtrlRoot() {
    return ctrl_root_;
}

UIControl* UIDlgBuilder::_Parse(xmlnode v_root,
                                UIControl* v_parent/* = nullptr*/) {
    for (xmlnode node = v_root; node != nullptr;
         node = node->next_sibling()) {
        LPCTSTR ctrl_name = node->name();
        UINT ctrl_namelen = _tcslen(ctrl_name);
        UIControl* new_ctrl = nullptr;
        switch (ctrl_namelen) {
        case 3:
        {
            if (CmpStr(ctrl_name, _T("dlg")))
                new_ctrl = new UIDialog;
            if (CmpStr(ctrl_name, _T("img")))
                new_ctrl = new UIImage;
            break;
        }
        case 9:
        {
            if (CmpStr(ctrl_name, _T("container")))
                new_ctrl = new UIContainer;

            break;
        }
        }

        // Invalid ctrl name
        if (!new_ctrl) {
            UISetError(kWarning, kCtrlKindInvalid,
                       _T("Control Kind \"%s\" invalid"), ctrl_name);
            return nullptr;
        }
        // Set basewnd
        new_ctrl->SetBaseWindow(basewnd_);
        // Add children
        if (node->first_node())
            _Parse(node->first_node(), new_ctrl);
        // Attach to parent (parent must have container attribute)
        if (v_parent != nullptr) {
            IUIContainer* container = reinterpret_cast<IUIContainer*>(v_parent->GetInterface(_T("container")));
            if (!container)
                return nullptr;
            container->Add(new_ctrl);
            new_ctrl->SetParent(v_parent);
        }
        // Process attributes
        if (node->first_attribute()) {
            new_ctrl->BeforeSetAttribute();
            for (xmlattr attr = node->first_attribute();
                 attr != nullptr;
                 attr = attr->next_attribute())
                new_ctrl->SetAttribute(attr->name(), attr->value());
            new_ctrl->AfterSetAttribute();
        }

        // Return first item
        if (!ctrl_root_)
            ctrl_root_ = new_ctrl;
    }
    return ctrl_root_;
}
}    // namespace DuiMini
