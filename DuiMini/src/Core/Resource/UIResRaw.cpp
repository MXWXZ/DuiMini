/**
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include <memory>
#include "Core/Resource/UIResRaw.h"
#include "Utils/UIException.h"

namespace DuiMini {
bool UIResRaw::SetResInfo(const char* info) {
    zippath_ = info;

    long exesize;
    long zipsize;
    unsigned char fileid[2];
    unsigned char resid[] = {0x55, 0x49};

    auto fp = std::shared_ptr<FILE>(fopen(info, "rb"), [](FILE* fp) {
        if (fp)
            fclose(fp);
    });
    if (!fp) {
        UISetError(kEL_Warning, "File %s open error!", info);
        return false;
    }

    fseek(fp.get(), -(long)sizeof(exesize), SEEK_END);
    if (fread(&exesize, sizeof(exesize), 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s exesize read error!", info);
        return false;
    }

    fseek(fp.get(), 0, SEEK_SET);
    auto exe = make_shared_array<unsigned char>(exesize);
    if (fread(exe.get(), exesize, 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s exe section read error!", info);
        return false;
    }

    // varify id
    if (fread(fileid, 2, 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s identifier read error!", info);
        return false;
    }
    if (fileid[0] != resid[0] || fileid[1] != resid[1]) {  // not packed exe
        UISetError(kEL_Warning, "File %s identifier varify error!", info);
        return false;
    }

    // reading zipfile
    if (fread(&zipsize, sizeof(zipsize), 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s zipsize read error!", info);
        return false;
    }
    zipbuf_ = make_shared_array<unsigned char>(zipsize);
    if (fread(zipbuf_.get(), zipsize, 1, fp.get()) != 1) {
        UISetError(kEL_Warning, "File %s zip section read error!", info);
        return false;
    }

    return zipcache_.OpenZip(zipbuf_.get(), zipsize);
}

}  // namespace DuiMini
