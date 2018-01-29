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
    if (!v_wnd)
        return nullptr;
    delete ctrl_root_;
    ctrl_root_ = nullptr;
    xml_root_ = v_root;
    return _Parse(v_wnd, xml_root_);
}

UIDialog* UIDlgBuilder::GetCtrlRoot() {
    return ctrl_root_;
}

UIControl* UIDlgBuilder::_Parse(UIWindow* v_wnd, xmlnode v_root,
                                UIControl* v_parent/* = nullptr*/) {
    for (xmlnode node = v_root; node != nullptr;
         node = node->next_sibling()) {
        if (!v_parent && !CmpStr(node->name(), CTRLNAME_DIALOG)) {
            UISetError(kWarning, kCtrlFormatInvalid,
                       _T("Dialog control must be the root."));
            return nullptr;
        }
        LPCTSTR ctrl_name = node->name();
        UINT ctrl_namelen = _tcslen(ctrl_name);
        UIControl* new_ctrl = nullptr;
        switch (ctrl_namelen) {
        case 3:
        {
            if (CmpStr(ctrl_name, CTRLNAME_DIALOG)) {
                if (v_parent) {
                    UISetError(kWarning, kCtrlFormatInvalid,
                               _T("Dialog control do not allow nesting."));
                    return nullptr;
                }
                new_ctrl = new UIDialog;
                ctrl_root_ = reinterpret_cast<UIDialog*>(new_ctrl);
            }
            if (CmpStr(ctrl_name, CTRLNAME_IMAGE))
                new_ctrl = new UIImage;
            break;
        }
        case 9:
        {
            if (CmpStr(ctrl_name, CTRLNAME_CONTAINER))
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
        new_ctrl->SetBaseWindow(v_wnd);
        // Attach to parent (parent must have container attribute)
        if (v_parent != nullptr) {
            IUIContainer* container = dynamic_cast<IUIContainer*>((UIControl*)v_parent->GetInterface(_T("container")));
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
        // Add children
        if (node->first_node())
            _Parse(v_wnd, node->first_node(), new_ctrl);
    }
    return ctrl_root_;
}
}    // namespace DuiMini
