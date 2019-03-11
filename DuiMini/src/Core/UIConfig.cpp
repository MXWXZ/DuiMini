/**
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include "Core/UIConfig.h"
#include "Utils/UIException.h"
#include "Core/Resource/UIResource.h"
#include "Core/Resource/UIResLoader.hpp"

namespace DuiMini {
UIConfigItem UIConfig::dlg_;
int UIConfig::shownlang_ = 0;
int UIConfig::shownskin_ = 0;
int UIConfig::shownfont_ = 0;
UIConfigItem UIConfig::lang_;
UIConfigItem UIConfig::skin_;
UIConfigItem UIConfig::font_;
UIConfigItem UIConfig::cache_resid_;
UIConfigItem UIConfig::cache_sys_resid_;
UIConfigItem UIConfig::cache_langstr_;
UIFont UIConfig::cache_font_style_;
uint UIConfig::cache_font_size_ = 0;

#define Config_BeginAttr(node) \
    UIConfigAttr _now;         \
    auto& _node = node
#define Config_EndAttr(item) item.push_back(_now)
#define Config_AddAttrStatic(x, y) _now[x] = y
#define Config_AddAttr(x) _now[x] = _node.GetAttrValue(x)
#define Config_AddAttrDef(x, y) _now[x] = _node.GetAttrValue(x, y)
#define Config_CmpAttr(x, y) _now[x] == y

void DuiMini::UIConfig::LoadConfig(
    const char* path /* = DUIMINI_DEFAULT_CONFIGFILE*/) {
}

int UIConfig::FindLangID(const char* name) { return FindItemID(lang_, name); }

int UIConfig::FindFontID(const char* name) { return FindItemID(lang_, name); }

int UIConfig::FindSkinID(const char* name) { return FindItemID(lang_, name); }

bool UIConfig::SetShownLang(uint id) {
    if (id >= lang_.size()) {
        UISetError(kEL_Warning, "Lang id %d is invalid!", id);
        return false;
    }

    cache_langstr_.clear();
    auto file = UIResource::LoadRes<UIXmlLoader>(lang_[id]["file"].GetData());
    if (!file)
        return false;
    for (auto node = file->GetRoot().FirstChild(); node;
         node = node.NextSibling()) {
        Config_BeginAttr(node);
        Config_AddAttr("name");
        Config_AddAttr("value");
        Config_EndAttr(cache_langstr_);
    }
    shownlang_ = id;
    return true;
}

bool UIConfig::SetShownFont(uint id) {
    if (id >= font_.size()) {
        UISetError(kEL_Warning, "Font id %d is invalid!", id);
        return false;
    }

    auto& nowfont = font_[id];
    if (nowfont["lang"] != lang_[shownlang_]["lang"]) {
        UISetError(kEL_Warning, "Font %s in language %s mismatch with %s!",
                   nowfont["name"].GetData(), nowfont["lang"].GetData(), lang_[shownlang_]["lang"].GetData());
        return false;
    }

    auto file = UIResource::LoadRes<UIRawLoader>(nowfont["file"].GetData());
    if (!file)
        return false;
    if (!cache_font_style_.loadFromMemory(file->GetFile(), file->GetFileSize()))
        return false;
    shownfont_ = id;
    return true;
}

bool UIConfig::SetShownSkin(uint id) {
    if (id >= skin_.size()) {
        UISetError(kEL_Warning, "Skin id %d is invalid!", id);
        return false;
    }

    cache_resid_.clear();
    auto file = UIResource::LoadRes<UIXmlLoader>(
        (skin_[id]["value"] + "/resid.xml").GetData());
    if (!file)
        return false;
    for (auto node = file->GetRoot().FirstChild(); node;
         node = node.NextSibling()) {
        Config_BeginAttr(node);
        Config_AddAttr("type");
        Config_AddAttr("name");
        Config_AddAttr("file");
        Config_EndAttr(cache_resid_);
    }
    shownskin_ = id;
    return true;
}

bool UIConfig::AddSystemSkin(uint id) {
    if (id >= skin_.size()) {
        UISetError(kEL_Warning, "Skin id %d is invalid!", id);
        return false;
    }

    auto file = UIResource::LoadRes<UIXmlLoader>(
        (skin_[id]["value"] + "/resid.xml").GetData());
    if (!file)
        return false;
    for (auto node = file->GetRoot().FirstChild(); node;
         node = node.NextSibling()) {
        Config_BeginAttr(node);
        Config_AddAttr("type");
        Config_AddAttr("name");
        Config_AddAttr("file");
        Config_EndAttr(cache_sys_resid_);
    }
    return true;
}

UIStr UIConfig::FindDlgFile(const char* name) {
    auto tmp = FindItem(dlg_, name);
    return tmp.empty() ? UIStr() : tmp["file"];
}

UIStr UIConfig::FindResFile(const char* name) {
    auto tmp = FindNextItem(cache_resid_, 0, "name", name);
    if (tmp.empty()) {
        tmp = FindNextItem(cache_sys_resid_, 0, "name", name);
        if (tmp.empty()) {
            UISetError(kEL_Warning, "Resid %s not found!", name);
            return UIStr();
        }
    }
    return tmp["file"];
}

UIStr UIConfig::FindLangFile(const char* name) {
    auto tmp = FindItem(cache_langstr_, name);
    return tmp.empty() ? UIStr() : tmp["file"];
}

UIFont UIConfig::FindFont(const char* name) {
    auto nowfont = FindItem(font_, name);
    if (nowfont.empty())
        return UIFont();
    auto file = UIResource::LoadRes<UIRawLoader>(nowfont["file"].GetData());
    if (!file)
        return UIFont();
    UIFont ret;
    if (!ret.loadFromMemory(file->GetFile(), file->GetFileSize()))
        return UIFont();
    return ret;
}

UIStr UIConfig::TranslatePath(const char* str) {
    UIStr tmp = str;
    size_t len = tmp.GetLength();
    if (!len)
        return UIStr();
    if (tmp[0] == '[' && tmp[len - 1] == ']')
        return FindResFile(tmp.Mid(1, len - 2).GetData());
    else
        return tmp;
}

UIStr UIConfig::TranslateStr(const char* str) {
    UIStr tmp = str;
    size_t len = tmp.GetLength();
    if (!len)
        return UIStr();
    if (tmp[0] == '[' && tmp[len - 1] == ']')
        return FindLangFile(tmp.Mid(1, len - 2).GetData());
    else if (tmp[0] == '\\' && tmp[1] == '[' && tmp[len - 1] == ']')
        return tmp.Mid(1, len - 1);
    else
        return tmp;
}

UIConfigAttr UIConfig::FindNextItem(const UIConfigItem& item, uint start,
                                    const char* name, const char* value) {
    if (start >= item.size())
        return UIConfigAttr();
    for (auto i = item.begin() + start; i != item.end(); ++i)
        if ((*i).at(name) == value)
            return *i;
    return UIConfigAttr();
}

int UIConfig::FindItemID(const UIConfigItem& item, const char* name) {
    for (auto i = item.begin(); i != item.end(); ++i)
        if ((*i).at("name") == name)
            return i - item.begin();
    UISetError(kEL_Warning, "Item %s not found!", name);
    return -1;
}

UIConfigAttr UIConfig::FindItem(const UIConfigItem& item, const char* name) {
    auto ret = FindNextItem(item, 0, "name", name);
    if (!ret.empty())
        return ret;
    UISetError(kEL_Warning, "Item %s not found!", name);
    return UIConfigAttr();
}

}  // namespace DuiMini
