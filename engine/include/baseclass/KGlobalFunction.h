//  **************************************
//  File:        KGlobalFunction.h
//  ***************************************


#ifndef _KGLOABALFUNCTIN_
#define _KGLOABALFUNCTIN_

#include <stdlib.h>

#include "NE_pubhead.h"
#include "FilePath.h"
#include "CharSet.h"
#include "KLog.h"

void TraceChars (const char* psz);
void TraceCharsW (const wchar_t* psz);
void TraceBytes (const char* pszTAG, BYTE* pBuffer, int iCount);

// #if defined(ANDROID_NDK) || defined(IOS_DEV)
// inline size_t mbstowcs ( wchar_t * wcstr, const char * mbstr, size_t max )
// {
	// return ConvertGBK2Unicode((char*)mbstr, max, wcstr);
// }

// inline size_t wcstombs ( char * mbstr, const wchar_t * wcstr, size_t max )
// {
	// return ConvertUnicode2GBK((wchar_t*)wcstr, max, mbstr);
// }
// #endif


//#define RTIC_DEMO	//demo

//
KNAPI kn_uint GetAddress(kn_byte acAddress[]);

/*
 *  kn_word
 * 
 * 		 temp [in] 
 * 		 n [in] 
 * kn_word
 */
KNAPI kn_word GetWORD(const kn_byte temp[], kn_int n);

/*
*  kn_dword
* 
* 		value [in] 
* 		value [in] 
* kn_dword
*/
KNAPI kn_dword GetDWORD(const kn_byte temp[], kn_int n);

/*
*  
*     
* 		pSourse [in] 
* 		n [in] 
* 		abyResult [out]
*   
*/ 

#define ReverseByteArray(pSourse, abyResult, n) \
											{for (kn_int iDefine = 0 ; iDefine < n ; iDefine++) \
											{									\
											abyResult[iDefine] = pSourse[n- 1- iDefine];	\
											}}

#define HIDWORD(l)   ((kn_dword) (((__int64) (l) >> 32) & 0xFFFFFFFF)) 
#define LODWORD(l)   ((kn_dword) (l)) 
#define MAKEINT64(a, b) ((__int64) (((kn_dword) (a)) | ((__int64) ((DWORD) (b))) << 32)) 

KNAPI void* DumpFile ( IN LPCTSTR strFileName, 
					   IN DWORD	dwMapStart,
					   IN DWORD	dwBuffSize );

KNAPI void long_reverse(kn_long &value);

KNAPI void int_reverse(kn_uint &value);

KNAPI void short_reverse(kn_ushort &value);

KNAPI void __int64_Reverse(__int64 &value);

#ifdef RTIC_DEMO
#define  RT_FREQ	60 //
enum JAME_TYPE
{
	RED_TYPE = 0,	//
	YELLOW_TYPE,	//
	GREEN_TYPE,		//
};

extern kn_bool g_bRTIC;		//RTIC
extern kn_bool g_bRPlan;	// 

JAME_TYPE GetLinkJametype(kn_dword dwLinkId);

//ID
kn_dword GetProcessIdFromName(LPCTSTR name);
void KillProgram(LPCTSTR ExeName);
#endif

//	
void string_split(const string &strsrc, vector<string>&arrStrDst, string::value_type separator);

#endif // _KGLOABALFUNCTIN_
