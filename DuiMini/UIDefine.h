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

// message
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

    kWM_IgnoreLimit_,  // after this will ignore attribute limit

    kWM_Disable,       //
    kWM_Invisible,     //
    kWM_Active,        //
    kWM_Visible,       //

    kWM_SkinChange,    //    former skinid       new skinid
    kWM_LangChange,    //    former langid       new langid

    kWM_End_           // USELESS
};

// make type beautiful
typedef long long LL;
typedef unsigned short ALPHA;
typedef unsigned short CFGID;
typedef unsigned short COLOR;
typedef unsigned int FILESIZE;
#define STAY -1

// string/wstring
#ifdef _UNICODE
typedef std::wstring tstring;
#define tostring std::to_wstring
#else
typedef std::string tstring;
#define tostring std::to_string
#endif  // _UNICODE

#define shared_ptr std::shared_ptr
#define make_shared std::make_shared

typedef shared_ptr<char[]> shared_ptr_char;
typedef shared_ptr<wchar_t[]> shared_ptr_wchar;
typedef shared_ptr<TCHAR[]> shared_ptr_tchar;
typedef shared_ptr<BYTE[]> shared_ptr_byte;

// make function beautiful
#define CmpStr(x, y) _tcscmp(x, y) == 0

#pragma warning(disable: 4244)            // warnings when converting
#pragma warning(disable: 4267)            // warnings when converting
#pragma warning(disable: 4251)            // warnings when exporting string
