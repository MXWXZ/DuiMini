/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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

private:
    static HINSTANCE instance_;     // program instance
};

}   // namespace DuiMini
