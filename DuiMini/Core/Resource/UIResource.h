/**
* Copyright (c) 2018-2050
* All rights reserved.
*
* @Author:MXWXZ
* @Date:2018/03/20
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
            delete (UIXmlLoader*)res_;
            break;
        case kFT_PIC:
            delete (UIRenderImage*)res_;
            break;
        }
        res_ = nullptr;
    }
    FileType type_;
    UStr path_;
    LPVOID res_ = nullptr;
    UINT using_ = 0;
};

typedef std::vector<shared_ptr<LoadedRes>> UIResItem;
typedef UIResItem::iterator UIResItemIt;
typedef UIResItem::const_iterator CUIResItemIt;

/**
 * resource interface
 * get resource data in multiple ways
 */
class DUIMINI_API UIResource {
public:
    /**
     * Load resource only ONCE
     * @param    FileType v_type: res type
     * @param    LPCTSTR v_path: res path
     * @return   loaded buffer
     * @ Res will be load if there is no other copy exist,otherwise will return
     * existed copy.
     * @ This function will allocate itself, you MUST call ReleaseRes to release
     * space if you want.DO NOT use delete by yourself(may affect other copies)
     * @ Be careful what you do to buffer will affect other copies!
     */
    static LPVOID LoadRes(FileType v_type, LPCTSTR v_path);

    // Release
    static void ReleaseResByName(LPCTSTR v_path);
    static void ReleaseRes(LPVOID v_res);

public:
    static void SetResType(ResType v_type);
    static ResType GetResType();

    /**
     * Get resource file size
     * @param    LPCTSTR v_path: relative path
     * @return   the file size,-1 for failed
     */
    static FILESIZE GetFileSize(LPCTSTR v_path);

    /**
     * Get resource file
     * @param    LPCTSTR v_path: relative path
     * @param    BYTE* v_buffer: buffer(please call 'GetFileSize' to get the
     *           size and apply for memory space.)
     * @param    long v_size: buffer size
     * @return   true for success
     * WARNING: this function WILL NOT check if there is enough space
     * in the buffer.
     */
    static bool GetFile(LPCTSTR v_path, BYTE* v_buffer, long v_size);

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
    static CUStr GetResInfo();

private:
    static shared_ptr<IUIRes> resclass_;   // resource class
    static ResType restype_;                // resource type
    static UIResItem res_item_;             // loaded res
};

}   // namespace DuiMini
