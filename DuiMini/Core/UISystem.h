/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:UI global class
 */
#pragma once

namespace DuiMini {
/**
 * system class
 * manage all about the ui system
 */
class DUIMINI_API UISystem {
public:
    /**
     * Initialize DuiMini library
     * @param    HINSTANCE inst:program HINSTANCE,usually the param of WinMain
    */
    static void Init(HINSTANCE inst);

    /**
     * Clean up
     * this function will NOT exit the program
    */
    static void Cleanup();

    /**
     * Safely exit the program
     * @param    const int code: exit code(default:0)
     * this function will call Cleanup() automatically
     * you should use this function as the way to exit safely
    */
    static void Exit(const int code = 0);

    /**
     * Set program Instance
     * @param    HINSTANCE inst:program HINSTANCE,usually the param of WinMain
    */
    static void SetInstance(HINSTANCE inst) { instance_ = inst; }
    static HINSTANCE GetInstance() { return instance_; }

    /**
     * Load global config
     * @param    LPCTSTR path:resource path(default:uires.xml)
     */
    static void LoadConfig(LPCTSTR path = DEFAULT_RESFILE);

    /**
     * Get config
     * @param    UINT id:config id
     * @return   UIAttr structure
     * WARNING:The function WILL NOT check whether id is valid!
     */
    static const UIAttr& GetCFGLang(UINT id) { return cfg_lang_[id]; }
    static const UIAttr& GetCFGFont(UINT id) { return cfg_font_[id]; }
    static const UIAttr& GetCFGSkin(UINT id) { return cfg_skin_[id]; }

    static UINT GetCFGShownLang() { return cfg_shownlang_; }
    static UINT GetCFGShownFont() { return cfg_shownfont_; }
    static UINT GetCFGShownSkin() { return cfg_shownskin_; }

private:
    static HINSTANCE instance_;     // program instance

    static UINT cfg_shownlang_;       // shown lang
    static UINT cfg_shownskin_;       // shown skin
    static UINT cfg_shownfont_;       // shown font
    static UIAttrSet cfg_lang_;       // language config
    static UIAttrSet cfg_skin_;       // skin config
    static UIAttrSet cfg_font_;       // font config
};

}   // namespace DuiMini
