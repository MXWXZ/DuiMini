/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/10
 */
#ifndef DUI_UTILS_UIXMLPARSE_HPP_
#define DUI_UTILS_UIXMLPARSE_HPP_

#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include <pugixml/pugixml.hpp>
typedef pugi::xml_document xmldoc;
typedef pugi::xml_node xmlnode;
typedef pugi::xml_attribute xmlattr;

namespace DuiMini {
/**
 * xml attribute wrapper class using pugixml
 */
class DUIMINI_API UIXmlAttr {
public:
    UIXmlAttr() {}
    UIXmlAttr(xmlattr attr) { SetAttr(attr); }
    ~UIXmlAttr() {}

    operator bool() const { return attr_; }

    void SetAttr(xmlattr attr) { attr_ = attr; }

    UIXmlAttr NextAttribute() const {
        return UIXmlAttr(attr_.next_attribute());
    }

    UIStr GetName() const { return UIStr(attr_.name()); }
    UIStr GetValue() const { return UIStr(attr_.value()); }

private:
    xmlattr attr_;
};

////////////////////////////////////////

/**
 * xml node wrapper class using pugixml
 */
class DUIMINI_API UIXmlNode {
public:
    UIXmlNode() {}
    UIXmlNode(xmlnode node) { SetNode(node); }
    ~UIXmlNode() {}

public:
    void SetNode(xmlnode node) { node_ = node; }

    UIStr GetAttrValue(const char* name, const char* def = "") const {
        xmlattr attr = node_.attribute(name);
        return UIStr(attr ? attr.value() : def);
    }

    UIStr GetAttrValue(const char* name, int def) const {
        return GetAttrValue(name, std::to_string(def).c_str());
    }

    bool CmpAttrValue(const char* name, const char* value) const {
        return GetAttrValue(name) == value;
    }

    bool CmpNodeName(const char* name) const {
        return CMPSTR(node_.name(), name);
    }

    operator bool() const { return node_; }
    UIStr GetName() const { return node_.name(); }
    UIXmlNode NextSibling() const { return UIXmlNode(node_.next_sibling()); }
    UIXmlAttr FirstAttribute() const {
        return UIXmlAttr(node_.first_attribute());
    }
    UIXmlNode FirstChild() const { return UIXmlNode(node_.first_child()); }

private:
    xmlnode node_;
};

}  // namespace DuiMini

#endif  // !DUI_UTILS_UIXMLPARSE_HPP_
