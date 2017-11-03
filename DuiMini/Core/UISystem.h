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

    /**
     * Get program Instance
     * @return   the instance set before
    */
    static HINSTANCE GetInstance() { return instance_; }

    /**
     * Load global config
     * @param    LPCTSTR path:resource path(default:uires.xml)
     * @return   true success  false failed
     */
    static bool LoadConfig(LPCTSTR path = DEFAULT_RESFILE);

private:
    static HINSTANCE instance_;     // program instance

    static UINode cfg_lang_;    // language config
};

}   // namespace DuiMini
