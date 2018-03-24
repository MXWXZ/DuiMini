/**
 * Copyright (c) 2018-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2018/03/20
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

// Default string
#define RESOURCE_KIND       _T("ZIP")         // Custom resource type
#define DEFAULT_RESFOLDER   _T("uires")       // Default res folder
#define DEFAULT_RESFILE     _T("uires.xml")   // Default res file
#define DEFAULT_RESIDFILE   _T("resid.xml")   // Default resid file

// control
// TODO: Add new Ctrl
#define CTRLNAME_CONTROL        _T("ctrl")
#define CTRLNAME_CONTAINER      _T("container")
#define CTRLNAME_DIALOG         _T("dlg")
#define CTRLNAME_IMAGE          _T("img")
#define CTRLNAME_BUTTON         _T("btn")
#define CTRLNAME_TEXT           _T("txt")

// third-part
// rapidxml
typedef rapidxml::xml_document<TCHAR> xmldoc;
typedef rapidxml::xml_node<TCHAR>* xmlnode;
typedef rapidxml::xml_attribute<TCHAR>* xmlattr;

// make type beautiful
typedef long long LL;
typedef unsigned char ALPHA;
typedef unsigned short SKINID;
typedef unsigned short LANGID;
typedef unsigned short FONTID;
typedef unsigned char COLOR;
typedef unsigned short BORDER_SIZE;
#define STAY -1

// make function beautiful
#define CmpStr(x, y) _tcscmp(x, y) == 0
#define GetStr2WStrLen(str) MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0)
#define Str2WStr(str, wstr, len) MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len)
#define GetWStr2Strlen(wstr) WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL)
#define WStr2Str(wstr,str,len) WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL)

// enum define
// font string trimming
enum StringTrimming {
    kST_None = 0,
    kST_Ch = 1,
    kST_Word = 2,
    kST_DotCh = 3,
    kST_DotWord = 4,
    kST_DotMid = 5
};
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

// string/wstring
#ifdef _UNICODE
typedef std::wstring tstring;
#define tostring std::to_wstring
#else
typedef std::string tstring;
#define tostring std::to_string
#endif  // _UNICODE

#pragma warning(disable: 4244)            // warnings when converting
#pragma warning(disable: 4251)            // warnings when exporting string
