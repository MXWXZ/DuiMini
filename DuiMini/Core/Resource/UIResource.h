/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/10/17
 *
 * @Description:Resource manager class
 */
#pragma once

namespace DuiMini {
/**
 * resource type
 * kRestype_File:normal file
 * kRestype_Package:zip file
 * kRestype_Self:pe resource
 */
enum Restype {
    kRestype_File = 0,
    kRestype_Package = 1,
    kRestype_RC = 2,
};

/**
 * resource interface
 * get resource data in multiple ways
 */
class DUIMINI_API UIResource {
public:
    ~UIResource();

    static void SetResType(Restype type);
    static Restype GetResType() { return restype_; }

    /**
     * [SAFE]Get resource file size
     * @param    LPCTSTR path: relative path
     * @return   the file size
     */
    static long GetFileSize(LPCTSTR path);

    /**
     * [SAFE]Get resource file
     * @param    LPCTSTR path: relative path
     * @param    BYTE* buf: buffer(please call 'GetFileSize' to get the
     *           size and apply for memory space.)
     * @param    long size: buffer size
     * @return   buf itself
     * WARNING: this function WILL NOT check if there is enough space
     * in the buffer.
     */
    static BYTE* GetFile(LPCTSTR path, BYTE* buf, long size);

    /**
     * Set resource info
     * @param    LPCTSTR info:info passed to res class
     * TIP:For kRestype_File is the root folder of res
     *     For kRestype_Package is the zip full path
     *     For kRestype_RC is the RC id in resource.h
     */
    static void SetResInfo(LPCTSTR info);

    /**
     * Get resource info
     * @return   resource info
     * TIP:For kRestype_File is the root folder of res
     *     For kRestype_Package is the zip full path
     *     For kRestype_RC is the RC id in resource.h
     */
    static LPCTSTR GetResInfo();

private:
    static IUIRes  *resclass_;  // resource class
    static Restype restype_;    // resource type
};

/**
 * Load xml file
 * automatic free space
 */
class DUIMINI_API UIXmlLoader {
public:
    UIXmlLoader();
    explicit UIXmlLoader(LPCTSTR path);
    ~UIXmlLoader();

    bool IsValid() const;

    /**
     * [SAFE]Load xml file
     * @param    LPCTSTR path:xml path(reletive to resource)
     */
    void Loadxml(LPCTSTR path);

    /**
     * Get root node
     * @return   xmlroot object for rootnode
     */
    xmlnode GetRoot() const;

private:
    BYTE* buf;
    xmldoc doc;

    UStr path;
};

}   // namespace DuiMini
