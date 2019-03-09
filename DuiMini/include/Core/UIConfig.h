/** @file
 * UI config manager.
 * Manage main config file.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_CORE_UICONFIG_H_
#define DUI_CORE_UICONFIG_H_

#include "UIDefine.h"
#include "Utils/UIUtils.h"

namespace DuiMini {
/**
 * Get config from main config file.
 */
class DUIMINI_API UIConfig {
public:
    /**
     * Load global config.
     * @param   path: config file path
     */
    static void LoadConfig(const char* path = DUIMINI_DEFAULT_CONFIGFILE);

    // find id
    static int FindLangID(const char* name);
    static int FindFontID(const char* name);
    static int FindSkinID(const char* name);

    // Get shown config id
    static int GetShownLangID() { return shownlang_; }
    static int GetShownFontID() { return shownfont_; }
    static int GetShownSkinID() { return shownskin_; }

    // Get shown config
    static UIConfigAttr GetShownLang() { return lang_[shownlang_]; }
    static UIConfigAttr GetShownFont() { return font_[shownfont_]; }
    static UIConfigAttr GetShownSkin() { return skin_[shownskin_]; }

    // Set shown config
    static bool SetShownLang(uint id);
    static bool SetShownFont(uint id);
    static bool SetShownSkin(uint id);
    static bool AddSystemSkin(uint id);

    /**
     * Find dlg file.
     * @param	name: dlgname
     * @return	xml file, empty for not found
     */
    static UIStr FindDlgFile(const char* name);

    /**
     * Find res file.
     * @param	name: resid
     * @return	res file, empty for not found
     */
    static UIStr FindResFile(const char* name);

    /**
     * Find lang file.
     * @param	name: lang name
     * @return	lang file, empty for not found
     */
    static UIStr FindLangFile(const char* name);

    /**
     * Get current font style.
     * @return  font style
     */
    static UIFont GetFontStyle() { return cache_font_style_; }

    static uint GetFontSize() { return cache_font_size_; }

    /**
     * Find font.
     * @param	name: font name(in current language)
     * @return	font class
     */
    static UIFont FindFont(const char* name);

    /**
     * Translate real file path from str(resid or path).
     * @param   str: str need to get path
     * @return  relative path, empty for not find
     * @note    This function will check '[' at the beginning and ']' at the end
     * to distinguish resid and path, please use "[resid]" to represent you want
     * to use resid.
     */
    static UIStr TranslatePath(const char* str);

    /**
     * Translate string from string(langstr or plain string).
     * @param   str: str need to translate
     * @return  translated string, if langstr not found, return \p str .
     * @note    This function will check '[' at the beginning and ']' at the end
     * to distinguish langstr and plain str, please use "[langstr]"
     * to represent you want to use langstr.
     * If your string is like "[string]"(started with '[' and ends in ']')
     * and you dont want to parse it as langstr, you must change the beginning
     * '[' to "\[".
     * e.g. if you want to use "[[abc[def]" as a string other than langstr,
     * you must write it like "\[[abc[def]"
     */
    static UIStr TranslateStr(const char* str);

private:
    static UIConfigAttr FindNextItem(const UIConfigItem& item, uint start,
                                     const char* name, const char* value);

    static int FindItemID(const UIConfigItem& item, const char* name);
    static UIConfigAttr FindItem(const UIConfigItem& item, const char* name);

private:
    static UIConfigItem dlg_;  //!< dlg config

    static int shownlang_;      //!< shown lang
    static int shownskin_;      //!< shown skin
    static int shownfont_;      //!< shown font
    static UIConfigItem lang_;  //!< language config
    static UIConfigItem skin_;  //!< skin config
    static UIConfigItem font_;  //!< font config

    // Cache
    static UIConfigItem cache_resid_;      //!< cache shown skin resid
    static UIConfigItem cache_sys_resid_;  //!< cache system skin id
    static UIConfigItem cache_langstr_;    //!< cache shown language str
    static UIFont cache_font_style_;       //!< cache shown font style
    static uint cache_font_size_;          //!< cache shown font size
};
}  // namespace DuiMini

#endif  // !DUI_CORE_UICONFIG_H_
