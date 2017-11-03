/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:
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
#include "Core/UIDefine.h"
#include "Utils/UIUtils.h"
#include "Utils/UIRecLog.h"
#include "Utils/UIException.h"
#include "Utils/UIUnzip.h"
#include "Core/UIInterface.h"
#include "Core/Resource/UIResource.h"
#include "Core/UISystem.h"

//#include "Core/UIManager.h"
//#include "Core/UIDlgBuilder.h"

/*
#include "Utils/Utils.h"
#include "Utils/UIDelegate.h"
#include "Core/UIDefine.h"
#include "Core/UIBase.h"
#include "Core/UIControl.h"
#include "Core/UIContainer.h"
#include "Core/UIMarkup.h"
#include "Core/UIRender.h"
#include "Utils/WinImplBase.h"


#include "Layout/UIVerticalLayout.h"
#include "Layout/UIHorizontalLayout.h"
#include "Layout/UITileLayout.h"
#include "Layout/UITabLayout.h"
#include "Layout/UIChildLayout.h"

#include "Control/UIList.h"
#include "Control/UICombo.h"
#include "Control/UIScrollBar.h"
#include "Control/UITreeView.h"

#include "Control/UILabel.h"
#include "Control/UIText.h"
#include "Control/UIEdit.h"

#include "Control/UIButton.h"
#include "Control/UIOption.h"
#include "Control/UICheckBox.h"

#include "Control/UIProgress.h"
#include "Control/UISlider.h"

#include "Control/UIRichEdit.h"
#include "Control/UIDateTime.h"

#include "Control/UIActiveX.h"
#include "Control/UIWebBrowser.h"
#include "Control/UIGifAnim.h"
*/
