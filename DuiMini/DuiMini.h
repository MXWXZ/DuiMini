/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
 */
#pragma once

// system header files
#include <cstdio>
#include <cassert>
#include <clocale>
#include <ctime>
#include <algorithm>
#include <string>
#include "windows.h"
#include "windowsx.h"
#include "tchar.h"
#include <map>
#include <vector>
#include <utility>
#include <CommCtrl.h> 
#pragma comment(lib,"comctl32.lib")  

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// third-part
#include "thirdpart/pugixml/pugixml.hpp"      // pugixml 1.8.1

#include "thirdpart/zlib/unzip.h"        // zlib 1.2.11
#include "thirdpart/zlib/iowin32.h"
#ifdef _WIN64
#pragma comment(lib, "thirdpart/zlib/zlib_x64.lib")
#else
#pragma comment(lib, "thirdpart/zlib/zlib_x86.lib")
#endif

// DuiMini
#include "UIDefine.h"

#include "Utils/UIUtils.h"
#include "Utils/UIRecLog.h"
#include "Utils/UIException.h"
#include "Utils/UIUnzip.h"

#include "Core/UIInterface.h"
#include "Core/Render/UIRender.h"
#include "Core/Resource/UIResource.h"
#include "Core/UIConfig.h"
#include "Core/UISystem.h"
#include "Core/UIDlgBuilder.h"
#include "Core/UIWindow.h"

// control
#include "Control/UIControl.h"
#include "Control/Layout/UIContainer.h"
#include "Control/UIDialog.h"
#include "Control/UIText.h"
#include "Control/UIImage.h"
#include "Control/UIButton.h"
