

#ifdef ANDROID_NDK
#include "FilePath.h"
#include <android/bitmap.h>
#include "DataSync.h"
#include "KScreen.h"
#include "mainforwindows.h"
 

//bool g_bLogEnable = true;

extern int g_iScreenWidth; // 
extern int g_iScreenHeight; // 

extern CGLACIERInstance  g_instance;

void CreateView();
void ResizeWindow(void* dst, int w, int h);

// 
void SetResourcePath()
{
 
	kn_char szResPath[] = _T("/sdcard/nplan/");
 	SetCurrentPath(szResPath);

}



BOOL InitInstance(AndroidBitmapInfo* pInfo, void* pBuf)
{

	// INIT HMI
	//g_screen.Create(g_iScreenWidth, g_iScreenHeight, RE_RGB_565, hWnd);
	//g_screen.Create(g_iScreenWidth, g_iScreenHeight, REBitmap::kARGB_8888_Config, hWnd);
	//g_screen.Create(g_iScreenWidth, g_iScreenHeight, REBitmap::kARGB_8888_Config, hWnd, SCREEN_RENDER_MAIN_THREAD);
	KGLACIERInitPara para;
	para.m_w = pInfo->width;
	para.m_h = pInfo->height;
	para.m_wnd = pBuf;

	//	android ui , SCREEN_RENDER_MULTI_THREAD
	para.m_render_mode = SCREEN_RENDER_MULTI_THREAD;	//SCREEN_RENDER_MAIN_THREAD;
	para.m_device_type = ANDROID_DEVICE;


	g_iScreenWidth = pInfo->width; // 
	g_iScreenHeight = pInfo->height; // 


	//setDPIName(g_iScreenWidth);
	REBitmap::Config config = REBitmap::kRGB_565_Config;

	if(pInfo->format == ANDROID_BITMAP_FORMAT_RGBA_8888)
	{
		config = REBitmap::kARGB_8888_Config;
	}
	else if(pInfo->format == ANDROID_BITMAP_FORMAT_RGB_565)
	{
		config = REBitmap::kRGB_565_Config;
	}
	else if(pInfo->format == ANDROID_BITMAP_FORMAT_RGBA_4444)
	{
		config = REBitmap::kARGB_4444_Config;
	}
	else if(pInfo->format == ANDROID_BITMAP_FORMAT_A_8)
	{
		config = REBitmap::kA8_Config;
	}

	para.m_format = config;

	LOGI ("InitInstance 11111");
	g_instance.create(para);

	LOGI ("InitInstance 22222");




	CreateView();

	g_instance.getScreen()->SetRenderFlag(TRUE);

	LOGI ("InitInstance 3333");





	return TRUE;
}



void AndroidResize(void* dst, int w, int h)
{

	ResizeWindow(dst, w, h);
 
}


// discard
void AndroidFlip()
{
	//g_instance.getScreen()->OnDraw();
	g_instance.getScreen()->SetRenderFlag(true);
}


void SetBitMapPointer(char* pBuf)
{
	//g_instance.getScreen()->setWnd(pBuf);
}



boost::mutex  mutexBitmap;
//writeLock lockBitmap(mutexBitmap);

void LockJavaBitmap()
{
	//LOGI ("LockJavaBitmap 000");
	mutexBitmap.lock();

	//LOGI ("LockJavaBitmap 1111");
}

void UnlockJavaBitmap()
{
	//LOGI ("UnlockJavaBitmap 000");
	mutexBitmap.unlock();
	//LOGI ("UnlockJavaBitmap 1111");
}


  

//void SendAndroidMessage(int message, int wParam, int lParam)
//{
//	SendOSMessage(message, wParam, lParam);
//}



// for android 
int RunModalEventLoop(bool& bExit)
{
	return 0;
}
#endif
