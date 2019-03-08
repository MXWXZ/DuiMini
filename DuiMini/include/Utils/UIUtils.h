/** @file
 * Utils for the UI system
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_UTILS_UIUTILS_H_
#define DUI_UTILS_UIUTILS_H_

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "UIDefine.h"

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

namespace DuiMini {
/**
 * make_shared do not support array, just make it support.
 * @param	size: array size
 * @return	shared_ptr var
 */
template <typename T>
std::shared_ptr<T> make_shared_array(size_t size) {
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

////////////////////////////////////////

class DUIMINI_API UIString {
public:
    UIString();
    UIString(const char ch);
    UIString(const std::string& str);
    UIString(const UIString& src);
    UIString(UIString&& src);
    UIString(const char* str, size_t len = -1);
    ~UIString();

public:
    void Append(const char* str);
    void Assign(const char* str, size_t len = -1);

    void Empty();
    bool IsEmpty() const;
    size_t GetLength() const;
    void SetAt(size_t index, const char ch);
    char GetAt(size_t index) const;
    const char* GetData() const;

    long long Str2LL() const;
    double Str2Double() const;
    UIString Str2Hex() const;
    UIString Hex2Str() const;
    UIString UL2Hex() const;
    unsigned long Hex2UL() const;

    char operator[](int index) const;
    UIString& operator=(UIString& str);
    UIString& operator=(UIString&& str);
    UIString operator+(const UIString& str) const;
    UIString& operator+=(const UIString& str);

    bool operator==(const UIString& str) const;
    bool operator!=(const UIString& str) const;
    bool operator<=(const UIString& str) const;
    bool operator<(const UIString& str) const;
    bool operator>=(const UIString& str) const;
    bool operator>(const UIString& str) const;

    int Compare(const UIString& str) const;
    int CompareNoCase(const UIString& str) const;

    void MakeUpper();
    void MakeLower();
    UIString ToUpper() const;
    UIString ToLower() const;

    UIString Left(size_t len) const;
    UIString Mid(size_t pos, size_t len) const;
    UIString Right(size_t len) const;

    long long Find(const UIString& str, size_t pos = 0) const;
    size_t Replace(const UIString& str_from, const UIString& str_to);

    int Format(const char* str, ...);

private:
    std::shared_ptr<std::string> buffer_;  //!< prevent warning C4251
};
typedef UIString UIStr;

typedef sf::IntRect UIRect;
typedef sf::Color UIColor;
typedef unsigned char RGBA;

/**
 * Screen point.
 */
struct Point {
    uint x;  //!< from left to right
    uint y;  //!< from top to bottom
};

////////////////////////////////////////

class DUIMINI_API UIUtils {
public:
    /**
     * Get full screen rect.
     * @return  size rect
     */
    static UIRect GetScreenRect();

    /**
     * Get color from \#xxxxxx or explicit color name.
     * @param	str: color string\n
     * @parblock
     * Support format:\n
     * \#00000000-\#FFFFFFFF RGBA hex format\n
     * \#000000-\#FFFFFF  RGB hex format with 100% alpha(equal to \#xxxxxxFF)\n
     * black        \#000000\n
     * white        \#FFFFFF\n
     * red          \#FF0000\n
     * green        \#00FF00\n
     * blue         \#0000FF\n
     * yellow       \#FFFF00\n
     * cyan         \#00FFFF\n
     * purple       \#FF00FF\n
     * gray         \#C0C0C0\n
     * transparent  \#00000000
     * @endparblock
     * @return	Parsed color, black for error
     */
    static UIColor GetColorFromStr(const char* str);
};
}  // namespace DuiMini

#endif  // !DUI_UTILS_UIUTILS_H_
