/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/28
 */
#pragma once
#include "thirdpart/pugixml/pugixml.hpp"      // pugixml 1.8.1
typedef pugi::xml_document xmldoc;
typedef pugi::xml_node xmlnode;
typedef pugi::xml_attribute xmlattr;

namespace DuiMini {
class DUIMINI_API UIXmlAttr {
public:
    UIXmlAttr();
    explicit UIXmlAttr(const xmlattr v_attr);
    ~UIXmlAttr();

    operator bool() const;
    void SetAttr(const xmlattr v_attr);
    UIXmlAttr NextAttribute() const;
    CUStr GetName() const;
    CUStr GetValue() const;

private:
    xmlattr attr_;
};

class DUIMINI_API UIXmlNode {
public:
    UIXmlNode();
    explicit UIXmlNode(const xmlnode v_node);
    ~UIXmlNode();

public:
    void SetNode(const xmlnode v_node);
    CUStr GetAttrValue(LPCTSTR v_name, LPCTSTR v_default = _T("")) const;
    CUStr GetAttrValue(LPCTSTR v_name, const int v_default) const;
    bool CmpAttrValue(LPCTSTR v_name, LPCTSTR v_value) const;
    bool CmpNodeName(LPCTSTR v_name) const;

    operator bool() const;
    CUStr GetName() const;
    UIXmlNode NextSibling() const;
    UIXmlAttr FirstAttribute() const;
    UIXmlNode FirstChild() const;

private:
    xmlnode node_;
};


class DUIMINI_API UIXmlLoader {
public:
    UIXmlLoader();
    explicit UIXmlLoader(LPCTSTR v_path);
    ~UIXmlLoader();

    void Loadxml(LPCTSTR v_path);
    UIXmlNode GetRoot() const;

private:
    xmldoc doc_;
};

}   // namespace DuiMini
