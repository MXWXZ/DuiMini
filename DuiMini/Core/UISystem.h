// ****************************************
// Copyright (c) 2017-2050
// All rights reserved.
//
// Author:MXWXZ
// Date:2017/09/05
//
// Description:UI global class
// ****************************************
#pragma once

namespace DuiMini {
// ****************************************
// system class
// manage all about the ui system
// ****************************************
class DUIMINI_API UISystem {
public:
    // ****************************************
    // Initialize DuiMini library
    // -param    HINSTANCE inst:program HINSTANCE,usually the param of WinMain
    // ****************************************
    static void Init(HINSTANCE inst);

    // ****************************************
    // Clean up
    // this function will NOT exit the program
    // ****************************************
    static void Cleanup();

    // ****************************************
    // Safely exit the program
    // -param    const int code: exit code(default:0)
    // this function will call Cleanup() automatically
    // you should NOT use this function as the way to exit safely
    // ****************************************
    static void Exit(const int code = 0);

    // ****************************************
    // Set program Instance
    // -param    HINSTANCE inst:program HINSTANCE,usually the param of WinMain
    // ****************************************
    static void SetInstance(HINSTANCE inst) { instance_ = inst; }

    // ****************************************
    // Get program Instance
    // -return   the instance set before
    // ****************************************
    static HINSTANCE GetInstance() { return instance_; }

public:
    // ****************************************
    // Get the current path
    // -return   current dir
    // the path does NOT include the \\ and file name at the end
    // e.g. C:\\windows\\system32
    // WARNING!return value is temporary object and should be transfer to
    // another UStr object if you want to use it later
    // ****************************************
    static CUStr GetCurrentDir();

protected:
    static HINSTANCE instance_;     // program instance
};

}   // namespace DuiMini
