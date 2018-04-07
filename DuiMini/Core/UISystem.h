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

    /**
     * Set program Instance
     * @param    HINSTANCE v_instance:program HINSTANCE,usually the param
     * of WinMain
    */
    static void SetInstance(HINSTANCE v_instance);
    static HINSTANCE GetInstance();

    /**
     * change language/skin
     * @param    v_id:config id
     * @return   true for success
     * ALL windows will receive event and global config will be change!
     */
    static bool ChangeSkin(SKINID v_id);
    static bool ChangeLang(LANGID v_id);

    /**
     * Window operation
     */
    static bool AddWindow(UIWindow* v_window);
    static UIWindow* GetWindow(LPCTSTR v_classname);
    static bool RemoveWindow(UIWindow* v_window);
    static void RemoveAllWindow();

private:
    static HINSTANCE instance_;     // program instance
    static UIPtrArray window_;      // created window
};

}   // namespace DuiMini
