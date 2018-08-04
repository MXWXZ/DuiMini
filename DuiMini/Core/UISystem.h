/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

namespace DuiMini {
class DUIMINI_API UISystem {
public:
    /**
     * Initialize DuiMini library
     * @param    HINSTANCE v_instance:program HINSTANCE,usually the param 
     * of WinMain
    */
    static void Init(HINSTANCE v_instance);

    /**
     * Clean up
     * this function will NOT exit the program
    */
    static void Cleanup();

    /**
     * Safely exit the program
     * @param    const int v_code: exit code(default:0)
     * this function will call Cleanup() automatically
     * you should use this function as the way to exit safely
    */
    static void Exit(const int v_code = 0);

    static void SetInstance(HINSTANCE v_inst) { instance_ = v_inst; }
    static HINSTANCE GetInstance() { return instance_; }

    /**
     * change language/skin
     * @param    v_id:config id
     * @return   true for success
     * ALL windows will receive event and global config will be change!
     */
    static bool ChangeSkin(CFGID v_id);
    static bool ChangeLang(CFGID v_id);

    /**
     * Window operation
     * Tip: here only register Window pointer to the ui system
     *      the operation you did here only affect the record of windows in the
     *      system and will DO NOTHING to the window itself(e.g. release the 
     *      space or anything else)
     */
    static void AddWindow(UIWindow* v_window);
    static UIWindow* GetWindow(LPCTSTR v_classname);
    static bool RemoveWindow(UIWindow* v_window);
    static void RemoveAllWindow();

private:
    static HINSTANCE instance_;
    static UIPtrArray window_;      // created window
};

}   // namespace DuiMini
