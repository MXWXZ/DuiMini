/************************************************************************
Copyright (c) 2017 MXWXZ
库定义文件
************************************************************************/
#pragma once
#ifndef E__CODE_DUIMINI_DUIMINI_CORE_UIDEFINE_H_
#define E__CODE_DUIMINI_DUIMINI_CORE_UIDEFINE_H_

// LIB导出函数（主程序请不要定义UILIB_EXPORT！静态编译请加上UILIB_STATIC）
#ifdef UILIB_STATIC
#   define DUIMINI_API
#else
#   if defined(UILIB_EXPORT)
#       define DUIMINI_API __declspec(dllexport)
#   else
#       define DUIMINI_API __declspec(dllimport)
#   endif
#endif

#define DUIMINI_VERSION _T("1.0")           // UI库版本

const int kMax_String_Length = MAX_PATH;    // 最大字符串长度
const int kMax_XML_Attributes = 64;         // XML最大属性个数

#define RESOURCE_KIND _T("ZIP")             // 自定义资源类型

#define EXITCODE_SUCCESS 0
#define EXITCODE_FILEFAIL 1

typedef unzFile ZFile;

#endif  // E__CODE_DUIMINI_DUIMINI_CORE_UIDEFINE_H_
