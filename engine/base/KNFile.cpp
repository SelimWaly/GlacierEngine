//  **************************************
//  File:        KNFile.cpp
//  ***************************************
#include "KNFile.h"
//#include "KComplexFile.h"
//#include "KPackedFile.h"
#include "KGlobalFunction.h"
#include "KProfile.h"

#define MAXSTRLEN (255)


#ifdef LINUX
#define  PATH_SEPARATOR '/'
#else
#define PATH_SEPARATOR	'\\'
#endif

kn_int g_grayType;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KNFile::KNFile()
{
}

KNFile::~KNFile()
{
	CloseFile();
}

kn_bool KNFile::IsFileOpen() const
{
	return IsOpen();
}

/*
*  
*     
* 		strFileName [in] 
* 		dwShareMode [in](share/exclusive)
*		dwCreationDisposition [in]API:CreateFile()
*		dwFlagsAndAttributes [in]API:CreateFile()
*   
*/ 
kn_long KNFile::OpenFile(const kn_string& strFileName,
						 kn_dword dwDesiredAccess,
						 kn_dword dwShareMode,
						 kn_dword dwCreationDisposition,
						 kn_dword dwFlagsAndAttributes)
{
    KNRESULT result = RESULT_UNKNOW;
#ifdef KOTEI_LINUX
    ConvertSlash(const_cast<kn_char*>(strFileName.c_str()));
#endif

	m_strName = strFileName;

    string strName;
    static char filename[MAXSTRLEN];
#ifdef UNICODE
    memset(filename, 0, MAXSTRLEN);
     WideCharToMultiByte(936, NULL, (LPCTSTR)strFileName.c_str(), strFileName.size(),
         (LPSTR)filename, strFileName.size() * sizeof(kn_char), NULL, NULL);
#else
     strncpy(filename, strFileName.c_str(), strFileName.length());
#endif

    strName = filename;

     // 
    result = KFile::Open(strFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, dwFlagsAndAttributes);

	if (result == KNRESULT(0)) {
		KFile::GetSize(m_ulSize); // Size.
	}

    return result;
}

/*
* 
*   
*/ 
kn_long KNFile::CloseFile()
{
    return Close();
}


/**
* 
* 
* @param ulSize    ulSize
*/
KNRESULT KNFile::GetSize(IN kn_ulong& ulSize)
{
    ulSize = m_ulSize;

    return RESULT_OK;
}


/*
* 
*     
* 		lOffset [in] 
* 		dwMoveMethod [in]0-  1-  2-
*   
*/ 
KNRESULT KNFile::Seek(kn_long lOffset, kn_dword dwMoveMethod)
{
	ASSERT(m_hFile != NULL);		
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);

    // m_lCurson
    // m_ulSize
	if (m_bIsOpen)
	{
		kn_long lCursor = 0; // 
		if (dwMoveMethod == 0)		// 
		{
			lCursor = lOffset;
		}
		else if (dwMoveMethod == 1)	// 
		{
			lCursor = m_lCursor + lOffset;
		}
		else if (dwMoveMethod == 2)	// 
		{
			lCursor = m_ulSize - lOffset;
		}

		if (dwMoveMethod == 0)		// 
		{
			lOffset += 0; // // m_ulPackedFileOffset == 0
		}
		else if (dwMoveMethod == 2)	// 
		{
			kn_ulong ulSize = 0;

            KNRESULT result = KFile::GetSize(ulSize); // 
			if (result != RESULT_OK)
			{
				return result;
			}
			lOffset += ulSize - (0 + m_ulSize); // m_ulSize == ulSizem_ulPackedFileOffset == 0
		}

		if (fseek(m_hFile, lOffset, dwMoveMethod) != 0)
		{
			return RESULT_UNKNOW;
		}

		m_lCursor = lCursor; // m_lCursor.

		return RESULT_OK;
	}

	return KNRESULT(EC_ERROR, SC_BASELIB, EF_FILE, KN_ERROR_NOT_OPEN);	// 
}

/*
*  
*   
*/ 
kn_long KNFile::Tell()
{
	if (m_bIsOpen)
	{
		return m_lCursor;
	}
	else
	{
		return RESULT_UNKNOW;
	}
}


/*
* 
*     
*   
*/ 
KNRESULT KNFile::Flush()
{
	return (fflush(m_hFile) == 0) ? RESULT_OK : RESULT_UNKNOW;
}
