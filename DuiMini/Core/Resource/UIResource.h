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
 * kRT_File:normal file
 * kRT_Package:zip file
 * kRT_RC:rc resource
 */
enum ResType {
    kRT_File = 0,
    kRT_Package = 1,
    kRT_RC = 2,
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
    TBYTE* buffer_ = nullptr;
    xmldoc doc_;

    UStr relativepath_;
};


/**
* File type
* kFT_XML:.xml file
* kFT_PIC:picture file
*/
enum FileType {
    kFT_XML,
    kFT_PIC,
};

struct DUIMINI_API LoadedRes {
    ~LoadedRes() {
        switch (type_) {
        case kFT_XML:
            delete reinterpret_cast<UIXmlLoader*>(res_);
            break;
        case kFT_PIC:
            delete reinterpret_cast<UIRenderImage*>(res_);
            break;
        }
        res_ = nullptr;
    }
    FileType type_;
    UStr path_;
    LPVOID res_ = nullptr;
    UINT using_ = 0;
};

typedef std::vector<LoadedRes*> UIResItem;
typedef std::vector<LoadedRes*>::iterator UIResItemIt;
typedef std::vector<LoadedRes*>::const_iterator CUIResItemIt;

/**
 * resource interface
 * get resource data in multiple ways
 */
class DUIMINI_API UIResource {
public:
    ~UIResource();

public:
    /**
     * Load resource only ONCE
     * @param    FileType v_type: res type
     * @param    LPCTSTR v_path: res path
     * @param    bool* v_result: whether load success
     * @return   loaded buffer
     * @ Res will be load if there is no other copy exist,otherwise will return
     * existed copy.
     * @ This function will allocate itself, you MUST call ReleaseRes to release
     * space if you want.DO NOT use delete by yourself(may affect other copies)
     * @ Be careful what you do to buffer will affect other copies!
     */
    static LPVOID LoadRes(FileType v_type, LPCTSTR v_path, bool* v_result = nullptr);

    // Release
    static void ReleaseResByName(LPCTSTR v_path);
    static void ReleaseRes(LPVOID v_res);

public:
    static void SetResType(ResType v_type);
    static ResType GetResType();

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
    static ResType restype_;    // resource type
    static UIResItem res_item_; // loaded res
};

}   // namespace DuiMini
