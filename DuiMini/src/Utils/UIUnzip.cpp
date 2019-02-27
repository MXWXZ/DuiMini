/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/23
 */
#include "Utils/UIUnzip.h"
#include "Utils/UIException.h"

namespace DuiMini {
UIUnzip::UIUnzip() { memset(&fp_, 0, sizeof(fp_)); }

UIUnzip::~UIUnzip() { CloseZip(); }

bool UIUnzip::OpenZip(const char* path) {
    CloseZip();
    if (!mz_zip_reader_init_file(&fp_, path,
                                 MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
        UISetError(kEL_Warning, "mz_zip_reader_init_file error! Return: %s",
                   mz_zip_get_error_string(mz_zip_get_last_error(&fp_)));
        return false;
    }

    inited_ = true;
    return true;
}

bool UIUnzip::OpenZip(void* buffer, size_t size) {
    CloseZip();
    if (!mz_zip_reader_init_mem(&fp_, buffer, size,
                                MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
        UISetError(kEL_Warning, "mz_zip_reader_init_mem error! Return:%s",
                   mz_zip_get_error_string(mz_zip_get_last_error(&fp_)));
        return false;
    }

    inited_ = true;
    return true;
}

bool UIUnzip::IsInited() const { return inited_; }

void UIUnzip::CloseZip() {
    if (inited_) {
        mz_zip_reader_end(&fp_);
        inited_ = false;
    }
}

long UIUnzip::GetFileSize(const char* path) {
    mz_zip_archive_file_stat stats;
    auto index = mz_zip_reader_locate_file(&fp_, path, NULL, 0);
    if (index < 0) {
        UISetError(kEL_Warning, "mz_zip_reader_locate_file error! Return: %s",
                   mz_zip_get_error_string(mz_zip_get_last_error(&fp_)));
        return -1;
    }
    if (!mz_zip_reader_file_stat(&fp_, (mz_uint)index, &stats)) {
        UISetError(kEL_Warning, "mz_zip_reader_file_stat error! Return: %s",
                   mz_zip_get_error_string(mz_zip_get_last_error(&fp_)));
        return -1;
    }
    return (long)stats.m_uncomp_size;  // no need to support large file
}

bool UIUnzip::GetFile(const char* path, void* buffer, long size) {
    if (!mz_zip_reader_extract_file_to_mem(&fp_, path, buffer, size, 0)) {
        UISetError(kEL_Warning,
                   "mz_zip_reader_extract_file_to_mem error! Return: %s",
                   mz_zip_get_error_string(mz_zip_get_last_error(&fp_)));
        return false;
    }
    return true;
}

}  // namespace DuiMini
