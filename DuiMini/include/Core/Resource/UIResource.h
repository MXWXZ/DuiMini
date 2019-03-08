/** @file
 * Resource manager.
 * Manage the resource, decide how to load resources and make it auto-deleted.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_CORE_RESOURCE_UIRESOURCE_H_
#define DUI_CORE_RESOURCE_UIRESOURCE_H_

#include <vector>
#include <memory>
#include "UIDefine.h"
#include "Utils/UIUtils.h"
#include "Core/UIInterface.h"
#include "Utils/UIException.h"

namespace DuiMini {
/**
 * Resource type.
 */
enum ResType {
    kRT_None = 0,
    kRT_File,     //!< normal file
    kRT_Package,  //!< zip file
    kRT_Raw,      //!< raw resource
};

/**
 * Resource interface.
 * Get resource data in multiple ways.
 */
class DUIMINI_API UIResource {
public:
    /**
     * Load resource only ONCE.
     * @param	path: res path
     * @return	loaded class pointer, nullptr for error
     * @note    Res will be load if there is no other copy exist,otherwise will
     * return existed copy.
     * @warning Space will be freed automatically, do NOT delete by yourself. Be
     * careful, what you do to pointed class will affect other copies!
     */
    template <typename T>
    static std::shared_ptr<T> LoadRes(const char* path) {
        static_assert(std::is_base_of<IUILoadFile, T>::value,
                      "class should inherit from IUILoadFile");

        auto it = resitem_.find(path);
        std::shared_ptr<void> filedata;
        long filesize;
        if (it == resitem_.end()) {  // not find
            filesize = GetFileSize(path);
            if (filesize == -1)
                return nullptr;
            filedata = make_shared_array<unsigned char>(filesize);
            if (!GetFile(path, filedata.get(), filesize))
                return nullptr;
            auto tmp = std::make_shared<LoadedRes>();
            tmp->res_ = filedata;
            tmp->size_ = filesize;
            tmp->using_ = 1;
            resitem_[path] = tmp;
        } else {
            filedata = it->second->res_;
            filesize = it->second->size_;
            ++(it->second->using_);
        }

        IUILoadFile* obj = new T();
        obj->SetPath(path);
        if (!obj->LoadFile(filedata.get(), filesize))
            return nullptr;

        return std::move(std::shared_ptr<T>((T*)obj, DeleteRes<T>));
    }

    /**
     * Set resource mode.
     * @param   type: resource type
     * @param   info: info passed to res class
     * @note    For kRT_File is the root folder of res
     *          For kRT_Package is the zip path
     *          For kRT_Raw is the packed executable file path
     * @see     GetResInfo
     */
    static void SetResMode(ResType type, const char* info);

    static ResType GetResType() { return restype_; }
    static UIStr GetResInfo();

private:
    static bool GetFile(const char* path, void* buffer, long size);
    static long GetFileSize(const char* path);

    /**
     * Deleter for shared_ptr.
     * @param	pointer: deleter param
     * @warning	Do NOT call it by yourself!
     */
    template <typename T>
    static void DeleteRes(T* pointer) {
        auto path = ((IUILoadFile*)pointer)->GetPath();
        auto it = resitem_.find(path);
        if (it == resitem_.end()) {
            UISetError(kEL_Warning, "Delete res %s error! Not exist!",
                       path.GetData());
        } else {
            --(it->second->using_);
            if (it->second->using_ == 0)
                resitem_.erase(it);
        }
        delete pointer;
    }

private:
    /**
     * Cache loaded resource.
     * Free space and any other things when the resource is not being used by
     * any object.
     */
    struct LoadedRes {
        std::shared_ptr<void> res_;  //!< loaded T pointer
        long size_;                  //!< file size
        uint using_ = 0;  //!< using count, will be released if equal 0
    };
    typedef std::map<UIStr, std::shared_ptr<LoadedRes>> UIResItem;

    static std::shared_ptr<IUIRes> resclass_;  //!< resource class
    static ResType restype_;                   //!< resource type
    static UIResItem resitem_;                 //!< loaded res
};
}  // namespace DuiMini

#endif  // !DUI_CORE_RESOURCE_UIRESOURCE_H_
