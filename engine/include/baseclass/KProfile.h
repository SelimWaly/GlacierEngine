//  **************************************
//  File:        KProfile.h
//  ***************************************

#ifndef _KPROFILE_H__
#define _KPROFILE_H__

#include "KFile.h"

class API KNAPI KProfile  
{
public:
	KProfile();
	virtual ~KProfile();

	// 
    kn_int Open(const kn_string& strFilename);
	// 
    void Close(void);

	// 
    kn_int Reset();
	// 
    kn_int Mark();
	// 
    kn_int Back();

	// Section
    kn_int GetSection(const char* pKey);
	// 
    kn_int GetString(const char* pKey, char* pBuff, kn_int nCount);
	// 
    kn_int GetValue(const char* pKey, kn_int& nVvalue);
    // 
    kn_int GetValue(const char* pKey, kn_ulong& nVvalue);
	// 
    kn_int GetValue(const char* pKey, kn_double& dValue);

	// 
    static void Split(const char *pBuff, ...);

	// 
	kn_int GetLine(char* pBuff, kn_int nCount);
protected:

	// 
    kn_int strnicmp2(const char* pStr1, const char* pStr2, kn_int nCount) const;

    KFile m_File;		// 
    kn_ulong m_ulMark;	// 
};


#ifdef NAVI_ENGINE
 
#endif

#endif // _KPROFILE_H__
