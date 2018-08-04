/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#include "stdafx.h"
#include "UIDlgBuilder.h"

namespace DuiMini {
UIDlgBuilder::UIDlgBuilder() {}

UIDlgBuilder::~UIDlgBuilder() {
    Release();
}

UIControl* UIDlgBuilder::Init(UIXmlNode v_root, UIWindow* v_wnd) {
    xml_root_ = v_root;
    return Parse(v_wnd, xml_root_);
}

void UIDlgBuilder::Release() {}

UIControl* UIDlgBuilder::CreateControl(UIControl* v_ctrl,
                                       UIWindow* v_wnd,
                                       UIControl* v_parent/* = nullptr*/) {
    assert(v_ctrl && v_wnd);
    // Set basewnd
    v_ctrl->SetBaseWindow(v_wnd);
    // Attach to parent (parent must have container attribute)
    if (v_parent) {
        // must use dynamic_cast!
        IUIContainer* container = dynamic_cast<IUIContainer*>((UIControl*)v_parent->GetInterface(CTRLNAME_CONTAINER));
        if (container) {
            container->Add(v_ctrl);
            v_ctrl->SetParent(v_parent);
        }
    }
    v_ctrl->BeforeSetAttribute();
    return v_ctrl;
}

bool UIDlgBuilder::FinishCreateControl(UIControl * v_ctrl) {
    assert(v_ctrl);
    v_ctrl->AfterSetAttribute();
    return true;
}

UIDialog* UIDlgBuilder::GetCtrlRoot() {
    return ctrl_root_.get();
}

UIControl* UIDlgBuilder::Parse(UIWindow* v_wnd, UIXmlNode v_root,
                                UIControl* v_parent/* = nullptr*/) {
    for (UIXmlNode node = v_root; node;node = node.NextSibling()) {
        if (!v_parent && node.GetName() != CTRLNAME_DIALOG) {
            ErrorMsg_FormatInvalid(_T("Dialog control (must be the root)"));
            return nullptr;
        }
        UStr ctrl_name = node.GetName();
        size_t ctrl_namelen = ctrl_name.GetLength();
        UIControl* new_ctrl = nullptr;
        // TODO: Add new Ctrl
        switch (ctrl_namelen) {
        case 3:
        {
            if (ctrl_name == CTRLNAME_DIALOG) {
                if (v_parent) {
                    ErrorMsg_FormatInvalid(_T("Dialog control (do not allow nesting)"));
                    return nullptr;
                }
                new_ctrl = new UIDialog;
                ctrl_root_.reset((UIDialog*)new_ctrl);
            }
            if (ctrl_name == CTRLNAME_IMAGE)
                new_ctrl = new UIImage;
            if (ctrl_name == CTRLNAME_BUTTON)
                new_ctrl = new UIButton;
            if (ctrl_name == CTRLNAME_TEXT)
                new_ctrl = new UIText;
            break;
        }
        case 9:
        {
            if (ctrl_name == CTRLNAME_CONTAINER)
                new_ctrl = new UIContainer;

            break;
        }
        }
        // Invalid ctrl name
        if (!new_ctrl) {
            ErrorMsg_FormatInvalid(ctrl_name.GetData());
            return nullptr;
        }

        CreateControl(new_ctrl, v_wnd, v_parent);
        // Process attributes
        for (UIXmlAttr attr = node.FirstAttribute(); attr;
             attr = attr.NextAttribute())
            new_ctrl->SetAttribute(attr.GetName(), attr.GetValue());
        FinishCreateControl(new_ctrl);

        // Add children
        if (node.FirstChild())
            Parse(v_wnd, node.FirstChild(), new_ctrl);
    }
    return ctrl_root_.get();
}
}    // namespace DuiMini
