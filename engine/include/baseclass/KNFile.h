//  **************************************
//  File:        KNFile.h
//  ***************************************

#ifndef _KNFILE_H_
#define _KNFILE_H_

// KNFileRead Me
// KNFile
// KNFile 
// 
// Type.hUNICODE:kn_char=charUNICODE:kn_char=wchar_t
// byte,short,long,float,double

// KNFileKNFile

// This class API now can be only used in Win32.

// ,Read.

#include "NE_pubhead.h"

#include "KFile.h"

class KComplexFile;

typedef map<string, KComplexFile*> KComplexFileMap;

// ADD. hzf.2006.11.8.
// --Begin
//lint -e1735 -e1506 -e774 -e1740 -e1763
// --End

#define REVERSE2(x) ((((x)&0xff00)>>8)|(((x)&0x00FF)<<8))
#define REVERSE4(x) ((((x)&0xff000000)>>24)|(((x)&0x00ff0000)>>8)|(((x)&0x0000ff00)<<8)|(((x)&0x000000ff)<<24))

#define KNERR_FILE_ERR RESULT_UNKNOW
#define KNERR_FILE_OK  RESULT_OK

class API KNFile : public KFile
{
public:
	KNFile();
	virtual ~KNFile();

public:
	kn_bool IsFileOpen() const;

	/*
	*  
	*     
	* 		strFileName [in] 
	* 		dwShareMode [in](share/exclusive)
	*		dwCreationDisposition [in]API:CreateFile()
	*		dwFlagsAndAttributes [in]API:CreateFile()
	*   
	*/ 
	virtual kn_long OpenFile(const kn_string& strFileName,
							 kn_dword dwDesiredAccess = GENERIC_READ,
							 kn_dword dwShareMode = FILE_SHARE_READ,
							 kn_dword dwCreationDisposition = OPEN_EXISTING,
							 kn_dword dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);

	/*
	* 
	*   
	*/ 
	virtual kn_long CloseFile();

	/*
	* 
	*     
	* 		lOffset [in] 
	* 		dwMoveMethod [in]0-  1-  2-
	*   
	*/ 
	virtual KNRESULT Seek(kn_long lOffset, kn_dword dwMoveMethod);

	/*
	* 
	*     
	*   
	*/ 
	virtual KNRESULT Flush();

    // 
    //////////////////////////////////////////////////////////////////////////
    /* 
    * 
    * @param ulSize    ulSize
    */
    virtual KNRESULT GetSize(IN kn_ulong& ulSize);


	/*
	*  
	*   
	*/ 
	virtual kn_long Tell();
    //////////////////////////////////////////////////////////////////////////


};

// ADD. hzf.2006.11.8.
// --Begin
//lint +e1735 +e1506 +e774 +e1740 +e1763
// --End

#endif // _KNFILE_H_
