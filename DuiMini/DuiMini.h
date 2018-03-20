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
#include <utility>

// third-part
#include "thirdpart/rapidxml/rapidxml.hpp"      // rapidxml 1.13
#include "thirdpart/rapidxml/rapidxml_utils.hpp"
#include "thirdpart/rapidxml/rapidxml_print.hpp"

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
