/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/28
 */
#include "stdafx.h"
#include "UIXmlLoader.h"

namespace DuiMini {
UIXmlNode::UIXmlNode() {}

UIXmlNode::UIXmlNode(const xmlnode v_node) {
    SetNode(v_node);
}

UIXmlNode::~UIXmlNode() {}

void UIXmlNode::SetNode(const xmlnode v_node) {
    node_ = v_node;
}

CUStr UIXmlNode::GetAttrValue(LPCTSTR v_name,
                              LPCTSTR v_default/* = _T("")*/) const {
    xmlattr attr = node_.attribute(v_name);
    return CUStr(attr ? attr.value() : v_default);
}

CUStr UIXmlNode::GetAttrValue(LPCTSTR v_name,
                              const int v_default) const {
    return GetAttrValue(v_name, UStr(v_default));
}

bool UIXmlNode::CmpAttrValue(LPCTSTR v_name, LPCTSTR value) const {
    return GetAttrValue(v_name) == value;
}

bool UIXmlNode::CmpNodeName(LPCTSTR v_name) const {
    return CmpStr(node_.name(), v_name);
}

UIXmlNode::operator bool() const {
    return node_;
}

CUStr UIXmlNode::GetName() const {
    return node_.name();
}

UIXmlNode UIXmlNode::NextSibling() const {
    return UIXmlNode(node_.next_sibling());
}

UIXmlAttr UIXmlNode::FirstAttribute() const {
    return UIXmlAttr(node_.first_attribute());
}

UIXmlNode UIXmlNode::FirstChild() const {
    return UIXmlNode(node_.first_child());
}

////////////////////////////////////////

UIXmlLoader::UIXmlLoader() {}

UIXmlLoader::UIXmlLoader(LPCTSTR v_path) {
    Loadxml(v_path);
}

UIXmlLoader::~UIXmlLoader() {}

void UIXmlLoader::Loadxml(LPCTSTR v_path) {
    FILESIZE buflen = UIResource::GetFileSize(v_path);
    auto buffer = UIUtils::SafeBYTE(buflen + 1);
    UIResource::GetFile(v_path, buffer.get(), buflen);
    buffer[buflen] = '\0';
    doc_.load_buffer(buffer.get(), buflen);
}

UIXmlNode UIXmlLoader::GetRoot() const {
    return UIXmlNode(doc_.first_child());
}

////////////////////////////////////////

UIXmlAttr::UIXmlAttr() {}

UIXmlAttr::UIXmlAttr(const xmlattr v_attr) {
    SetAttr(v_attr);
}

UIXmlAttr::~UIXmlAttr() {}

UIXmlAttr::operator bool() const {
    return attr_;
}

void UIXmlAttr::SetAttr(const xmlattr v_attr) {
    attr_ = v_attr;
}

UIXmlAttr UIXmlAttr::NextAttribute() const {
    return UIXmlAttr(attr_.next_attribute());
}

CUStr UIXmlAttr::GetName() const {
    return CUStr(attr_.name());
}

CUStr UIXmlAttr::GetValue() const {
    return CUStr(attr_.value());
}
}   // namespace DuiMini
