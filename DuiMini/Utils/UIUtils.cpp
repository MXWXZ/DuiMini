/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIUtils.h"

namespace DuiMini {
CUStr UIUtils::GetCurrentDir() {
    TCHAR path[MAX_PATH] = { _T('\0') };
    GetCurrentDirectory(MAX_PATH, path);
    return CUStr(path);
}

CUStr UIUtils::GetTimeStr(LPCTSTR v_str) {
    time_t tm;
    time(&tm);
    TCHAR tmpstr[64];
    _tcsftime(tmpstr, sizeof(tmpstr), v_str, localtime(&tm));
    return CUStr(tmpstr);
}

////////////////////////////////////////

UIAttr::UIAttr() {}

UIAttr::~UIAttr() {}

UStr& UIAttr::operator[](CUStr v_name) {
    return attribute_[v_name];
}

CUStr UIAttr::GetValue(LPCTSTR v_name) const {
    SSMapCIt it = attribute_.find(v_name);
    if (it != attribute_.end())
        return it->second;
    else
        return UStr();
}

SSMapIt UIAttr::GetBegin() {
    return attribute_.begin();
}

SSMapIt UIAttr::GetEnd() {
    return attribute_.end();
}

UIAttrSet::UIAttrSet() {}

UIAttrSet::~UIAttrSet() {}

UIAttr& UIAttrSet::operator[] (const int v_pos) {
    return attribute_set_[v_pos];
}

CUIAttr UIAttrSet::GetValue(const int v_pos) {
    if (v_pos >= size_)
        return UIAttr();
    return attribute_set_[v_pos];
}

void UIAttrSet::AddAttr(const UIAttr &v_value) {
    attribute_set_[size_++] = v_value;
}

int UIAttrSet::GetSize() const {
    return size_;
}

void UIAttrSet::Clear() {
    attribute_set_.clear();
    size_ = 0;
}

int UIAttrSet::FindNextAttr(int v_start, LPCTSTR v_attr,
                            LPCTSTR v_value/* = _T("")*/) {
    for (int i = v_start; i < size_; ++i)
        if (!attribute_set_[i].GetValue(v_attr).IsEmpty())
            if (CmpStr(v_value, _T("")) || attribute_set_[i][v_attr] == v_value)
                return i;
    return -1;
}

////////////////////////////////////////

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
    xmlattr attr = node_->first_attribute(v_name);
    if (!attr)
        return CUStr(v_default);
    else
        return CUStr(attr->value());
}

CUStr DuiMini::UIXmlNode::GetAttrValue(LPCTSTR v_name,
                                       const int v_default) const {
    return GetAttrValue(v_name, CUStr(v_default));
}

bool UIXmlNode::CmpAttrValue(LPCTSTR v_name, LPCTSTR value) const {
    return GetAttrValue(v_name) == value;
}

bool UIXmlNode::CmpNodeName(LPCTSTR v_name) const {
    return CmpStr(node_->name(), v_name);
}

////////////////////////////////////////

UIPtrArray::UIPtrArray(UINT v_size) {
    allocated_ = v_size;
    ptrvoid_ = reinterpret_cast<LPVOID*>(malloc(v_size * sizeof(LPVOID)));
    ZeroMemory(ptrvoid_, v_size * sizeof(LPVOID));
}

UIPtrArray::~UIPtrArray() {
    if (ptrvoid_ != nullptr)
        free(ptrvoid_);
}

void UIPtrArray::Empty() {
    if (ptrvoid_ != nullptr)
        free(ptrvoid_);
    ptrvoid_ = nullptr;
    count_ = allocated_ = 0;
}

void UIPtrArray::Resize(UINT v_size) {
    Empty();
    ptrvoid_ = reinterpret_cast<LPVOID*>(malloc(v_size * sizeof(LPVOID)));
    ZeroMemory(ptrvoid_, v_size * sizeof(LPVOID));
    allocated_ = v_size;
    count_ = v_size;
}

bool UIPtrArray::IsEmpty() const {
    return count_ == 0;
}

bool UIPtrArray::Add(LPVOID v_data) {
    if (++count_ >= allocated_) {
        allocated_ *= 2;
        if (allocated_ == 0)
            allocated_ = 11;
        ptrvoid_ = reinterpret_cast<LPVOID*>(realloc(ptrvoid_,
                                                allocated_ * sizeof(LPVOID)));
        if (!ptrvoid_)
            return false;
    }
    ptrvoid_[count_ - 1] = v_data;
    return true;
}

bool UIPtrArray::InsertAt(UINT v_index, LPVOID v_data) {
    if (v_index == count_)
        return Add(v_data);
    if (v_index < 0 || v_index > count_)
        return false;
    if (++count_ >= allocated_) {
        allocated_ *= 2;
        if (allocated_ == 0)
            allocated_ = 11;
        ptrvoid_ = reinterpret_cast<LPVOID*>(realloc(ptrvoid_,
                                                allocated_ * sizeof(LPVOID)));
        if (!ptrvoid_)
            return false;
    }
    memmove(&ptrvoid_[v_index + 1],
            &ptrvoid_[v_index], (count_ - v_index - 1) * sizeof(LPVOID));
    ptrvoid_[v_index] = v_data;
    return true;
}

bool UIPtrArray::SetAt(UINT v_index, LPVOID v_data) {
    if (v_index < 0 || v_index >= count_)
        return false;
    ptrvoid_[v_index] = v_data;
    return true;
}

bool UIPtrArray::Remove(UINT v_index) {
    if (v_index < 0 || v_index >= count_)
        return false;
    if (v_index < --count_)
        CopyMemory(ptrvoid_ + v_index,
                   ptrvoid_ + v_index + 1, (count_ - v_index) * sizeof(LPVOID));
    return true;
}

int UIPtrArray::Find(LPVOID v_data) const {
    for (UINT i = 0; i < count_; ++i)
        if (ptrvoid_[i] == v_data)
            return i;
    return -1;
}

UINT UIPtrArray::GetSize() const {
    return count_;
}

LPVOID* UIPtrArray::GetData() {
    return ptrvoid_;
}

LPVOID UIPtrArray::GetAt(UINT v_index) const {
    if (v_index < 0 || v_index >= count_)
        return nullptr;
    return ptrvoid_[v_index];
}

LPVOID UIPtrArray::operator[] (UINT v_index) const {
    if (v_index >= count_)
        return nullptr;
    return ptrvoid_[v_index];
}

////////////////////////////////////////

UIString::UIString() {}

UIString::UIString(const TCHAR v_ch) {
    buffer_ = v_ch;
}

UIString::UIString(const int v_digit) {
    TCHAR buf[64];
    _itot(v_digit, buf, 10);
    buffer_ = buf;
}

UIString::UIString(LPCTSTR v_str, int v_len /*= -1*/) {
    Assign(v_str, v_len);
}

UIString::UIString(const UIString& v_src) {
    buffer_ = v_src.buffer_;
}

UIString::~UIString() {}

int UIString::GetLength() const {
    return buffer_.length();
}

UIString::operator LPCTSTR() const {
    return GetData();
}

void UIString::Append(LPCTSTR v_str) {
    buffer_.append(v_str);
}

void UIString::Assign(LPCTSTR v_str, int v_len /*= -1*/) {
    if (v_len == -1)
        buffer_.assign(v_str);
    else
        buffer_.assign(v_str, v_len);
}

bool UIString::IsEmpty() const {
    return buffer_.empty();
}

void UIString::Empty() {
    buffer_.clear();
}

LPCTSTR UIString::GetData() const {
    return buffer_.c_str();
}

int UIString::Str2Int() const {
    return _ttoi(buffer_.c_str());
}

TCHAR UIString::GetAt(int v_index) const {
    return buffer_[v_index];
}

TCHAR UIString::operator[] (int v_index) const {
    return GetAt(v_index);
}

const UIString& UIString::operator=(LPCTSTR v_str) {
    Assign(v_str);
    return *this;
}

const UIString& UIString::operator=(const TCHAR v_ch) {
    buffer_ = v_ch;
    return *this;
}

UIString UIString::operator+(LPCTSTR v_str) const {
    UIString tmp = *this;
    tmp.Append(v_str);
    return tmp;
}

const UIString& UIString::operator+=(LPCTSTR v_str) {
    Append(v_str);
    return *this;
}

const UIString& UIString::operator+=(const TCHAR v_ch) {
    TCHAR v_str[] = { v_ch, _T('\0') };
    Append(v_str);
    return *this;
}

bool UIString::operator == (LPCTSTR v_str) const { return (Compare(v_str) == 0); }
bool UIString::operator != (LPCTSTR v_str) const { return (Compare(v_str) != 0); }
bool UIString::operator <= (LPCTSTR v_str) const { return (Compare(v_str) <= 0); }
bool UIString::operator <  (LPCTSTR v_str) const { return (Compare(v_str) < 0); }
bool UIString::operator >= (LPCTSTR v_str) const { return (Compare(v_str) >= 0); }
bool UIString::operator >  (LPCTSTR v_str) const { return (Compare(v_str) > 0); }

void UIString::SetAt(int v_index, TCHAR v_ch) {
    buffer_[v_index] = v_ch;
}

int UIString::Compare(LPCTSTR v_str) const {
    return buffer_.compare(v_str);
}

int UIString::CompareNoCase(LPCTSTR v_str) const {
    return _tcsicmp(buffer_.c_str(), v_str);
}

void UIString::MakeUpper() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::toupper);
}

void UIString::MakeLower() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::tolower);
}

UIString UIString::Left(int v_len) const {
    return UIString(buffer_.c_str(), v_len);
}

UIString UIString::Mid(int v_pos, int v_len) const {
    return UIString(buffer_.substr(v_pos, v_len).c_str());
}

UIString UIString::Right(int v_len) const {
    int pos = GetLength() - v_len;
    if (pos < 0) {
        pos = 0;
        v_len = GetLength();
    }
    return Mid(pos, v_len);
}

int UIString::Find(TCHAR v_ch, int v_pos /*= 0*/) const {
    return buffer_.find(v_ch, v_pos);
}

int UIString::Find(LPCTSTR v_str, int v_pos /*= 0*/) const {
    return buffer_.find(v_str, v_pos);
}

int UIString::Replace(LPCTSTR v_str_from, LPCTSTR v_str_to) {
    int cnt = 0;
    for (tstring::size_type pos(0); pos != tstring::npos;
         pos += _tcslen(v_str_to)) {
        if ((pos = buffer_.find(v_str_from, pos)) != tstring::npos) {
            buffer_.replace(pos, _tcslen(v_str_from), v_str_to);
            ++cnt;
        } else {
            break;
        }
    }
    return cnt;
}

int UIString::Format(LPCTSTR v_str, ...) {
    LPTSTR tmp = nullptr;
    va_list argList;
    int len;
    va_start(argList, v_str);
    len = _vsntprintf(NULL, 0, v_str, argList);
    tmp = reinterpret_cast<TCHAR*>(malloc((len + 1) * sizeof(TCHAR)));
    ZeroMemory(tmp, (len + 1) * sizeof(TCHAR));
    int ret = _vsntprintf(tmp, len + 1, v_str, argList);
    va_end(argList);
    Assign(tmp);
    free(tmp);
    return ret;
}

}   // namespace DuiMini
