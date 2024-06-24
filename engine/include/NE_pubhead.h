//  **************************************
//  File:        NE_pubhead.h
//  ***************************************

#ifndef _NE_PUBHEAD_H_
#define _NE_PUBHEAD_H_

#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#ifdef ANDROID_NDK
#include <android/log.h>
#include <assert.h>
#include <unistd.h>
#include <sys/resource.h>
extern bool g_bLogEnable;	//	log
#endif
using namespace std;
#include "NE_type.h"
#include "NE_configure.h"
#include "NE_macro.h"
//#include "NE_error.h"
#include "NE_debug.h"

#if defined(QT_WINDOWS_LIB) || defined(QT_LIB) || defined(QT_LINUX_LIB)
#include "KLog.h"
#include <stdio.h>
#include <limits.h>
#include <qglobal.h>
#endif

#ifndef ANDROID_NDK
#else
#define ASSERT(expr) \
	if (g_bLogEnable && !(expr)) __android_log_print(ANDROID_LOG_WARN, "ASSERT", "[#%d][t%d][%s] [%s]", \
	__LINE__, gettid(), __FUNCTION__, #expr);

#define _ASSERT(X) ASSERT(X)
#endif



//#define  LOG_TAG    "NE"
#ifdef ANDROID_NDK
#define  LOGI(...)  if(g_bLogEnable) __android_log_print(ANDROID_LOG_INFO  , "INFO",__VA_ARGS__)
#define  LOGE(...)  if(g_bLogEnable) __android_log_print(ANDROID_LOG_ERROR  , "ERROR",__VA_ARGS__)
#define  LOGD(...)  if(g_bLogEnable) __android_log_print(ANDROID_LOG_DEBUG  , "DEBUG",__VA_ARGS__)
#elif defined(QT_WINDOWS_LIB) || defined(QT_LIB) || defined(QT_LINUX_LIB)
#define  LOGI LogInfo
#define  LOGE LogInfo
#define  LOGD LogInfo
#else
#define  LOGI(...)
#define  LOGE(...)
#define  LOGD(...)
#endif //ANDROID_NDK

// export uicomposer dll
//#define  UIC_DLL

#endif // _NE_PUBHEAD_H_
