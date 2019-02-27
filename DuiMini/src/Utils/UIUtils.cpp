/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/01/18
 */

#include "Utils/UIUtils.h"
#include <SFML/Window/VideoMode.hpp>

#include <string>
#include <stdarg.h>

#ifdef WIN32
#define stricmp _stricmp
#else
#include <strings.h>
#define stricmp strcasecmp
#endif

namespace DuiMini {
UIString::UIString() {}

UIString::UIString(const char ch) { buffer_ = ch; }

UIString::UIString(const std::string& str) { buffer_ = str; }

UIString::UIString(const char* str, size_t len /*= -1*/) { Assign(str, len); }

UIString::UIString(const UIString& src) { buffer_ = src.buffer_; }

UIString::UIString(UIString&& src) { buffer_ = move(src.buffer_); }

UIString::~UIString() {}

void UIString::Append(const char* str) { buffer_.append(str); }

void UIString::Assign(const char* str, size_t len /*= -1*/) {
    if (len == size_t(-1))
        buffer_.assign(str);
    else
        buffer_.assign(str, len);
}

bool UIString::IsEmpty() const { return buffer_.empty(); }

void UIString::Empty() { buffer_.clear(); }

size_t UIString::GetLength() const { return buffer_.length(); }

void UIString::SetAt(size_t index, const char ch) { buffer_[index] = ch; }

char UIString::GetAt(size_t index) const { return buffer_[index]; }

const char* UIString::GetData() const { return buffer_.c_str(); }

long long UIString::Str2LL() const {
    return std::stoll(GetData(), nullptr, 10);
}

double UIString::Str2Double() const { return std::stod(GetData()); }

UIString UIString::Str2Hex() const {
    UIString ret;
    char buf[10];
    for (auto& i : buffer_) {
        if (i < 0)  // only support ascii
            break;
        sprintf(buf, "%X", i);
        ret += buf;
    }
    return ret;
}

UIString UIString::Hex2Str() const {
    UIString ret;
    size_t len = buffer_.size();
    if (len % 2)
        --len;
    char buf[3] = {0};
    for (size_t i = 0; i < len; i += 2) {
        buf[0] = buffer_[i];
        buf[1] = buffer_[i + 1];
        buf[2] = '\0';
        ret += (char)std::stoll(buf, nullptr, 16);
    }
    return ret;
}

UIString UIString::UL2Hex() const {
    char buf[64];
    sprintf(buf, "%X",
            static_cast<unsigned int>(std::stoul(GetData(), nullptr, 10)));
    return UIString(buf);
}

unsigned long UIString::Hex2UL() const {
    return std::stoul(GetData(), nullptr, 16);
}

char UIString::operator[](int index) const { return GetAt(index); }

UIString& UIString::operator=(UIString& str) {
    buffer_ = str.buffer_;
    return *this;
}

UIString& UIString::operator=(UIString&& str) {
    buffer_ = move(str.buffer_);
    return *this;
}

UIString UIString::operator+(const UIString& str) const {
    UIString tmp = *this;
    tmp += str;
    return tmp;
}

UIString& UIString::operator+=(const UIString& str) {
    buffer_.append(str.buffer_);
    return *this;
}

bool UIString::operator==(const UIString& str) const {
    return (Compare(str) == 0);
}

bool UIString::operator!=(const UIString& str) const {
    return (Compare(str) != 0);
}

bool UIString::operator<=(const UIString& str) const {
    return (Compare(str) <= 0);
}

bool UIString::operator<(const UIString& str) const {
    return (Compare(str) < 0);
}

bool UIString::operator>=(const UIString& str) const {
    return (Compare(str) >= 0);
}

bool UIString::operator>(const UIString& str) const {
    return (Compare(str) > 0);
}

int UIString::Compare(const UIString& str) const {
    return buffer_.compare(str.buffer_);
}

int UIString::CompareNoCase(const UIString& str) const {
    return stricmp(GetData(), str.GetData());
}

void UIString::MakeUpper() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::toupper);
}

void UIString::MakeLower() {
    std::transform(buffer_.begin(), buffer_.end(), buffer_.begin(), ::tolower);
}

UIString UIString::ToUpper() const {
    UIString ret = *this;
    ret.MakeUpper();
    return ret;
}

UIString UIString::ToLower() const {
    UIString ret = *this;
    ret.MakeLower();
    return ret;
}

UIString UIString::Left(size_t len) const { return Mid(0, len); }

UIString UIString::Mid(size_t pos, size_t len) const {
    return UIString(buffer_.substr(pos, len).c_str());
}

UIString UIString::Right(size_t len) const {
    size_t pos = GetLength() - len;
    if (pos < 0) {
        pos = 0;
        len = GetLength();
    }
    return Mid(pos, len);
}

long long UIString::Find(const UIString& str, size_t pos /*= 0*/) const {
    size_t ret = buffer_.find(str.GetData(), pos);
    return (ret == std::string::npos) ? (long long)-1 : ret;
}

size_t UIString::Replace(const UIString& str_from, const UIString& str_to) {
    size_t cnt = 0;
    size_t steplen = str_to.GetLength();
    for (std::string::size_type pos(0); pos != std::string::npos;
         pos += steplen) {
        if ((pos = buffer_.find(str_from.GetData(), pos)) !=
            std::string::npos) {
            buffer_.replace(pos, str_from.GetLength(), str_to.GetData());
            ++cnt;
        } else {
            break;
        }
    }
    return cnt;
}

int UIString::Format(const char* str, ...) {
    // va_list can only be used once in gcc!
    // though reuse is also allowed in MinGW
    va_list args1, args2;
    va_start(args1, str);
    va_copy(args2, args1);
    int len = vsnprintf(nullptr, 0, str, args1);
    va_end(args1);
    auto buf = make_shared_array<char>(len + 1);
    int ret = vsnprintf(buf.get(), len + 1, str, args2);
    va_end(args2);
    Assign(buf.get());
    return ret;
}

////////////////////////////////////////

UIRect UIUtils::GetScreenRect() {
    auto size = sf::VideoMode::getDesktopMode();
    return UIRect(0, 0, size.width, size.height);
}

UIColor UIUtils::GetColorFromStr(const char* str) {
    UIStr tmp = str;
    if (tmp == "black")
        tmp = "#000000";
    else if (tmp == "white")
        tmp = "#FFFFFF";
    else if (tmp == "red")
        tmp = "#FF0000";
    else if (tmp == "green")
        tmp = "#00FF00";
    else if (tmp == "blue")
        tmp = "#0000FF";
    else if (tmp == "yellow")
        tmp = "#FFFF00";
    else if (tmp == "cyan")
        tmp = "#00FFFF";
    else if (tmp == "purple")
        tmp = "#FF00FF";
    else if (tmp == "gray")
        tmp = "#C0C0C0";
    else if (tmp == "transparent")
        tmp = "#00000000";
    if (tmp.GetLength() == 9)  // RGBA
        return UIColor(
            (RGBA)tmp.Mid(1, 2).Hex2UL(), (RGBA)tmp.Mid(3, 2).Hex2UL(),
            (RGBA)tmp.Mid(5, 2).Hex2UL(), (RGBA)tmp.Mid(7, 2).Hex2UL());
    else  // RGB(A=255)
        return UIColor((RGBA)tmp.Mid(1, 2).Hex2UL(),
                       (RGBA)tmp.Mid(3, 2).Hex2UL(),
                       (RGBA)tmp.Mid(5, 2).Hex2UL());
}
}  // namespace DuiMini
