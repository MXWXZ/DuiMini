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
 * kFile:normal file
 * kPackage:zip file
 * kRC:rc resource
 */
enum Restype {
    kFile = 0,
    kPackage = 1,
    kRC = 2,
};

/**
 * resource interface
 * get resource data in multiple ways
 */
class DUIMINI_API UIResource {
public:
    ~UIResource();

    static void SetResType(Restype v_type);
    static Restype GetResType();

    /**
     * Get resource file size
     * @param    LPCTSTR v_path: relative path
     * @return   the file size
     */
    static long GetFileSize(LPCTSTR v_path);

    /**
     * Get resource file
     * @param    LPCTSTR v_path: relative path
     * @param    BYTE* v_buffer: buffer(please call 'GetFileSize' to get the
     *           size and apply for memory space.)
     * @param    long v_size: buffer size
     * @return   buf itself
     * WARNING: this function WILL NOT check if there is enough space
     * in the buffer.
     */
    static BYTE* GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size);

    /**
     * Set resource info
     * @param    LPCTSTR info:info passed to res class
     * TIP:For kRestype_File is the root folder of res
     *     For kRestype_Package is the zip full path
     *     For kRestype_RC is the RC id in resource.h
     */
    static void SetResInfo(LPCTSTR v_info);

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
    explicit UIXmlLoader(LPCTSTR v_path);
    ~UIXmlLoader();

    /**
     * Load xml file
     * @param    LPCTSTR path:xml path(relative to resource)
     */
    void Loadxml(LPCTSTR v_path);

    /**
     * Get root node
     * @return   xmlroot object for rootnode
     */
    xmlnode GetRoot() const;

private:
    BYTE* buffer_ = nullptr;
    xmldoc doc_;

    UStr relativepath_;
};

}   // namespace DuiMini
