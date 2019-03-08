/**
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include <memory>
#include "Core/Resource/UIResFile.h"
#include "Utils/UIException.h"

namespace DuiMini {
UIResFile::UIResFile() {}

UIResFile::~UIResFile() {}

UIResFile::UIResFile(const char* info) { SetResInfo(info); }

bool UIResFile::SetResInfo(const char* info) {
    path_ = info;
    return true;
}

UIStr UIResFile::GetResInfo() const { return path_; }

bool UIResFile::GetFile(const char* path, void* buffer, long size) {
    UIStr filepath;
    filepath.Format("%s/%s", path_.GetData(), path);

    auto fp =
        std::shared_ptr<FILE>(fopen(filepath.GetData(), "rb"), [](FILE* fp) {
            if (fp)
                fclose(fp);
        });
    if (!fp) {
        UISetError(kEL_Warning, "File %s open error!", path);
        return false;
    }
    if (fread(buffer, size, 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s read error!", filepath.GetData());
        return false;
    }
    return true;
}

long UIResFile::GetFileSize(const char* path) {
    UIStr filepath;
    filepath.Format("%s/%s", path_.GetData(), path);

    auto fp =
        std::shared_ptr<FILE>(fopen(filepath.GetData(), "rb"), [](FILE* fp) {
            if (fp)
                fclose(fp);
        });
    if (!fp) {
        UISetError(kEL_Warning, "File %s open error!", path);
        return -1;
    }
    fseek(fp.get(), 0, SEEK_END);
    return ftell(fp.get());
}

}  // namespace DuiMini
