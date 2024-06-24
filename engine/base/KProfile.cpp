//  **************************************
//  File:        KProfile.cpp
//  ***************************************


#include <string.h>
#include <stdarg.h>

#include "NE_pubhead.h"
#include "KProfile.h"

// ADD. hzf.2006.11.9.
// --Begin
//lint -e570 -e64 -e668 -e650
// --End

#define MAX_LINE_SIZE	(512)
#define STEP			(16)

/*
* 
*     
*   
*/ 
KProfile::KProfile()
{
    m_ulMark = -1;
}

/*
* 
*     
*   
*/ 
KProfile::~KProfile()
{
	m_File.Close();
}

/*
* 
*     
* 		strFileName [in] 
*   0-1
*/ 
kn_int KProfile::Open(const kn_string& strFilename)
{
    if ( m_File.IsOpen() )
	{
		m_File.Close();
	}

//#ifdef _UNICODE
//    m_pFile = _wfopen(strFilename.c_str(), _T("rb"));
//#else
//    m_pFile = fopen(strFilename.c_str(), _T("rb"));
//#endif

	m_File.Open(strFilename, GENERIC_READ, NULL, OPEN_EXISTING, NULL);
	if ( !m_File.IsOpen())
	{
		return -1;
	}

    return 0;
}

/*
* 
*     
*   
*/ 
void KProfile::Close(void)
{
    if (m_File.IsOpen()) 
	{
		m_File.Close();
	}
}

/*
* 
*     
* 		pBuff [out] 
* 		nCount [in]
*   0-1
*/ 
kn_int KProfile::GetLine(char* pBuff, kn_int nCount)
{
    if (!m_File.IsOpen())
	{
		return -1;
	}

	kn_ulong fileSize = 0;
    m_File.GetSize(fileSize);
    if (static_cast<kn_ulong>(m_File.Tell()) >= fileSize) 
	{
		return -1; 
	}
    
    for (kn_int i = 0; i < nCount; i += STEP)
    {
        kn_ulong ret = 0;
		m_File.Read(&pBuff[i], sizeof(char)*STEP, ret);

        if ((ret == 0) && (i == 0)) 
		{
			return -1;
		}

        for (kn_int j = 0; j < (kn_int)ret; ++j)
        {
            if (pBuff[i+j] == '\n')
            {
                pBuff[i + j - 1 > 0 ? i + j -1 : 0] = 0;
                //fseek(m_pFile, -ret+j+1, SEEK_CUR);
				m_File.Seek(j + 1 - ret, 1);
                return 0;
            }
        }
    }

    return 0;
}

/*
* 
*     
* 		pKey [in] 
* 		pBuff [out]
*		nSize [in]
*   0-1
*/ 
kn_int KProfile::GetString(const char* pKey, char* pBuff, kn_int nSize)
{
    if (!pKey || !pBuff) 
	{
		return -1;
	}

    const kn_int nLen = strlen(pKey);

    char pchTemp[MAX_LINE_SIZE] = {0};

    while (GetLine(pchTemp, MAX_LINE_SIZE) != -1)
    {
        if (strnicmp2(pchTemp, pKey, nLen) == 0) // key
        {
            kn_int nOutLen = strlen(pchTemp)-nLen;
            if (nOutLen > nSize)
			{
				nOutLen = nSize;
			}
            
            strncpy(pBuff, &pchTemp[nLen+1], nOutLen);

            return 0;
        }
    }

    return -1;
}
    
/*
*  
*     
* 		pStr1 [in] 1
* 		pStr2 [in]2
* 		nCount [in]
*   0-1
*/ 
kn_int KProfile::strnicmp2(const char* pStr1, const char* pStr2, kn_int nCount) const
{
    for (kn_int i = 0; i < nCount; ++i)
    {
        if (pStr1[i] != pStr2[i] && 
            pStr1[i]+0x20 != pStr2[i] && 
            pStr1[i] != pStr2[i]+0x20)
        {
            return -1;
        }
    }

    return 0;
}

/*
* 
*     
* 		pKey [in] 
* 		nValue [out]
*   0-1
*/ 
kn_int KProfile::GetValue(const char* pKey, kn_int& nValue)
{
    char buff[MAX_LINE_SIZE] = {0};

    if (GetString(pKey, buff, MAX_LINE_SIZE) == -1) return -1;

    nValue = atoi(buff);

    return 0;    
}

/*
* 
*     
* 		pKey [in] 
* 		nValue [out]
*   0-1
*/ 
kn_int KProfile::GetValue(const char* pKey, kn_ulong& nValue)
{
    char buff[MAX_LINE_SIZE] = {0};

    if (GetString(pKey, buff, MAX_LINE_SIZE) == -1) return -1;

    nValue = atol(buff);

    return 0;    
}

/*
* 
*     
* 		pKey [in] 
* 		dValue [out]
*   0-1
*/ 
kn_int KProfile::GetValue(const char* pKey, kn_double& dValue)
{
    char chBuff[MAX_LINE_SIZE] = {0};

    if (GetString(pKey, chBuff, MAX_LINE_SIZE) == -1)
	{
		return -1;
	}

    dValue = atof(chBuff);

    return 0;  
}

/*
* 
*     
*   0
*/ 
kn_int KProfile::Reset()
{
	// ADD. hzf.2006.11.9.
	// --Begin
	ASSERT(m_File.IsOpen());
	// --End
	
    //fseek(m_pFile, 0, SEEK_SET);
	m_File.Seek(0, 0);
    return 0;
}

/*
* 
*     
*   0
*/ 
kn_int KProfile::Mark()
{
	// ADD. hzf.2006.11.9.
	// --Begin
	ASSERT(m_File.IsOpen());
	// --End
	
    m_ulMark = m_File.Tell();
    return 0;
}

/*
* 
*     
*   0-1
*/ 
kn_int KProfile::Back()
{
	// ADD. hzf.2006.11.9.
	// --Begin
	ASSERT(m_File.IsOpen());
	// --End
	
    if (m_ulMark != -1)
    {
        //fseek(m_pFile, m_uiMark, SEEK_SET);
		m_File.Seek(m_ulMark, 0);
        return 0;
    }
    
    return -1;
}

/*
* Section
*     
* 		pKey [out] 
*   0-1
*/ 
kn_int KProfile::GetSection(const char* pKey)
{
	// ADD. hzf.2006.11.9.
	// --Begin
	ASSERT(m_File.IsOpen());
	// --End

    if (NULL == pKey)
	{
		return -1;
	}

    //fseek(m_pFile, 0, SEEK_SET);
	Reset();

    const kn_int nLen = strlen(pKey);

    char pchTemp[MAX_LINE_SIZE] = {0};

    while(GetLine(pchTemp, MAX_LINE_SIZE) != -1)
    {
        // break
        if (pchTemp[0] == '[' && pchTemp[nLen+1] == ']')
        {
            if (strnicmp2(&pchTemp[1], pKey, nLen) == 0)
            {
                return 0;
            }
        }
    } 

    return -1;
}

/*
* 
*     
* 		pBuff [in] 
*   
*/ 
void KProfile::Split(const char* pBuff, ...)
{    
    va_list marker;
    va_start(marker, pBuff);
    
    kn_int begin = 0;

    char* pVar = va_arg(marker, char*);

    for (kn_int i = 0; i <= (kn_int)strlen(pBuff); ++i)
    {
        if (pVar == NULL) 
			break;

        if (pBuff[i] == ',' || pBuff[i] == 0)
        {
            memcpy(pVar, &pBuff[begin], i-begin);
            pVar[i-begin] = 0;
            begin = i+1;

            pVar = va_arg(marker, char*);
        }
    }
    
    va_end(marker);
}

// ADD. hzf.2006.11.9.
// --Begin
//lint +e570 +e64 +e668 +e650
// --End
