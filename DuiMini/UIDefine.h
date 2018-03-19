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

// TODO: Add new Ctrl
#define CTRLNAME_CONTROL        _T("ctrl")
#define CTRLNAME_CONTAINER      _T("container")
#define CTRLNAME_DIALOG         _T("dlg")
#define CTRLNAME_IMAGE          _T("img")
#define CTRLNAME_BUTTON         _T("btn")
#define CTRLNAME_TEXT           _T("txt")

// rapidxml
typedef rapidxml::xml_document<TCHAR> xmldoc;
typedef rapidxml::xml_node<TCHAR>* xmlnode;
typedef rapidxml::xml_attribute<TCHAR>* xmlattr;

#define CmpStr(x,y) _tcscmp(x,y) == 0
typedef long long LL;
typedef unsigned char ALPHA;
typedef unsigned short SKINID;
typedef unsigned short LANGID;
typedef unsigned short FONTID;
typedef unsigned char COLOR;

#define STAY -1

// TODO: Add new Msg
enum WindowMessage {
    //      Msg                 WPARAM              LPARAM
    kWM_Start_ = 0,    // USELESS

    kWM_MouseEnter,    //               WM_MOUSEMOVE
    kWM_MouseLeave,    //                    ...
    kWM_MouseMove,     //                    ...
    kWM_LButtonDown,   //               WM_LBUTTONDOWN
    kWM_LButtonUp,     //                    ...
    kWM_LButtonClick,  //                    ...
    kWM_LButtonDBClick,//                    ...
    kWM_RButtonDown,   //                    ...
    kWM_RButtonUp,     //                    ...
    kWM_RButtonClick,  //                    ...
    kWM_RButtonDBClick,//                    ...

    kWM_Disable,       //
    kWM_Invisible,     //
    kWM_IgnoreLimit_,  // after this will ignore attribute limit
    kWM_Active,        //
    kWM_Visible,       //

    kWM_SkinChange,    //    former skinid       new skinid
    kWM_LangChange,    //    former langid       new langid

    kWM_End_           // USELESS
};

#define GetStr2WStrLen(str) MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0)
#define Str2WStr(str,wstr,len) MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len)

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif  // _UNICODE

#pragma warning(disable: 4251)            // warnings when exporting string
