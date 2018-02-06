/**
 * Copyright (c) 2017-2050
 * All rights reserved.
 *
 * @Author:MXWXZ
 * @Date:2017/12/19
 *
 * @Description:
 */
#include "stdafx.h"
#include "UIRenderGDIP.h"

namespace DuiMini {
ULONG_PTR UIRenderGDIP::gdiplus_token = 0;

UIRenderGDIP::UIRenderGDIP() {}

UIRenderGDIP::~UIRenderGDIP() {
    DeleteDC(background_);
    DeleteObject(bg_bitmap_);
    background_ = NULL;
    bg_bitmap_ = NULL;
}

bool UIRenderGDIP::GlobalInit() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    if (Gdiplus::GdiplusStartup(&gdiplus_token,
                                &gdiplusStartupInput, NULL) != Gdiplus::Ok) {
        UISetError(kLL_Warning, kEC_ThirdPartFail,
                   _T("GDI+ GdiplusStartup fail!"));
        return false;
    }
    return true;
}

bool UIRenderGDIP::GlobalRelease() {
    Gdiplus::GdiplusShutdown(gdiplus_token);
    return true;
}

bool UIRenderGDIP::Paint(UIWindow* v_wnd) {
    if (!v_wnd)
        return false;
    HWND hwnd = v_wnd->GetHWND();
    RECT rcwindow;
    GetWindowRect(hwnd, &rcwindow);
    SIZE sizewindow;
    UIDialog* dlg = v_wnd->GetDlgBuilder()->GetCtrlRoot();

    RECT pos = dlg->GetPos();
    sizewindow.cx = pos.right - pos.left;
    sizewindow.cy = pos.bottom - pos.top;

    HDC hdc = GetDC(hwnd);
    BITMAPINFOHEADER bmp_infoheader = { 0 };
    int nBytesPerLine = ((sizewindow.cx * 32 + 31) & (~31)) >> 3;
    bmp_infoheader.biSize = sizeof(BITMAPINFOHEADER);
    bmp_infoheader.biWidth = sizewindow.cx;
    bmp_infoheader.biHeight = sizewindow.cy;
    bmp_infoheader.biPlanes = 1;
    bmp_infoheader.biBitCount = 32;
    bmp_infoheader.biCompression = BI_RGB;
    bmp_infoheader.biClrUsed = 0;
    bmp_infoheader.biSizeImage = nBytesPerLine * sizewindow.cy;
    if (background_ == NULL) {
        background_ = CreateCompatibleDC(hdc);
        PVOID bits = NULL;
        bg_bitmap_ = CreateDIBSection(NULL, (PBITMAPINFO)&bmp_infoheader,
                                      DIB_RGB_COLORS, &bits, NULL, 0);
        if (bg_bitmap_ == NULL)
            return false;
        SelectObject(background_, bg_bitmap_);

        graph_ = new Gdiplus::Graphics(background_);
        bg_rect_ = dlg->PaintBackground();
        graph_->ReleaseHDC(background_);
        delete graph_;
        graph_ = nullptr;
    }
    HDC hdctmp = CreateCompatibleDC(hdc);
    PVOID bits = NULL;
    HBITMAP bmptmp = CreateDIBSection(NULL, (PBITMAPINFO)&bmp_infoheader,
                                        DIB_RGB_COLORS, &bits, NULL, 0);
    HGDIOBJ bmpobj = SelectObject(hdctmp, bmptmp);
    POINT ptsrc = { 0, 0 };
    BLENDFUNCTION blendfunc;
    blendfunc.BlendOp = 0;
    blendfunc.BlendFlags = 0;
    blendfunc.AlphaFormat = 1;
    blendfunc.SourceConstantAlpha = v_wnd->GetBGAlpha();
    AlphaBlend(hdctmp, 0, 0, sizewindow.cx, sizewindow.cy,
               background_, bg_rect_.left, bg_rect_.top,
               bg_rect_.right - bg_rect_.left,
               bg_rect_.bottom - bg_rect_.top, blendfunc);

    graph_ = new Gdiplus::Graphics(hdctmp);
    v_wnd->GetDlgBuilder()->GetCtrlRoot()->Paint();
    graph_->ReleaseHDC(hdctmp);
    delete graph_;
    graph_ = nullptr;

    POINT wndpos = { rcwindow.left, rcwindow.top };
    blendfunc.SourceConstantAlpha = v_wnd->GetAlpha();
    HMODULE funinst = LoadLibrary(_T("User32.DLL"));
    typedef BOOL(WINAPI *FUNC)(HWND, HDC, POINT*, SIZE*, HDC, POINT*,
                                 COLORREF, BLENDFUNCTION*, DWORD);
    FUNC UpdateLayeredWindow;
    UpdateLayeredWindow = (FUNC)GetProcAddress(funinst, "UpdateLayeredWindow");
    if (!UpdateLayeredWindow(hwnd, hdc, &wndpos, &sizewindow, hdctmp,
                             &ptsrc, 0, &blendfunc, ULW_ALPHA))
        return false;

    SelectObject(hdctmp, bmpobj);

    DeleteObject(funinst);
    DeleteObject(bmpobj);
    DeleteObject(bmptmp);
    DeleteDC(hdctmp);
    DeleteDC(hdc);
    return true;
}

bool UIRenderGDIP::RedrawBackground() {
    DeleteObject(background_);
    background_ = nullptr;
    return true;
}

bool UIRenderGDIP::DrawImage(UIRenderImage* v_img, int v_left,
                             int v_top, int v_width, int v_height) {
    if (!graph_)
        return false;
    if (graph_->DrawImage((Gdiplus::Image*)v_img->GetInterface(),
                          v_left, v_top, v_width, v_height) != Gdiplus::Ok) {
        UISetError(kLL_Warning, kEC_ThirdPartFail,
                   _T("GDI+ DrawImage fail!"));
        return false;
    }
    return true;
}

////////////////////////////////////////

UIRenderImageGDIP::UIRenderImageGDIP() {}

UIRenderImageGDIP::UIRenderImageGDIP(LPCTSTR v_path) {
    Load(v_path);
}

UIRenderImageGDIP::~UIRenderImageGDIP() {
    Release();
}

bool UIRenderImageGDIP::Load(LPCTSTR v_path) {
    long buflen = UIResource::GetFileSize(v_path);
    HGLOBAL mem = GlobalAlloc(GHND, buflen);
    BYTE* buffer = reinterpret_cast<BYTE*>(GlobalLock(mem));
    UIResource::GetFile(v_path, buffer, buflen);
    GlobalUnlock(mem);
    IStream *stream = nullptr;
    if (CreateStreamOnHGlobal(buffer, TRUE, &stream) != S_OK) {
        UISetError(kLL_Warning, kEC_ThirdPartFail,
                   _T("GDI+ CreateStreamOnHGlobal fail!"));
        return false;
    }
    img_ = Gdiplus::Image::FromStream(stream);
    stream->Release();
    return true;
}

bool UIRenderImageGDIP::Release() {
    delete img_;
    img_ = nullptr;
    return true;
}

void* UIRenderImageGDIP::GetInterface() const {
    return reinterpret_cast<void*>(img_);
}

UINT UIRenderImageGDIP::GetWidth() const {
    if (!img_)
        return 0;
    return img_->GetWidth();
}

UINT UIRenderImageGDIP::GetHeight() const {
    if (!img_)
        return 0;
    return img_->GetHeight();
}
}    // namespace DuiMini
