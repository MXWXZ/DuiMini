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
    * [SAFE]Find dlg config
    * @param    LPCTSTR v_name:dlgname
    * @return   dlg attr structure, nullptr for not find
    */
    static UIAttr* FindDlg(LPCTSTR v_name);

    /**
    * [SAFE]Find resid
    * @param    LPCTSTR v_name:resid name
    * @return   resid attr structure, nullptr for not find
    */
    static UIAttr* FindResid(LPCTSTR v_name);
    static CUStr FindResidFile(LPCTSTR v_name);     // return file directly

    /**
     * [SAFE]Get real file path from str(resid or path)
     * @param    LPCTSTR v_str:resid or path
     * @return   relative path, empty for not find
     * This function will find '.' to distinguish resid and path, so please
     * ensure every path include '.' and every resid exclude '.'
     */
    static CUStr GetStrFile(LPCTSTR v_str);

private:
    static UIAttrSet cfg_dlg_;        // dlg config

    static UINT cfg_shownlang_;       // shown lang
    static UINT cfg_shownskin_;       // shown skin
    static UINT cfg_shownfont_;       // shown font
    static UIAttrSet cfg_lang_;       // language config
    static UIAttrSet cfg_skin_;       // skin config
    static UIAttrSet cfg_font_;       // font config

    static UIAttrSet res_id_;         // shown skin resid
};

#define GetAttrFile(x) UIConfig::GetStrFile(GetAttribute(x))
}   // namespace DuiMini
