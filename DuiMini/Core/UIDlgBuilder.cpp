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
    return Parse(v_wnd, xml_root_);
}

UIControl* UIDlgBuilder::CreateControl(UIControl* v_ctrl,
                                       UIWindow* v_wnd,
                                       UIControl* v_parent/* = nullptr*/) {
    // Set basewnd
    v_ctrl->SetBaseWindow(v_wnd);
    // Attach to parent (parent must have container attribute)
    if (v_parent) {
        // must use dynamic_cast!
        IUIContainer* container = dynamic_cast<IUIContainer*>((UIControl*)v_parent->GetInterface(CTRLNAME_CONTAINER));
        if (!container)
            return nullptr;
        container->Add(v_ctrl);
        v_ctrl->SetParent(v_parent);
    }
    v_ctrl->BeforeSetAttribute();
    return v_ctrl;
}

void UIDlgBuilder::FinishCreateControl(UIControl * v_ctrl) {
    v_ctrl->AfterSetAttribute();
}

UIDialog* UIDlgBuilder::GetCtrlRoot() {
    return ctrl_root_;
}

UIControl* UIDlgBuilder::Parse(UIWindow* v_wnd, xmlnode v_root,
                                UIControl* v_parent/* = nullptr*/) {
    for (xmlnode node = v_root; node != nullptr;
         node = node->next_sibling()) {
        if (!v_parent && !CmpStr(node->name(), CTRLNAME_DIALOG)) {
            UISetError(kLL_Warning, kEC_CtrlFormatInvalid,
                       _T("Dialog control must be the root."));
            return nullptr;
        }
        LPCTSTR ctrl_name = node->name();
        size_t ctrl_namelen = _tcslen(ctrl_name);
        UIControl* new_ctrl = nullptr;
        // TODO: Add new Ctrl
        switch (ctrl_namelen) {
        case 3:
        {
            if (CmpStr(ctrl_name, CTRLNAME_DIALOG)) {
                if (v_parent) {
                    UISetError(kLL_Warning, kEC_CtrlFormatInvalid,
                               _T("Dialog control do not allow nesting."));
                    return nullptr;
                }
                new_ctrl = new UIDialog;
                ctrl_root_ = reinterpret_cast<UIDialog*>(new_ctrl);
            }
            if (CmpStr(ctrl_name, CTRLNAME_IMAGE))
                new_ctrl = new UIImage;
            if (CmpStr(ctrl_name, CTRLNAME_BUTTON))
                new_ctrl = new UIButton;
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
            UISetError(kLL_Warning, kEC_CtrlKindInvalid,
                       _T("Control Kind \"%s\" invalid"), ctrl_name);
            return nullptr;
        }

        CreateControl(new_ctrl, v_wnd, v_parent);
        // Process attributes
        for (xmlattr attr = node->first_attribute();
             attr != nullptr;
             attr = attr->next_attribute())
            new_ctrl->SetAttribute(attr->name(), attr->value());
        FinishCreateControl(new_ctrl);

        // Add children
        if (node->first_node())
            Parse(v_wnd, node->first_node(), new_ctrl);
    }
    return ctrl_root_;
}
}    // namespace DuiMini
