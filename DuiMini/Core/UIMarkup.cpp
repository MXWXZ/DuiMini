/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIMarkup.h"

namespace DuiMini {
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*
UIMarkupNode::UIMarkupNode() : owner_(NULL) {
}

UIMarkupNode::UIMarkupNode(UIMarkup* owner, int pos) : owner_(owner), pos_(pos), num_attributes_(0) {
}

UIMarkupNode UIMarkupNode::GetSibling() {
    if (owner_ == NULL) return UIMarkupNode();
    ULONG pos = owner_->elements_[pos_].next;
    if (pos == 0) return UIMarkupNode();
    return UIMarkupNode(owner_, pos);
}

bool UIMarkupNode::HasSiblings() const {
    if (owner_ == NULL) return false;
    ULONG pos = owner_->elements_[pos_].next;
    return pos > 0;
}

UIMarkupNode UIMarkupNode::GetChild() {
    if (owner_ == NULL) return UIMarkupNode();
    ULONG pos = owner_->elements_[pos_].child;
    if (pos == 0) return UIMarkupNode();
    return UIMarkupNode(owner_, pos);
}

UIMarkupNode UIMarkupNode::GetChild(LPCTSTR name) {
    if (owner_ == NULL) return UIMarkupNode();
    ULONG pos = owner_->elements_[pos_].child;
    while (pos != 0) {
        if (_tcscmp(owner_->strXML_ + owner_->elements_[pos].start, name) == 0) {
            return UIMarkupNode(owner_, pos);
        }
        pos = owner_->elements_[pos].next;
    }
    return UIMarkupNode();
}

bool UIMarkupNode::HasChildren() const {
    if (owner_ == NULL) return false;
    return owner_->elements_[pos_].child != 0;
}

UIMarkupNode UIMarkupNode::GetParent() {
    if (owner_ == NULL) return UIMarkupNode();
    ULONG pos = owner_->elements_[pos_].parent;
    if (pos == 0) return UIMarkupNode();
    return UIMarkupNode(owner_, pos);
}

bool UIMarkupNode::IsValid() const {
    return owner_ != NULL;
}

LPCTSTR UIMarkupNode::GetName() const {
    if (owner_ == NULL) return NULL;
    return owner_->strXML_ + owner_->elements_[pos_].start;
}

LPCTSTR UIMarkupNode::GetValue() const {
    if (owner_ == NULL) return NULL;
    return owner_->strXML_ + owner_->elements_[pos_].data;
}

LPCTSTR UIMarkupNode::GetAttributeName(int index) {
    if (owner_ == NULL) return NULL;
    if (num_attributes_ == 0) MapAttributes();
    if (index < 0 || index >= num_attributes_) return _T("");
    return owner_->strXML_ + attributes_[index].name;
}

LPCTSTR UIMarkupNode::GetAttributeValue(int index) {
    if (owner_ == NULL) return NULL;
    if (num_attributes_ == 0) MapAttributes();
    if (index < 0 || index >= num_attributes_) return _T("");
    return owner_->strXML_ + attributes_[index].value;
}

LPCTSTR UIMarkupNode::GetAttributeValue(LPCTSTR name) {
    if (owner_ == NULL) return NULL;
    if (num_attributes_ == 0) MapAttributes();
    for (int i = 0; i < num_attributes_; i++) {
        if (_tcscmp(owner_->strXML_ + attributes_[i].name, name) == 0) 
            return owner_->strXML_ + attributes_[i].value;
    }
    return _T("");
}

bool UIMarkupNode::GetAttributeValue(int index, LPTSTR value, SIZE_T chmax) {
    if (owner_ == NULL) return false;
    if (num_attributes_ == 0) MapAttributes();
    if (index < 0 || index >= num_attributes_) return false;
    _tcsncpy(value, owner_->strXML_ + attributes_[index].value, chmax);
    return true;
}

bool UIMarkupNode::GetAttributeValue(LPCTSTR name, LPTSTR value, SIZE_T chmax) {
    if (owner_ == NULL) return false;
    if (num_attributes_ == 0) MapAttributes();
    for (int i = 0; i < num_attributes_; i++) {
        if (_tcscmp(owner_->strXML_ + attributes_[i].name, name) == 0) {
            _tcsncpy(value, owner_->strXML_ + attributes_[i].value, chmax);
            return true;
        }
    }
    return false;
}

int UIMarkupNode::GetAttributeCount() {
    if (owner_ == NULL) return 0;
    if (num_attributes_ == 0) MapAttributes();
    return num_attributes_;
}

bool UIMarkupNode::HasAttributes() {
    if (owner_ == NULL) return false;
    if (num_attributes_ == 0) MapAttributes();
    return num_attributes_ > 0;
}

bool UIMarkupNode::HasAttribute(LPCTSTR name) {
    if (owner_ == NULL) return false;
    if (num_attributes_ == 0) MapAttributes();
    for (int i = 0; i < num_attributes_; i++) {
        if (_tcscmp(owner_->strXML_ + attributes_[i].name, name) == 0) return true;
    }
    return false;
}

void UIMarkupNode::MapAttributes() {
    num_attributes_ = 0;
    LPCTSTR str = owner_->strXML_ + owner_->elements_[pos_].start;
    LPCTSTR strend = owner_->strXML_ + owner_->elements_[pos_].data;
    str += _tcslen(str) + 1;
    while (str < strend) {
        owner_->SkipWhitespace(str);
        attributes_[num_attributes_].name = str - owner_->strXML_;
        str += _tcslen(str) + 1;
        owner_->SkipWhitespace(str);
        if (*str++ != _T('\"')) return;

        attributes_[num_attributes_++].value = str - owner_->strXML_;
        if (num_attributes_ >= kMax_XML_Attributes) return;
        str += _tcslen(str) + 1;
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

UIMarkup::UIMarkup(LPCTSTR strXML) {
    strXML_ = NULL;
    elements_ = NULL;
    num_elements_ = 0;
    ispreservewhitespace_ = true;
    if (strXML != NULL) Load(strXML);
}

UIMarkup::~UIMarkup() {
    Release();
}

bool UIMarkup::IsValid() const {
    return elements_ != NULL;
}

void UIMarkup::SetPreserveWhitespace(bool ispreserve) {
    ispreservewhitespace_ = ispreserve;
}

bool UIMarkup::Load(LPCTSTR strXML) {
    Release();
    SIZE_T chlen = _tcslen(strXML) + 1;
    strXML_ = static_cast<LPTSTR>(malloc(chlen * sizeof(TCHAR)));
    CopyMemory(strXML_, strXML, chlen * sizeof(TCHAR));
    bool res = Parse();
    if (!res) Release();
    return res;
}

bool UIMarkup::LoadFromMem(BYTE* byte, DWORD size, XMLEncode encoding /*= kXMLEncode_UTF8) {
#ifdef _UNICODE
    if (encoding == kXMLEncode_UTF8) {
        if (size >= 3 && byte[0] == 0xEF && byte[1] == 0xBB && byte[2] == 0xBF) {
            byte += 3; size -= 3;
        }
        DWORD wide = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)byte, size, NULL, 0);

        strXML_ = static_cast<LPTSTR>(malloc((wide + 1) * sizeof(TCHAR)));
        MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)byte, size, strXML_, wide);
        strXML_[wide] = _T('\0');
    } else if (encoding == kXMLEncode_ASNI) {
        DWORD wide = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)byte, size, NULL, 0);

        strXML_ = static_cast<LPTSTR>(malloc((wide + 1) * sizeof(TCHAR)));
        MultiByteToWideChar(CP_ACP, 0, (LPCSTR)byte, size, strXML_, wide);
        strXML_[wide] = _T('\0');
    } else {
        if (size >= 2 && ((byte[0] == 0xFE && byte[1] == 0xFF) || (byte[0] == 0xFF && byte[1] == 0xFE))) {
            size = size / 2 - 1;

            if (byte[0] == 0xFE && byte[1] == 0xFF) {
                byte += 2;

                for (DWORD swap = 0; swap < size; swap++) {
                    register CHAR tmp = byte[(swap << 1) + 0];
                    byte[(swap << 1) + 0] = byte[(swap << 1) + 1];
                    byte[(swap << 1) + 1] = tmp;
                }
            } else {
                byte += 2;
            }

            strXML_ = static_cast<LPTSTR>(malloc((size + 1) * sizeof(TCHAR)));
            CopyMemory(strXML_, byte, size * sizeof(TCHAR));
            strXML_[size] = _T('\0');

            byte -= 2;
        }
    }
#else // !_UNICODE
    if (encoding == kXMLEncode_UTF8) {
        if (size >= 3 && byte[0] == 0xEF && byte[1] == 0xBB && byte[2] == 0xBF) {
            byte += 3; size -= 3;
        }
        DWORD wide = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)byte, size, NULL, 0);

        LPWSTR w_str = static_cast<LPWSTR>(malloc((wide + 1) * sizeof(WCHAR)));
        MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)byte, size, w_str, wide);
        w_str[wide] = L'\0';

        DWORD wide = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)w_str, wide, NULL, 0, NULL, NULL);

        strXML_ = static_cast<LPTSTR>(malloc((wide + 1) * sizeof(TCHAR)));
        WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)w_str, wide, strXML_, wide, NULL, NULL);
        strXML_[wide] = _T('\0');

        free(w_str);
    } else if (encoding == kXMLEncode_UNICODE) {
        if (size >= 2 && ((byte[0] == 0xFE && byte[1] == 0xFF) || (byte[0] == 0xFF && byte[1] == 0xFE))) {
            size = size / 2 - 1;

            if (byte[0] == 0xFE && byte[1] == 0xFF) {
                byte += 2;

                for (DWORD swap = 0; swap < size; swap++) {
                    register CHAR tmp = byte[(swap << 1) + 0];
                    byte[(swap << 1) + 0] = byte[(swap << 1) + 1];
                    byte[(swap << 1) + 1] = tmp;
                }
            } else {
                byte += 2;
            }

            DWORD wide = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)byte, size, NULL, 0, NULL, NULL);
            strXML_ = static_cast<LPTSTR>(malloc((wide + 1) * sizeof(TCHAR)));
            WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)byte, size, strXML_, wide, NULL, NULL);
            strXML_[wide] = _T('\0');

            byte -= 2;
        }
    } else {
        strXML_ = static_cast<LPTSTR>(malloc((size + 1) * sizeof(TCHAR)));
        CopyMemory(strXML_, byte, size * sizeof(TCHAR));
        strXML_[size] = _T('\0');
    }
#endif // _UNICODE

    bool res = Parse();
    if (!res) Release();
    return res;
}

bool UIMarkup::LoadFromFile(LPCTSTR filename, XMLEncode encoding /*= kXMLEncode_UTF8) {
    Release();
    CDuiString sFile = CPaintManagerUI::GetResourcePath();
    if (CPaintManagerUI::GetResourceZip().IsEmpty()) {
        sFile += filename;
        HANDLE hFile = ::CreateFile(sFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) return Failed(_T("Error opening file"));
        DWORD dwSize = ::GetFileSize(hFile, NULL);
        if (dwSize == 0) return Failed(_T("File is empty"));
        if (dwSize > 4096 * 1024) return Failed(_T("File too large"));

        DWORD dwRead = 0;
        BYTE* pByte = new BYTE[dwSize];
        ::ReadFile(hFile, pByte, dwSize, &dwRead, NULL);
        ::CloseHandle(hFile);

        if (dwRead != dwSize) {
            delete[] pByte;
            Release();
            return Failed(_T("Could not read file"));
        }
        bool ret = LoadFromMem(pByte, dwSize, encoding);
        delete[] pByte;

        return ret;
    } else {
        sFile += CPaintManagerUI::GetResourceZip();
        HZIP hz = NULL;
        if (CPaintManagerUI::IsCachedResourceZip()) hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
        else hz = OpenZip((void*)sFile.GetData(), 0, 2);
        if (hz == NULL) return Failed(_T("Error opening zip file"));
        ZIPENTRY ze;
        int i;
        if (FindZipItem(hz, filename, true, &i, &ze) != 0) return Failed(_T("Could not find ziped file"));
        DWORD dwSize = ze.unc_size;
        if (dwSize == 0) return Failed(_T("File is empty"));
        if (dwSize > 4096 * 1024) return Failed(_T("File too large"));
        BYTE* pByte = new BYTE[dwSize];
        int res = UnzipItem(hz, i, pByte, dwSize, 3);
        if (res != 0x00000000 && res != 0x00000600) {
            delete[] pByte;
            if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);
            return Failed(_T("Could not unzip file"));
        }
        if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);
        bool ret = LoadFromMem(pByte, dwSize, encoding);
        delete[] pByte;

        return ret;
    }
}

void UIMarkup::Release() {
    if (strXML_ != NULL) free(strXML_);
    if (elements_ != NULL) free(elements_);
    strXML_ = NULL;
    elements_ = NULL;
    num_elements_;
}

void UIMarkup::GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const {
    _tcsncpy(pstrMessage, ErrorMsg_, cchMax);
}

void UIMarkup::GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const {
    _tcsncpy(pstrSource, ErrorXML_, cchMax);
}

UIMarkupNode UIMarkup::GetRoot() {
    if (num_elements_ == 0) return UIMarkupNode();
    return UIMarkupNode(this, 1);
}

bool UIMarkup::Parse() {
    ReserveElement(); // Reserve index 0 for errors
    ::ZeroMemory(ErrorMsg_, sizeof(ErrorMsg_));
    ::ZeroMemory(ErrorXML_, sizeof(ErrorXML_));
    LPTSTR pstrXML = strXML_;
    return Parse(pstrXML, 0);
}

bool UIMarkup::Parse(LPTSTR& pstrText, ULONG iParent) {
    SkipWhitespace(pstrText);
    ULONG iPrevious = 0;
    for (; ; ) {
        if (*pstrText == _T('\0') && iParent <= 1) return true;
        SkipWhitespace(pstrText);
        if (*pstrText != _T('<')) return Failed(_T("Expected start tag"), pstrText);
        if (pstrText[1] == _T('/')) return true;
        *pstrText++ = _T('\0');
        SkipWhitespace(pstrText);
        // Skip comment or processing directive
        if (*pstrText == _T('!') || *pstrText == _T('?')) {
            TCHAR ch = *pstrText;
            if (*pstrText == _T('!')) ch = _T('-');
            while (*pstrText != _T('\0') && !(*pstrText == ch && *(pstrText + 1) == _T('>'))) pstrText = ::CharNext(pstrText);
            if (*pstrText != _T('\0')) pstrText += 2;
            SkipWhitespace(pstrText);
            continue;
        }
        SkipWhitespace(pstrText);
        // Fill out element structure
        XML_ELEMENT* pEl = ReserveElement();
        ULONG iPos = pEl - elements_;
        pEl->start = pstrText - strXML_;
        pEl->parent = iParent;
        pEl->next = pEl->child = 0;
        if (iPrevious != 0) elements_[iPrevious].next = iPos;
        else if (iParent > 0) elements_[iParent].child = iPos;
        iPrevious = iPos;
        // Parse name
        LPCTSTR pstrName = pstrText;
        SkipIdentifier(pstrText);
        LPTSTR pstrNameEnd = pstrText;
        if (*pstrText == _T('\0')) return Failed(_T("Error parsing element name"), pstrText);
        // Parse attributes
        if (!ParseAttributes(pstrText)) return false;
        SkipWhitespace(pstrText);
        if (pstrText[0] == _T('/') && pstrText[1] == _T('>')) {
            pEl->data = pstrText - strXML_;
            *pstrText = _T('\0');
            pstrText += 2;
        } else {
            if (*pstrText != _T('>')) return Failed(_T("Expected start-tag closing"), pstrText);
            // Parse node data
            pEl->data = ++pstrText - strXML_;
            LPTSTR pstrDest = pstrText;
            if (!ParseData(pstrText, pstrDest, _T('<'))) return false;
            // Determine type of next element
            if (*pstrText == _T('\0') && iParent <= 1) return true;
            if (*pstrText != _T('<')) return Failed(_T("Expected end-tag start"), pstrText);
            if (pstrText[0] == _T('<') && pstrText[1] != _T('/')) {
                if (!Parse(pstrText, iPos)) return false;
            }
            if (pstrText[0] == _T('<') && pstrText[1] == _T('/')) {
                *pstrDest = _T('\0');
                *pstrText = _T('\0');
                pstrText += 2;
                SkipWhitespace(pstrText);
                SIZE_T cchName = pstrNameEnd - pstrName;
                if (_tcsncmp(pstrText, pstrName, cchName) != 0) return Failed(_T("Unmatched closing tag"), pstrText);
                pstrText += cchName;
                SkipWhitespace(pstrText);
                if (*pstrText++ != _T('>')) return Failed(_T("Unmatched closing tag"), pstrText);
            }
        }
        *pstrNameEnd = _T('\0');
        SkipWhitespace(pstrText);
    }
}

UIMarkup::XML_ELEMENT* UIMarkup::ReserveElement() {
    if (num_elements_ == 0) num_reservedelements_ = 0;
    if (num_elements_ >= num_reservedelements_) {
        num_reservedelements_ += (num_reservedelements_ / 2) + 500;
        elements_ = static_cast<XML_ELEMENT*>(realloc(elements_, num_reservedelements_ * sizeof(XML_ELEMENT)));
    }
    return &elements_[num_elements_++];
}

void UIMarkup::SkipWhitespace(LPCTSTR& pstr) const {
    while (*pstr > _T('\0') && *pstr <= _T(' ')) pstr = ::CharNext(pstr);
}

void UIMarkup::SkipWhitespace(LPTSTR& pstr) const {
    while (*pstr > _T('\0') && *pstr <= _T(' ')) pstr = ::CharNext(pstr);
}

void UIMarkup::SkipIdentifier(LPCTSTR& pstr) const {
    // 属性只能用英文，所以这样处理没有问题
    while (*pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr))) pstr = ::CharNext(pstr);
}

void UIMarkup::SkipIdentifier(LPTSTR& pstr) const {
    // 属性只能用英文，所以这样处理没有问题
    while (*pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr))) pstr = ::CharNext(pstr);
}

bool UIMarkup::ParseAttributes(LPTSTR& pstrText) {
    if (*pstrText == _T('>')) return true;
    *pstrText++ = _T('\0');
    SkipWhitespace(pstrText);
    while (*pstrText != _T('\0') && *pstrText != _T('>') && *pstrText != _T('/')) {
        SkipIdentifier(pstrText);
        LPTSTR pstrIdentifierEnd = pstrText;
        SkipWhitespace(pstrText);
        if (*pstrText != _T('=')) return Failed(_T("Error while parsing attributes"), pstrText);
        *pstrText++ = _T(' ');
        *pstrIdentifierEnd = _T('\0');
        SkipWhitespace(pstrText);
        if (*pstrText++ != _T('\"')) return Failed(_T("Expected attribute value"), pstrText);
        LPTSTR pstrDest = pstrText;
        if (!ParseData(pstrText, pstrDest, _T('\"'))) return false;
        if (*pstrText == _T('\0')) return Failed(_T("Error while parsing attribute string"), pstrText);
        *pstrDest = _T('\0');
        if (pstrText != pstrDest) *pstrText = _T(' ');
        pstrText++;
        SkipWhitespace(pstrText);
    }
    return true;
}

bool UIMarkup::ParseData(LPTSTR& pstrText, LPTSTR& pstrDest, char cEnd) {
    while (*pstrText != _T('\0') && *pstrText != cEnd) {
        if (*pstrText == _T('&')) {
            while (*pstrText == _T('&')) {
                ParseMetaChar(++pstrText, pstrDest);
            }
            if (*pstrText == cEnd)
                break;
        }

        if (*pstrText == _T(' ')) {
            *pstrDest++ = *pstrText++;
            if (!ispreservewhitespace_) SkipWhitespace(pstrText);
        } else {
            LPTSTR pstrTemp = ::CharNext(pstrText);
            while (pstrText < pstrTemp) {
                *pstrDest++ = *pstrText++;
            }
        }
    }
    // Make sure that MapAttributes() works correctly when it parses
    // over a value that has been transformed.
    LPTSTR pstrFill = pstrDest + 1;
    while (pstrFill < pstrText) *pstrFill++ = _T(' ');
    return true;
}

void UIMarkup::ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest) {
    if (pstrText[0] == _T('a') && pstrText[1] == _T('m') && pstrText[2] == _T('p') && pstrText[3] == _T(';')) {
        *pstrDest++ = _T('&');
        pstrText += 4;
    } else if (pstrText[0] == _T('l') && pstrText[1] == _T('t') && pstrText[2] == _T(';')) {
        *pstrDest++ = _T('<');
        pstrText += 3;
    } else if (pstrText[0] == _T('g') && pstrText[1] == _T('t') && pstrText[2] == _T(';')) {
        *pstrDest++ = _T('>');
        pstrText += 3;
    } else if (pstrText[0] == _T('q') && pstrText[1] == _T('u') && pstrText[2] == _T('o') && pstrText[3] == _T('t') && pstrText[4] == _T(';')) {
        *pstrDest++ = _T('\"');
        pstrText += 5;
    } else if (pstrText[0] == _T('a') && pstrText[1] == _T('p') && pstrText[2] == _T('o') && pstrText[3] == _T('s') && pstrText[4] == _T(';')) {
        *pstrDest++ = _T('\'');
        pstrText += 5;
    } else {
        *pstrDest++ = _T('&');
    }
}

bool UIMarkup::Failed(LPCTSTR pstrError, LPCTSTR pstrLocation) {
    // Register last error
    TRACE(_T("XML Error: %s"), pstrError);
    if (pstrLocation != NULL) TRACE(pstrLocation);
    _tcsncpy(ErrorMsg_, pstrError, (sizeof(ErrorMsg_) / sizeof(ErrorMsg_[0])) - 1);
    _tcsncpy(ErrorXML_, pstrLocation != NULL ? pstrLocation : _T(""), lengthof(ErrorXML_) - 1);
    return false; // Always return 'false'
}
*/
}   // namespace DuiMini
