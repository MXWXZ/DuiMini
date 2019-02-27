/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/10
 */
#ifndef DUI_CORE_UISYSTEM_H_
#define DUI_CORE_UISYSTEM_H_

#include "UIDefine.h"

namespace DuiMini {
class DUIMINI_API UISystem {
public:
    /**
     * Initialize DuiMini library
     * You should call this function before using any DuiMini component
     */
    static void Init();

    /**
     * Clean up
     * You should call this function before you return your main function
     * @note    this function will NOT exit the program
     * @see     Exit
     */
    static void Cleanup();

    /**
     * Safely exit the program
     * This function will call Cleanup() automatically, Then exit the program
     * @param	const int code: exit code(default:0)
     * @note    You should use this function as the way to exit safely
     * @see     Cleanup
     */
    static void Exit(const int code = 0);
};

}  // namespace DuiMini

#endif  // !DUI_CORE_UISYSTEM_H_
