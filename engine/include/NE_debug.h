//  **************************************
//  File:        NE_debug.h
//  ***************************************

#ifndef _NE_DEBUG_H_
#define _NE_DEBUG_H_

#include <assert.h>

// Define ASSERT
#ifndef ASSERT
    
    #ifdef NDEBUG // for release
//         #define ASSERT(expr) \
//             if (!(expr)) LOG_ASSERT(__FILE__, __LINE__, __FUNCTION__, #expr);
			#if defined(QT_LINUX_LIB)
				#define  ASSERT(X) Q_ASSERT(X)
			#else
				#define  ASSERT(X)
			#endif
    #else
        #ifdef KOTEI_VC
            #include <crtdbg.h>
            #define ASSERT(X) _ASSERT(X)
        #else
			#define _ASSERT(X) assert(X) 
            #define ASSERT(X) assert(X)
        #endif // KOTEI_VC
    #endif	//	NDEBUG
#endif	//	ASSERT

// DEFINE _SYSTEMMONITOR
//#ifdef _DEBUG
//    #ifdef WIN32
//		#ifndef _SYSTEMMONITOR
//		#define _SYSTEMMONITOR // 启用监测系统
//		#endif
//    #endif
//#endif

#endif // _NE_DEBUG_H_
