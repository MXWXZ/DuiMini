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

// Library export/import define
// DO NOT DEFINE [UILIB_EXPORT] IN YOUR MAIN PROGRAM!
// Please add [UILIB_STATIC] as a preprocessor definition.
#ifdef UILIB_STATIC
#   define DUIMINI_API
#else
#   if defined(UILIB_EXPORT)
#       define DUIMINI_API __declspec(dllexport)
#   else
#       define DUIMINI_API __declspec(dllimport)
#   endif
#endif

#define DUIMINI_VERSION _T("1.0")           // UI library version

#define RESOURCE_KIND       _T("ZIP")         // Custom resource type
#define DEFAULT_RESFOLDER   _T("uires")       // Default res folder
#define DEFAULT_RESFILE     _T("uires.xml")   // Default res file

// rapidxml
typedef rapidxml::xml_document<TCHAR> xmldoc;
typedef rapidxml::xml_node<TCHAR>* xmlnode;
typedef rapidxml::xml_attribute<TCHAR>* xmlattr;

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif  // _UNICODE

#pragma warning(disable: 4251)            // warnings when exporting string
