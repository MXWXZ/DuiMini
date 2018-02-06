/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:The defination file of UI library
 */
#pragma once

/**
 * Library export/import define
 * DO NOT DEFINE [UILIB_EXPORT] IN YOUR MAIN PROGRAM!
 * Add [UILIB_STATIC] as a preprocessor definition if you use static library.
 */
#ifdef UILIB_STATIC
#   define DUIMINI_API
#else
#   if defined(UILIB_EXPORT)
#       define DUIMINI_API __declspec(dllexport)
#   else
#       define DUIMINI_API __declspec(dllimport)
#   endif
#endif

#define DUIMINI_VERSION _T("1.0")             // UI library version

#define RESOURCE_KIND       _T("ZIP")         // Custom resource type
#define DEFAULT_RESFOLDER   _T("uires")       // Default res folder
#define DEFAULT_RESFILE     _T("uires.xml")   // Default res file
#define DEFAULT_RESIDFILE   _T("resid.xml")   // Default resid file

#define CTRLNAME_CONTROL        _T("control")
#define CTRLNAME_CONTAINER      _T("container")
#define CTRLNAME_DIALOG         _T("dlg")
#define CTRLNAME_IMAGE          _T("img")

// rapidxml
typedef rapidxml::xml_document<TCHAR> xmldoc;
typedef rapidxml::xml_node<TCHAR>* xmlnode;
typedef rapidxml::xml_attribute<TCHAR>* xmlattr;

#define CmpStr(x,y) _tcscmp(x,y) == 0
typedef unsigned char ALPHA;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif  // _UNICODE

#pragma warning(disable: 4251)            // warnings when exporting string
