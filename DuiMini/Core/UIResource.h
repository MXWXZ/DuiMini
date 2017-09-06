// ****************************************
// Copyright (c) 2017-2050
// All rights reserved.
//
// Author:MXWXZ
// Date:2017/09/05
//
// Description:Resource manager class
// ****************************************
#pragma once

namespace DuiMini {
// ****************************************
// resource type
// kRestype_File:normal file
// kRestype_Package:zip file
// kRestype_Self:pe resource
// ****************************************
enum Restype {
    kRestype_File = 0,
    kRestype_Package = 1,
    kRestype_Self = 2,
};

// ****************************************
// resource interface
// get resource data in multiple ways
// ****************************************
class DUIMINI_API UIResource {
public:
    ~UIResource();

    // ****************************************
    // Get resource file size
    // -param    LPCTSTR path: relative path
    // -return   -1 when file do not exist or damaged,otherwise is the file size
    // ****************************************
    static long GetFileSize(LPCTSTR path);

    // ****************************************
    // Get resource file
    // -param    BYTE* buf: buffer(please manually call 'GetFileSize' to get the
    //           size and apply for memory space.)
    // -param    long size: buffer size
    // -return   false - fail     true - succeed
    // WARNING: this function MUST be used after calling 'GetFileSize' and
    // WILL NOT check if there is enough space in the buffer.
    // ****************************************
    static bool GetFile(BYTE* buf, long size);

    // ****************************************
    // Set resource type
    // -param    Restype type: resource type
    // ****************************************
    static void SetResType(Restype type);

    // ****************************************
    // Get resource type
    // -return   current Restype enum
    // ****************************************
    static Restype GetResType() { return restype_; }

    // ****************************************
    // Set resource path for restype File&Zip file
    // -param    LPCTSTR path:folder or zip path
    // this function is INVALID when restype is kRestype_Self
    // ****************************************
    static void SetResPath(LPCTSTR path) { respath_ = path; }

    // ****************************************
    // Get current resource path
    // -return   current resource path
    // this function is INVALID when restype is kRestype_Self
    // ****************************************
    static LPCTSTR GetResPath() { return respath_; }

    // ****************************************
    // Set resource path for restype PE res
    // -param    UINT id:resource id
    // this function is INVALID when restype is kRestype_File
    // or kRestype_Package
    // ****************************************
    static void SetResID(UINT id) { resid_ = id; }

    // ****************************************
    // Get current resource id
    // -return   current resource id
    // this function is INVALID when restype is kRestype_File
    // or kRestype_Package
    // ****************************************
    static UINT GetResID() { return resid_; }

protected:
    static UStr lastfile_;      // last file calling GetFileSize
    static UINT resid_;         // resource id
    static Restype restype_;    // resource type
    static UStr respath_;       // resource path
    static ZFile zipcache_;     // cached opening zip pointer
};

}   // namespace DuiMini
