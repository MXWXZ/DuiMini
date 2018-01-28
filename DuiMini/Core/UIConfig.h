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
class DUIMINI_API UIConfig {
public:
    /**
    * Load global config
    * @param    LPCTSTR v_relativepath:resource relative path
    * (default:uires.xml)
    */
    static void LoadConfig(LPCTSTR v_relativepath = DEFAULT_RESFILE);

    /**
    * Get config
    * @return   UIAttrSet structure point
    */
    static UIAttrSet* GetLang();
    static UIAttrSet* GetFont();
    static UIAttrSet* GetSkin();
    static UIAttrSet* GetDlg();
    static UIAttrSet* GetResid();
    static UIAttrSet* GetLangstr();

    /**
    * Get Shown config
    */
    static UINT GetCFGShownLang();
    static UINT GetCFGShownFont();
    static UINT GetCFGShownSkin();

    /**
    * Set Shown Config
    * @param    UINT v_id:config id
    * @return   new config id
    */
    static UINT SetShownLang(UINT v_id);
    static UINT SetShownFont(UINT v_id);
    static UINT SetShownSkin(UINT v_id);

    /**
    * Find dlg config
    * @param    LPCTSTR v_name:dlgname
    * @return   dlg attr structure, nullptr for not find
    */
    static UIAttr* FindDlg(LPCTSTR v_name);

    /**
    * Find resid
    * @param    LPCTSTR v_name:resid name
    * @return   resid attr structure, nullptr for not find
    */
    static UIAttr* FindResid(LPCTSTR v_name);
    static CUStr FindResidFile(LPCTSTR v_name);     // return file directly

    /**
     * Get real file path from str(resid or path)
     * @param    LPCTSTR v_str:resid or path
     * @return   relative path, empty for not find
     * This function will check '[' at the beginning and ']' at the end
     * to distinguish resid and path, please use "[resid]" to represent
     * you want to use resid.
     */
    static CUStr GetStrFile(LPCTSTR v_str);

    /**
     * Find language str
     * @param    LPCTSTR v_name:str name
     * @return   langstr attr structure, nullptr for not find
     */
    static UIAttr* FindLangstr(LPCTSTR v_name);
    static CUStr FindLangstrValue(LPCTSTR v_name);

    /**
    * Get real string from string(language string or string)
    * @param    LPCTSTR v_str:langstr or str
    * @return   real string, if langstr not find, return itself.
    * This function will check '[' at the beginning and ']' at the end
    * to distinguish langstr and str, please use "[langstr]" to represent
    * you want to use langstr.
    *
    * If your string is like "[string]"(started with '[' and ends in ']')
    * and you dont want to parse it as langstr, you must change the beginning
    * '[' to "\[". 
    * e.g. if you want to use "[[abc[def]" as a string other than langstr,
    * you must write it like "\[[abc[def]"
    */
    static CUStr GetStrStr(LPCTSTR v_str);

private:
    static UIAttrSet cfg_dlg_;        // dlg config

    static UINT cfg_shownlang_;       // shown lang
    static UINT cfg_shownskin_;       // shown skin
    static UINT cfg_shownfont_;       // shown font
    static UIAttrSet cfg_lang_;       // language config
    static UIAttrSet cfg_skin_;       // skin config
    static UIAttrSet cfg_font_;       // font config

    static UIAttrSet res_id_;         // shown skin resid
    static UIAttrSet lang_str_;       // shown language str
};

#define GetAttrFile(x) UIConfig::GetStrFile(GetAttribute(x))
#define GetAttrStr(x) UIConfig::GetStrStr(GetAttribute(x))
}   // namespace DuiMini
