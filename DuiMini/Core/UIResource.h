/************************************************************************
Copyright (c) 2017 MXWXZ
UI资源类
************************************************************************/
#pragma once
#ifndef E__CODE_DUIMINI_DUIMINI_CORE_UIRESOURCE_H_
#define E__CODE_DUIMINI_DUIMINI_CORE_UIRESOURCE_H_

namespace DuiMini {
enum Restype {
    kRestype_File = 0,            // 常规文件
    kRestype_Package = 1,         // 压缩包
    kRestype_Self = 2,            // 自身rc资源
};

class DUIMINI_API UIResource {
 public:
    ~UIResource();
    static long GetFileSize(LPCTSTR path);
    static bool GetFile(BYTE* buf, long size);

    static void SetResType(Restype type) { restype_ = type; }
    static Restype GetResType() { return restype_; }
    // for type0&1
    static void SetResPath(LPCTSTR path) { respath_ = path; }
    static LPCTSTR GetResPath() { return respath_; }
    // for type2
    static void SetResID(UINT id) { resid_ = id; }
    static UINT GetResID() { return resid_; }

 protected:
    static UStr lastfile_;
    static UINT resid_;
    static Restype restype_;
    static UStr respath_;
    static ZFile zipcache_;
};

}   // namespace DuiMini

#endif  // E__CODE_DUIMINI_DUIMINI_CORE_UIRESOURCE_H_
