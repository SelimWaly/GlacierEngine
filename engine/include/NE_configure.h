//  **************************************
//  File:        Ne_configure.h
//  ***************************************

#ifndef _NE_CONFIGURE_H_
#define _NE_CONFIGURE_H_

#define _LINUX_PLATFORM		0x01
#define _WIN32_PLATFORM		0x02
#define _WINCE_PLATFORM		0x03

// OS Platform
#if defined(_WIN32_WCE)
	#define _CURRENT_PLATFORM _WINCE_PLATFORM
	#ifndef WIN32
		#define WIN32
	#endif
#elif defined(_WINDOWS)
    #define _CURRENT_PLATFORM _WIN32_PLATFORM
    #ifndef WIN32
        #define WIN32
    #endif
#else
    #define _CURRENT_PLATFORM _LINUX_PLATFORM
    #define LINUX
#endif // OS Platform

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

    #include <windows.h>
    #include <tchar.h>
#endif

// C++ Compiler
#if   _CURRENT_PLATFORM == _LINUX_PLATFORM
    #ifndef KOTEI_GCC
		#include "LINUXTCHAR.h"
        #define KOTEI_GCC
    #endif
#elif _CURRENT_PLATFORM == _WIN32_PLATFORM
    #ifndef KOTEI_VC
        #define KOTEI_VC
    #endif
#elif _CURRENT_PLATFORM == _WINCE_PLATFORM
    #ifndef KOTEI_EVC
        #define KOTEI_EVC
    #endif
#endif // C++ Compiler

// ����DEBUG��_DEBUG��
#if defined(KOTEI_EVC) && defined(DEBUG) && !defined(_DEBUG)
    #define _DEBUG
#endif

#if defined(KOTEI_VC) && defined(_DEBUG) && !defined(DEBUG)
    #define DEBUG
#endif // DEBUG

#ifdef IOS_DEV
	#include "LINUXTCHAR.h"
#endif
#endif // _NE_CONFIGURE_H_
