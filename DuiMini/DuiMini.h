/************************************************************************
Copyright (c) 2017 MXWXZ
DuiMini公共头文件
************************************************************************/
#pragma once
#ifndef E__CODE_DUIMINI_DUIMINI_DUIMINI_H_
#define E__CODE_DUIMINI_DUIMINI_DUIMINI_H_

// 头文件
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include <assert.h>
#include <locale.h>
#include <time.h>

#include "thirdpart/zlib/unzip.h"        // zlib 1.2.11
#include "thirdpart/zlib/iowin32.h"
#ifdef _WIN64
#pragma comment(lib, "thirdpart/zlib/zlib_x64.lib")
#else
#pragma comment(lib, "thirdpart/zlib/zlib_x86.lib")
#endif

#include "Core/UIDefine.h"                // UI库定义文件
#include "Utils/UIUtils.h"                // UI库公用文件
#include "Utils/UIUnzip.h"                // UI库解压类
#include "Utils/UIRecLog.h"               // UI库日志记录类
#include "Core/UIResource.h"              // UI库资源类
#include "Core/UISystem.h"                // UI库系统类
#include "Core/UIMarkup.h"                // UI库XML解析类

/*
#include "Utils/Utils.h"
#include "Utils/UIDelegate.h"
#include "Core/UIDefine.h"
#include "Core/UIManager.h"
#include "Core/UIBase.h"
#include "Core/UIControl.h"
#include "Core/UIContainer.h"
#include "Core/UIMarkup.h"
#include "Core/UIDlgBuilder.h"
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

#endif  // E__CODE_DUIMINI_DUIMINI_DUIMINI_H_
