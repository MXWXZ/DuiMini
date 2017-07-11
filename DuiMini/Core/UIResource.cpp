/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIResource.h"

namespace DuiMini {
/************************************************************************
Initialize static member
************************************************************************/
UINT UIResource::resid_ = 0;
UStr UIResource::lastfile_ = _T("");
UStr UIResource::respath_ = _T("");
ZFile UIResource::zipcache_ = NULL;
Restype UIResource::restype_ = kRestype_File;

UIResource::~UIResource() {
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
}

/************************************************************************
Set resource type
Restype type: resource type
            kRestype_File      normal file
            kRestype_Package   zip file
            kRestype_Self      .rc resource
************************************************************************/
void UIResource::SetResType(Restype type) {
    if (zipcache_ != NULL)
        UIUnzip::CloseZip(zipcache_);
    resid_ = 0;
    lastfile_ = _T("");
    respath_ = _T("");
    zipcache_ = NULL;
    restype_ = type;
}

/************************************************************************
Get resource file size
LPCTSTR path: relative path
ret value: -1 when file do not exist or damaged
           otherwise is the file size
************************************************************************/
long UIResource::GetFileSize(LPCTSTR path) {
    lastfile_ = path;
    if (restype_ == kRestype_File) {
        UStr tmppath;
        tmppath.Format(_T("%s\\%s"), respath_, path);

        FILE* fp;
        fp = _tfopen(tmppath, _T("rb"));
        if (fp == NULL) {
            UStr msg;
            msg.Format(_T("File \"%s\" doesn't exist!"), tmppath);
            UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            return -1;
        }
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fclose(fp);
        return size;
    } else if (restype_ == kRestype_Package) {
        if (zipcache_ == NULL) {
            zipcache_ = UIUnzip::OpenZip(respath_);
            if (zipcache_ == NULL) {
                UStr msg;
                msg.Format(_T("Zip file \"%s\" doesn't exist!"), respath_);
                UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            }
        }
        return UIUnzip::LocateZipItem(zipcache_, path);
    } else {
        if (zipcache_ == NULL) {
            HRSRC srcsys = FindResource(UISystem::GetInstance(),
                                        MAKEINTRESOURCE(resid_), _T("ZIP"));
            HGLOBAL globalsys = LoadResource(UISystem::GetInstance(), srcsys);
            LPVOID file = LockResource(globalsys);
            TCHAR tmppath[MAX_PATH];
            GetTempPath(MAX_PATH, tmppath);
            TCHAR tmpfile[MAX_PATH];
            GetTempFileName(tmppath, _T("~ui"), 563, tmpfile);

            FILE* fp;
            fp = _tfopen(tmpfile, _T("wb"));
            if (fp == NULL) {
                UStr msg;
                msg.Format(_T("Temp path permission denied!"), tmppath);
                UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            }
            fwrite(file, (UINT)SizeofResource(UISystem::GetInstance(),
                                              srcsys), 1, fp);
            fclose(fp);
            UnlockResource(globalsys);
            FreeResource(globalsys);
            respath_ = tmpfile;

            zipcache_ = UIUnzip::OpenZip(respath_);
            if (zipcache_ == NULL) {
                UStr msg;
                msg.Format(_T("Zip file \"%s\" doesn't exist!"), respath_);
                UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            }
        }
        return UIUnzip::LocateZipItem(zipcache_, path);
    }
}

/************************************************************************
Get resource file
BYTE* buf: buffer(please call 'GetFileSize' to get the
            size and apply for memory space.)
long size: buffer size
ret value: false - fail     true - succeed
WARNING: this function MUST be used after calling 'GetFileSize' and
         WILL NOT check if there is enough space in the buffer.
************************************************************************/
bool UIResource::GetFile(BYTE* buf, long size) {
    if (restype_ == kRestype_File) {
        UStr tmppath;
        tmppath.Format(_T("%s\\%s"), respath_, lastfile_);

        FILE* fp;
        fp = _tfopen(tmppath, _T("rb"));
        if (fp == NULL) {
            UStr msg;
            msg.Format(_T("File \"%s\" doesn't exist!"), tmppath);
            UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            return false;
        }
        fread(buf, 1, size, fp);
        fclose(fp);
    } else {
        if (!UIUnzip::UnZipData(zipcache_, buf)) {
            UStr msg;
            msg.Format(_T("Read file \"%s\" in \"%s\" error!"),
                       lastfile_, respath_);
            UIRecLog::RecordLog(kLoglevel_Error, msg, EXITCODE_FILEFAIL);
            return false;
        }
    }
    return true;
}

}   // namespace DuiMini
