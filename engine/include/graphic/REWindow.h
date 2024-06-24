﻿//  **************************************
//  File:        REWindow.h
//  ***************************************
#ifndef REWindow_DEFINED
#define REWindow_DEFINED
#include "SkiaRESurface.h"
#include <vector>

//#define USE_DDRAW
// 
void ShowRefreshingBound(kn_bool bShow);

#ifdef WIN32
class API REWinDeviceSurface: public RESurface
{
public:
	REWinDeviceSurface(HDC,kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~REWinDeviceSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);

protected:
	HDC	m_hdc;
	BITMAPINFO* m_p_bmi;
	kn_int m_x_dc;
	kn_int m_y_dc;
};

class API RELayerWinDeviceSurface: public REWinDeviceSurface
{
public:
	RELayerWinDeviceSurface(HWND, HDC,kn_int width, kn_int height);

	// 
	virtual ~RELayerWinDeviceSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);

protected:
	HWND m_hwnd;
	HBITMAP m_hbitmap;
	HDC	 m_mem_dc;

};

#ifdef USE_DDRAW
class API REDDrawSurface: public RESurface
{
public:
	REDDrawSurface(HWND,kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~REDDrawSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);

private:
	HWND m_hwnd;
	HDC	m_hdc;
	kn_int m_x_dc;
	kn_int m_y_dc;
};
#endif  //USE_DDRAW

//#endif  //WIN32
class CGLEvn;

class API REGlSurface: public RESurface
{
public:
	REGlSurface(HDC, kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~REGlSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);
	void setGLEnv(CGLEvn*  gl);
	virtual void preDraw();
protected:
	HDC	m_hdc;
	kn_byte* m_p_data;
	CGLEvn* m_gl_env;
	UINT m_texture_id;
	float m_vt[12];
	float m_uv[8];
};

#if 0
// add by boy for GLES2.0 --- 2015.5
class KGlesEnv;
class API REGLESSurface: public RESurface
{
public:
	REGLESSurface(kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~REGLESSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);
	void setGLESEnv(KGlesEnv* gles);
	virtual void preDraw();
protected:
	kn_byte* m_p_data;
	KGlesEnv* m_gles_env;
	UINT m_texture_id;
	float m_vt[12];
	float m_uv[8];
	bool m_isSetEnv;
};
/////////////////////////////////////////////
#endif

// add by boy for skia-gpu draw --- 2015.6.5
#ifdef SKIAGL
#include "core/SkBitmap.h"   
#include "core/SkDevice.h"   
#include "core/SkPaint.h"  
#include "core/SkStream.h"
#include "core/SkImage.h"
#include "core/SkImageTypes.h"
#include "core/SkImageDecoder.h"
#include "core/SkImageEncoder.h"
#include "core/SkSurface.h"
#include "core/SkTypeface.h"
#include "core/SkStrokeRec.h"
#include "core/SkPicture.h"
#include "utils/SkCamera.h"
#include "views/SkApplication.h"
#include "views/SkOSWindow_Win.h"
#include "gpu/SkGpuDevice.h"
#include "core/SkBitmapDevice.h"
#include "gpu/GrContext.h"
#include "gpu/gl/SkGLContext.h"
#include "gpu/GrContextFactory.h"
#include "gpu/gl/GrGLInterface.h"

class API RESkiaGLSurface: public RESurface
{
public:
	RESkiaGLSurface(HWND wnd, kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~RESkiaGLSurface() ;  

	// 
	virtual void Flip(LSTRECT &lst_rect);
	virtual kn_bool Initialize(kn_dword width, kn_dword height, REBitmap::Config colorFormat);
	virtual void preDraw();
	virtual void Release();
 
protected:
	bool m_isSetEnv;
	HWND m_wnd;
	SkOSWindow *m_SkWind;
	GrContext *m_context;
	SkSurface *m_surface;
	const GrGLInterface* m_interface;
	GrRenderTarget* m_renderTarget;
	kn_int m_width;
	kn_int m_height;
};
#endif //SKIAGL
/////////////////////////////////////////////

class API REGLLayerWinDeviceSurface: public REGlSurface
{
public:
	REGLLayerWinDeviceSurface(HWND, HDC,kn_int width, kn_int height);

	// 
	virtual ~REGLLayerWinDeviceSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);

	HDC getMemDC();
protected:
	BYTE *m_buffer;
	HWND m_hwnd;
	HBITMAP m_hbitmap;
	HDC	 m_mem_dc;
	BYTE*	 m_p_mem_data;
	BITMAPINFO* m_p_bmi;
	BLENDFUNCTION m_blf;
	bool m_enable_gl;
};
#endif  //WIN32


#ifdef ANDROID_NDK
class API REAndroidSurface: public RESurface
{
public:
	REAndroidSurface(char* buff, kn_int width, kn_int height, REBitmap::Config colorFormat);

	// 
	virtual ~REAndroidSurface() ;

	// 
	virtual void Flip(LSTRECT &lst_rect);

	void SetDstPointer(char* pBuf);

protected:

    char* m_pixels;
};

#endif  // ANDROID_NDK

#ifdef QT_HMI

#include <QApplication>
#include <QtGui>

class API REQtSoftSurface: public RESurface
{
public:
    REQtSoftSurface(void* p, kn_int width, kn_int height, REBitmap::Config colorFormat);

    // 
    virtual ~REQtSoftSurface() ;

    // 
    virtual void Flip(LSTRECT &lst_rect);

    void SetDstLabel(QLabel* pLabel);

protected:

    QLabel* m_label;
    QImage* m_image;
    //QPixmap  m_pixmap;

};


#endif  // QT_HMI

#ifdef IOS_DEV

#include "SkCGUtils.h"

class API REIOSSurface: public RESurface
{
public:
	REIOSSurface(void*& buff, kn_int width, kn_int height, REBitmap::Config colorFormat);
    
	// 
	virtual ~REIOSSurface() ;
    
	// 
	virtual void Flip(LSTRECT &lst_rect);
    
	void SetDstPointer(char* pBuf);
    
    
    CGImageRef GetCGImageRef();
    
protected:
    
    // texture for gl
    unsigned char* m_pTexBuf;
    
    // soft
    CGImageRef m_cgimage;
    
    bool m_bGLFilp;
    
    
};

#endif

#endif  // REWindow_DEFINED
