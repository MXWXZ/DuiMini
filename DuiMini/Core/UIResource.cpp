/************************************************************************
Copyright (c) 2017 MXWXZ
************************************************************************/
#include "stdafx.h"
#include "DuiMini.h"
#include "UIResource.h"

namespace DuiMini {
/************************************************************************
静态成员初始化
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
获取资源文件大小
LPCTSTR path：资源文件路径
返回值：-1文件不存在，否则为资源文件大小
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
            UIRecLog::RecordLog(kLoglevel_Error, msg);
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
获取资源文件
BYTE* buf：文件缓冲区（必须先调用GetFileSize获取文件大小并初始化缓冲区，
            函数不检查空间是否足够）
long size：缓冲区大小
返回值：true成功 false失败
注：初始化在GetFileSize中进行，请不要在GetFileSize之前调用本函数！
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
            UIRecLog::RecordLog(kLoglevel_Error, msg);
            return false;
        }
        fread(buf, 1, size, fp);
        fclose(fp);
    } else {
        if (!UIUnzip::UnZipData(zipcache_, buf)) {
            UStr msg;
            msg.Format(_T("Read file \"%s\" in \"%s\" error!"),
                       lastfile_, respath_);
            UIRecLog::RecordLog(kLoglevel_Error, msg);
            return false;
        }
    }
    return true;
}

}   // namespace DuiMini
