/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/01/24
 *
 * @Description:
 */
#pragma once

namespace DuiMini {
struct DUIMINI_API UIFont {
    UStr name_;
    UStr lang_;
    UStr font_;
    UINT size_;
    bool bold_;
    bool italic_;
    bool underline_;
    bool strikeout_;
};

////////////////////////////////////////

#define GetAttrPath(x) UIConfig::GetStrPath(x)
#define GetAttrStr(x) UIConfig::TranslateStr(x)

class DUIMINI_API UIConfig {
public:
    /**
    * Load global config
    * @param    LPCTSTR v_relativepath:resource relative path
    * (default:uires.xml)
    */
    static void LoadConfig(LPCTSTR v_relativepath = DEFAULT_RESFILE);

    // Get Shown lang config
    static LANGID GetShownLang();
    static FONTID GetShownFont();
    static SKINID GetShownSkin();

    /**
    * Set Shown Config
    * @param    v_id:config id
    */
    static void SetShownLang(LANGID v_id);
    static void SetShownFont(FONTID v_id);
    static void SetShownSkin(SKINID v_id);

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
    static UIAttr* FindLangMap(LPCTSTR v_name);
    static CUStr FindLangMapValue(LPCTSTR v_name);    // return value directly

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
    static UIAttrSet dlg_;            // dlg config

    static LANGID shownlang_;         // shown lang
    static SKINID shownskin_;         // shown skin
    static FONTID shownfont_;         // shown font
    static UIAttrSet lang_;           // language config
    static UIAttrSet skin_;           // skin config
    static UIAttrSet font_;           // font config

    static UIAttrSet res_id_;         // shown skin resid
    static UIAttrSet lang_str_;       // shown language str
};
}   // namespace DuiMini
