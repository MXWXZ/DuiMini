/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
enum StringAlign {
    kSA_LT,
    kSA_MT,
    kSA_RT,
    kSA_LM,
    kSA_MM,
    kSA_RM,
    kSA_LB,
    kSA_MB,
    kSA_RB,
};

enum StringTrimming {
    kST_None = 0,
    kST_Ch = 1,
    kST_Word = 2,
    kST_DotCh = 3,
    kST_DotWord = 4,
    kST_DotMid = 5
};

struct DUIMINI_API UIFont {
    UStr name_;
    UStr lang_;
    UStr font_;
    USHORT size_ = 0;
    bool bold_ = false;
    bool italic_ = false;
    bool underline_ = false;
    bool strikeout_ = false;
};

struct DUIMINI_API UIStringFormat {
    UIColor color_;
    StringTrimming trimming_ = kST_None;
    StringAlign align_ = kSA_LT;
    bool autowrap_ = false;
    bool vertical_ = false;
};

////////////////////////////////////////

#define UIGetStrPath(x) UIConfig::GetStrPath(x)
#define UITranslateStr(x) UIConfig::TranslateStr(x)

class DUIMINI_API UIConfig {
public:
    /**
    * Load global config
    * @param    LPCTSTR v_relativepath:resource relative path
    * (default:uires.xml)
    */
    static void LoadConfig(LPCTSTR v_relativepath = DEFAULT_RESFILE);

    // find id
    static CFGID FindLangID(LPCTSTR v_name);
    static CFGID FindFontID(LPCTSTR v_name);
    static CFGID FindSkinID(LPCTSTR v_name);

    // Get shown config id
    static CFGID GetShownLangID() { return shownlang_; }
    static CFGID GetShownFontID() { return shownfont_; }
    static CFGID GetShownSkinID() { return shownskin_; }

    // Get shown config
    static UIAttr& GetShownLang() { return lang_[shownlang_]; }
    static UIAttr& GetShownFont() { return font_[shownfont_]; }
    static UIAttr& GetShownSkin() { return skin_[shownskin_]; }

    /**
    * Set Shown Config
    * @param    v_id:config id
    */
    static bool SetShownLang(CFGID v_id);
    static bool SetShownFont(CFGID v_id);
    static bool SetShownSkin(CFGID v_id);
    static bool AddSystemSkin(CFGID v_id);

    /**
    * Find dlg config
    * @param    LPCTSTR v_name:dlgname
    * @return   dlg attr structure, nullptr for not find
    */
    static UIAttr* FindDlg(LPCTSTR v_name);
    static CUStr FindDlgFile(LPCTSTR v_name);       // return file directly

    /**
    * Find resid
    * @param    LPCTSTR v_name:resid name
    * @return   resid attr structure, nullptr for not find
    */
    static UIAttr* FindResid(LPCTSTR v_name);
    static CUStr FindResidFile(LPCTSTR v_name);     // return file directly

    /**
     * Get real file path from str(resid or path)
     * @param    LPCTSTR v_str:str need to get path
     * @return   relative path, empty for not find
     * This function will check '[' at the beginning and ']' at the end
     * to distinguish resid and path, please use "[resid]" to represent
     * you want to use resid.
     */
    static CUStr GetStrPath(LPCTSTR v_str);

    /**
     * Find language string map
     * @param    LPCTSTR v_name:str name
     * @return   langstr attr structure, nullptr for not find
     */
    static UIAttr* FindLang(LPCTSTR v_name);
    static CUStr FindLangValue(LPCTSTR v_name);    // return value directly

    /**
     * Get current font style
     * @return   font style
     */
    static UIFont GetFontStyle() { return font_style_; }
    /**
     * Find font
     * @param    LPCTSTR v_name:font name
     * @return   font attr structure, nullptr for not find
     */
    static UIAttr* FindFont(LPCTSTR v_name);
    static UIFont FindFontValue(LPCTSTR v_name);    // return value directly

    /**
    * Translate string from string(langstr or plain string)
    * @param    LPCTSTR v_str:str need to translate
    * @return   translated string, if langstr not find, return v_str.
    * This function will check '[' at the beginning and ']' at the end
    * to distinguish langstr and plain str, please use "[langstr]"
    * to represent you want to use langstr.
    *
    * If your string is like "[string]"(started with '[' and ends in ']')
    * and you dont want to parse it as langstr, you must change the beginning
    * '[' to "\[". 
    * e.g. if you want to use "[[abc[def]" as a string other than langstr,
    * you must write it like "\[[abc[def]"
    */
    static CUStr TranslateStr(LPCTSTR v_str);

private:
    /**
    * Find next CFG item with v_name=v_value
    * @return   nullptr for not find
    */
    static UIAttr* FindNextCFGItem(UICFGItem& v_item, UINT v_start,
                                   LPCTSTR v_name, LPCTSTR v_value);

    static CFGID FindItemID(const UICFGItem& v_item, LPCTSTR v_name);
    static UIAttr* FindItem(UICFGItem& v_item, LPCTSTR v_name);

private:
    static UICFGItem dlg_;            // dlg config

    static CFGID shownlang_;          // shown lang
    static CFGID shownskin_;          // shown skin
    static CFGID shownfont_;          // shown font
    static UICFGItem lang_;           // language config
    static UICFGItem skin_;           // skin config
    static UICFGItem font_;           // font config

    static UICFGItem res_id_;         // shown skin resid
    static UICFGItem sys_res_id_;     // system skin id
    static UICFGItem lang_str_;       // shown language str
    static UIFont font_style_;        // shown font style
};
}   // namespace DuiMini
