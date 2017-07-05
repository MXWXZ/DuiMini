/************************************************************************
Copyright (c) 2017 MXWXZ
XMLΩ‚Œˆ¿‡
************************************************************************/
#pragma once
#ifndef E__CODE_DUIMINI_DUIMINI_CORE_UIMARKUP_H_
#define E__CODE_DUIMINI_DUIMINI_CORE_UIMARKUP_H_

namespace DuiMini {
/*
enum XMLEncode{
    kXMLEncode_UTF8 = 0,
    kXMLEncode_UNICODE = 1,
    kXMLEncode_ASNI = 2,
};

class UIMarkup;
class UIMarkupNode;

class DUIMINI_API UIMarkup {
    friend class UIMarkupNode;
public:
    UIMarkup(LPCTSTR pstrXML = NULL);
    ~UIMarkup();

    bool Load(LPCTSTR pstrXML);
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, XMLEncode encoding = kXMLEncode_UTF8);
    bool LoadFromFile(LPCTSTR pstrFilename, XMLEncode encoding = kXMLEncode_UTF8);
    void Release();
    bool IsValid() const;

    void SetPreserveWhitespace(bool bPreserve = true);
    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
    
    UIMarkupNode GetRoot();

private:
    typedef struct tagXML_ELEMENT {
        ULONG start;
        ULONG child;
        ULONG next;
        ULONG parent;
        ULONG data;
    } XML_ELEMENT;

    LPTSTR strXML_;
    XML_ELEMENT* elements_;
    ULONG num_elements_;
    ULONG num_reservedelements_;
    TCHAR ErrorMsg_[100];
    TCHAR ErrorXML_[50];
    bool ispreservewhitespace_;

private:
    bool Parse();
    bool Parse(LPTSTR& pstrText, ULONG iParent);
    XML_ELEMENT* ReserveElement();
    inline void SkipWhitespace(LPTSTR& pstr) const;
    inline void SkipWhitespace(LPCTSTR& pstr) const;
    inline void SkipIdentifier(LPTSTR& pstr) const;
    inline void SkipIdentifier(LPCTSTR& pstr) const;
    bool ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);
    void ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);
    bool ParseAttributes(LPTSTR& pstrText);
    bool Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);
};


class DUIMINI_API UIMarkupNode {
    friend class UIMarkup;
public:
    UIMarkupNode();
    UIMarkupNode(UIMarkup* owner, int pos);

    bool IsValid() const;

    UIMarkupNode GetParent();
    UIMarkupNode GetSibling();
    UIMarkupNode GetChild();
    UIMarkupNode GetChild(LPCTSTR name);

    bool HasSiblings() const;
    bool HasChildren() const;
    LPCTSTR GetName() const;
    LPCTSTR GetValue() const;

    bool HasAttributes();
    bool HasAttribute(LPCTSTR name);
    int GetAttributeCount();
    LPCTSTR GetAttributeName(int index);
    LPCTSTR GetAttributeValue(int index);
    LPCTSTR GetAttributeValue(LPCTSTR name);
    bool GetAttributeValue(int index, LPTSTR value, SIZE_T chmax);
    bool GetAttributeValue(LPCTSTR name, LPTSTR value, SIZE_T chmax);

private:
    void MapAttributes();

    typedef struct {
        ULONG name;
        ULONG value;
    } XML_ATTRIBUTE;

    int pos_;
    int num_attributes_;
    XML_ATTRIBUTE attributes_[kMax_XML_Attributes];
    UIMarkup* owner_;
};
*/
}   // namespace DuiMini

#endif  // E__CODE_DUIMINI_DUIMINI_CORE_UIMARKUP_H_
