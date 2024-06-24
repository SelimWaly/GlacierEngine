﻿//  **************************************
//  File:        CharSet.cpp
//  ***************************************

#include "CharSet.h"
#include "KGlobalFunction.h"
#include "FilePath.h"

#define REVERSE2(x) ((((x)&0xff00)>>8)|(((x)&0x00FF)<<8))

//	
static BYTE* s_pUN2GBTbale = NULL;
static BYTE* s_pGB2UNTbale = NULL;

static BYTE* s_pJIS2UNTable = NULL;
static BYTE* s_pUN2JISTable = NULL;


#ifdef AREA_JP

static int ANSI_CODE = CHARSET_SJIS;		//	shift-jis

#else
static int ANSI_CODE = CHARSET_GBK;

#endif
// 
bool IsFullWidthChar_SJIS (unsigned char code)
{
	return ((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xFC));
	
}

bool IsFullWidthChar_GBK(unsigned char code)
{
	// GBK  > 127
	return (code > 127);
}

bool IsFullWidthChar(unsigned char code)
{
	if(ANSI_CODE == CHARSET_GBK)
	{
		return IsFullWidthChar_GBK(code);
	}
	else if(ANSI_CODE == CHARSET_SJIS)
	{
		return IsFullWidthChar_SJIS(code);
	}
	else
	{
		ASSERT(0);
		
		
	}
	return false;
	
}


/***********************************************************************
* Function :	
*
*
* Returns:   void
***********************************************************************/
void ReleaseCharSetTable ()
{
	SAFE_DELETE_GROUP (s_pUN2GBTbale);
	SAFE_DELETE_GROUP (s_pGB2UNTbale);

	SAFE_DELETE_GROUP (s_pJIS2UNTable);
	SAFE_DELETE_GROUP (s_pUN2JISTable);
    //if (s_pUN2GBTbale != NULL)
    //{
    //    delete [] s_pUN2GBTbale;
    //    s_pUN2GBTbale = NULL;
    //}

    //if (s_pGB2UNTbale != NULL)
    //{
    //    delete [] s_pGB2UNTbale;
    //    s_pGB2UNTbale = NULL;
    //}
}



/***********************************************************************
* Function :	
*
* Parameter: const TCHAR * pFileName	
* Parameter: int & iLen					
*
* Returns:   BYTE*	file buffer
***********************************************************************/
BYTE* GetFileBuffer(const TCHAR* pFileName, long& iLen)
{

#if defined(KOTEI_LINUX) && defined(_UNICODE) // Linuxfopen
    //  linux & UINCODE
    char szTemp[MAX_PATH] = {0};
    wcstombs(szTemp, pFileName, MAX_PATH);

    LOGI ("GetFileBuffer szTemp = %s", szTemp);

    FILE* fs = fopen(szTemp, "rb");
#else
    FILE* fs = _tfopen(pFileName, _T("rb"));
#endif


	if (fs == NULL)
	{
#ifdef QT_WINDOWS_LIB
        LOGE ("file open error %ls\n", pFileName);
#else
        LOGE ("file open error %s\n", pFileName);
#endif
		return NULL;
	}

	fseek(fs, 0, SEEK_END);
	long lFileSize = ftell(fs);

	fseek(fs, 0, SEEK_SET);

	BYTE* pBuffer = new BYTE[lFileSize];

	long iReadNum = fread (pBuffer, sizeof(BYTE), lFileSize, fs);

	fclose(fs);

	if(iReadNum != lFileSize)
	{
		LOGE ("fread %s error, iReadNum = %d, lFileSize = %d\n", pFileName, iReadNum, lFileSize);
		delete [] pBuffer;
		pBuffer = NULL;
	}
	else
	{
		// OK
		iLen = lFileSize;
	}

	return pBuffer;

}


kn_string GetTablePath()
{
	kn_string wstrTableFile = GetCurrentPath();
	wstrTableFile += _T("resource/");



	return wstrTableFile;

}


/***********************************************************************
* Function : shift-jisunicode ,  MultiByteToWideChar
*
* Parameter: char * szSJIS		shift-jis
* Parameter: size_t iSJISLen		shift-jis
* Parameter: wchar_t * wszUnicode	uncode
*
* Returns:   int		unicode
***********************************************************************/
int ConvertSJIS2Unicode(IN const char* szSJIS, IN size_t iSJISLen, OUT wchar_t* wszUnicode)
{
	//	shift-jis

	//const int SJIS_MIN = 0x000;
	//const int SJIS_MAX = 0xFFFF;

	BYTE* pBuffer = s_pJIS2UNTable;

	if (pBuffer == NULL)
	{
		long lFileSize = 0;

// 		kn_string wstrTableFile = _T("Font/ju_table.txt");
// 		GetFilePath (wstrTableFile);

		kn_string wstrTableFile = GetTablePath();

		wstrTableFile += _T("ju_table.txt");

		pBuffer = GetFileBuffer(wstrTableFile.c_str(), lFileSize);

		if(pBuffer == NULL || lFileSize != MAXWORD * 2)
		{
			LOGE ("Get File ju_table.txt buffer error!\n");
			return -1; 
		}

		s_pJIS2UNTable = pBuffer;
	}


	WORD wSJIS = 0;
	size_t iUnIndex = 0;
	size_t iSJISIndex = 0;

	for (iSJISIndex = 0; iSJISIndex < iSJISLen; iSJISIndex++)
	{

		unsigned char code = szSJIS[iSJISIndex];

		//	 1 
		//	1. ASCII (0x20-0x7E)
		//	2. ASCII0x00-0x1F0x7F
		//	3. JIS X 02010xA1-0xDF
		//if (code < 0x80 || (code >= 0xA1 && code <= 0xDF))
		//{
		//	wSJIS = MAKEWORD (0, szSJIS[iSJISIndex]);
		//}
		//else
		//{
		//	//  2
		//	//	“”0x81-0x9F0xE0-0xEF47
		//	//	“”0xF0-0xFC13
		//	wSJIS = MAKEWORD (szSJIS[iSJISIndex + 1], szSJIS[iSJISIndex]);
		//	iSJISIndex++;	//	sjis index
		//}


		if((code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xFC))
		{
	
			//  2
			//	“”0x81-0x9F0xE0-0xEF47
			//	“”0xF0-0xFC13
			wSJIS = MAKEWORD (szSJIS[iSJISIndex + 1], szSJIS[iSJISIndex]);
			iSJISIndex++;	//	sjis index
		}
		else
		{
			//	 1 
			//	1. ASCII (0x20-0x7E)
			//	2. ASCII0x00-0x1F0x7F
			//	3. JIS X 02010xA1-0xDF
			wSJIS = MAKEWORD (0, szSJIS[iSJISIndex]);
		}

		//	 Table[shift-jis Code] = Unicode
		int iTableIndex = wSJIS;

		//	
		wszUnicode[iUnIndex] = MAKEWORD (pBuffer[iTableIndex << 1], pBuffer[(iTableIndex << 1) + 1]);

		iUnIndex++;

	}

	wszUnicode[iUnIndex] = 0;	//	

	return iUnIndex;
}


/***********************************************************************
* Function : uncodesjis ,  WideCharToMultiByte
*
* Parameter: IN wchar_t * wszUnicode	uncode
* Parameter: IN size_t iUnLen			uncode
* Parameter: OUT char * szMul			shitf-jis
*
* Returns:   int						shitf-jis
***********************************************************************/
int ConvertUnicode2SJIS(IN const wchar_t* wszUnicode, IN size_t iUnLen, OUT char* szMul)
{
	BYTE* pBuffer = s_pUN2JISTable;

	if (pBuffer == NULL)
	{
		long lFileSize = 0;

// 		kn_string wstrTableFile = _T("Font/uj_table.txt");
// 		GetFilePath (wstrTableFile);

		kn_string wstrTableFile = GetTablePath();
		wstrTableFile += _T("uj_table.txt");


		pBuffer = GetFileBuffer(wstrTableFile.c_str(), lFileSize);

		if(pBuffer == NULL || lFileSize != MAXWORD * 2)
		{
			LOGE ("Get File uj_table.txt buffer error!\n");
			return -1; 
		}

		s_pUN2JISTable = pBuffer;
	}


	wchar_t wUnicode = 0;

	int iMulIndex = 0;

	for (size_t iUnIndex = 0; iUnIndex < iUnLen; iUnIndex++)
	{
		wUnicode = wszUnicode[iUnIndex];

		ASSERT(wUnicode < MAXWORD);	// for linux wchar_t

		//	 Table[Unicode] = shift-jis code
		int iTableIndex = REVERSE2(wUnicode);

		if (iTableIndex < MAXWORD && iTableIndex >= 0)
		{
			iTableIndex <<= 1;	//	iTableIndex * 2;

			//	
			szMul[iMulIndex] = pBuffer[iTableIndex];
			szMul[iMulIndex + 1] = pBuffer[iTableIndex + 1];

			if(szMul[iMulIndex + 1] == 0)
			{
				//	0, 
				iMulIndex++;
			}
			else
			{
				//	
				iMulIndex+=2;
			}


		}
		else
		{
			//	are you killing me?
			szMul [iMulIndex] = 0;
			szMul [iMulIndex+1] = 0;
			iMulIndex += 2;
			ASSERT(0);
		}


	}

	//	
	szMul[iMulIndex] = 0;


	return iMulIndex;
}



/***********************************************************************
* Function : uncodeGBK ,  WideCharToMultiByte
*
* Parameter: IN wchar_t * wszUnicode	uncode
* Parameter: IN size_t iUnLen			uncode
* Parameter: OUT char * szGBK			gbk
*
* Returns:   int						gbk
***********************************************************************/
int ConvertUnicode2GBK(IN const wchar_t* wszUnicode, IN size_t iUnLen, OUT char* szGBK)
{
//	return ConvertUnicode2SJIS(wszUnicode, iUnLen, szGBK);

    const int UNICODE_MAX = MAXWORD;
    const int UNICODE_MIN = 0;
	const size_t ARRAY_SIZE = UNICODE_MAX - UNICODE_MIN;

    BYTE* pBuffer = s_pUN2GBTbale;
		
    if (pBuffer == NULL)
    {
		//	
		long lFileSize = 0;

		kn_string wstrTableFile = GetTablePath();
		wstrTableFile +=  _T("ug_table.txt");

//         kn_string wstrTableFile = _T("Font/ug_table.txt");
//         GetFilePath (wstrTableFile);

		pBuffer = GetFileBuffer(wstrTableFile.c_str(), lFileSize);

		if(pBuffer == NULL)
		{
			LOGE("ConvertUnicode2GBK No table.");
			return -1;
		}

		if ((lFileSize >> 1) != ARRAY_SIZE)
		{
			//	
			LOGE("ConvertUnicode2GBK table size error.");
			return -2;
		}

		s_pUN2GBTbale = pBuffer;
    }

	wchar_t wUnicode = 0;

    int iGBIndex = 0;

    for (size_t iUnIndex = 0; iUnIndex < iUnLen; iUnIndex++)
    {
        wUnicode = wszUnicode[iUnIndex];

        ASSERT(wUnicode < MAXWORD);	// for linux wchar_t

        //	 Table[Unicode] = GBCode
        int iTableIndex = REVERSE2(wUnicode) - UNICODE_MIN;

        if (iTableIndex < ARRAY_SIZE && iTableIndex >= 0)
        {
            iTableIndex <<= 1;	//	iTableIndex * 2;

            //if (pBuffer[iTableIndex * 2] == 0 && pBuffer[iTableIndex * 2 + 1] == 0 && wUnicode < 127 )
            if (pBuffer[iTableIndex] == 0 && pBuffer[iTableIndex + 1] == 0 && wUnicode < 127 )
            {
                //	ASCII
                szGBK[iGBIndex] = static_cast<char>(wUnicode);
                iGBIndex ++;
            }
            else
            {
                //	
                szGBK[iGBIndex] = pBuffer[iTableIndex];
                szGBK[iGBIndex + 1] = pBuffer[iTableIndex + 1];

                iGBIndex +=2;
            }


        }
        else
        {
            szGBK [iGBIndex] = 0;
            szGBK [iGBIndex+1] = 0;
            iGBIndex += 2;
        }


    }

    //	
    szGBK[iGBIndex] = 0;



    return iGBIndex;
}


/***********************************************************************
* Function : gbkunicode ,  MultiByteToWideChar
*
* Parameter: char * szGBK		gbk
* Parameter: size_t iGBLen		gbk
* Parameter: wchar_t * wszUnicode	uncode
*
* Returns:   int		unicode
***********************************************************************/
int ConvertGBK2Unicode(IN const char* szGBK, IN size_t iGBLen, OUT wchar_t* wszUnicode)
{

//	return ConvertSJIS2Unicode(szGBK, iGBLen, wszUnicode);

    //	GBK
    const int GBK_MIN = 0x8140;
    const int GBK_MAX = 0xFFFF;
	const size_t ARRAY_SIZE = GBK_MAX - GBK_MIN;

    BYTE* pBuffer = s_pGB2UNTbale;

    if (pBuffer == NULL)
    {
		long lFileSize = 0;

		kn_string wstrTableFile = GetTablePath();
		wstrTableFile += _T("gu_table.txt");


//         kn_string wstrTableFile = _T("Font/gu_table.txt");
//         GetFilePath (wstrTableFile);
		pBuffer = GetFileBuffer(wstrTableFile.c_str(), lFileSize);

		if(pBuffer == NULL)
		{
			LOGE("ConvertGBK2Unicode No table.");
			return -1;
		}

		if ((lFileSize >> 1) != ARRAY_SIZE)
		{
			//	
			LOGE("ConvertGBK2Unicode Table error");
			return -2;
		}

		s_pGB2UNTbale = pBuffer;
    }


    WORD wGB = 0;
    size_t iUnIndex = 0;
    size_t iGBIndex = 0;

    for (iGBIndex = 0; iGBIndex < iGBLen; iGBIndex++)
    {
        //	GBK  > 127, ASCII
        if (szGBK[iGBIndex] > 0)
        {
            wszUnicode[iUnIndex] = szGBK[iGBIndex];
            iUnIndex ++;

        }
        else
        {
            // 			memcpy(&wGB, szGBK + iGBIndex, 2);
            // 			wGB = REVERSE2(wGB);
            wGB = MAKEWORD (szGBK[iGBIndex + 1], szGBK[iGBIndex]);

            //	 Table[GBCode] = Unicode
            int iTableIndex = wGB - GBK_MIN;


            if (iTableIndex < ARRAY_SIZE && iTableIndex >= 0)
            {
                //	
                //memcpy (wszUnicode + iUnIndex, pBuffer + iTableIndex * 2, 2);
                wszUnicode[iUnIndex] = MAKEWORD (pBuffer[iTableIndex << 1], pBuffer[(iTableIndex << 1) + 1]);
            }
            else
            {
                wszUnicode[iGBIndex] = 0;
              }

            iGBIndex++;	//	gb index
            iUnIndex ++;
        }

    }

    wszUnicode[iUnIndex] = 0;	//	

	return iUnIndex;
}



/***********************************************************************
* Function :GB, 
*
* Parameter: char * szIn	
* Parameter: char * szOut	
*
* Returns:   void
***********************************************************************/
void ConvertCreateChar (IN char* szIn, OUT char* szOut)
{

    char chMin = ' ';
    char chMax = '~';

    WORD wMin = 0xA3A0;	//	 "";
    WORD wMax = 0xA3FE;	//	"";

    const size_t delta = wMin - chMin;

    size_t len = strlen(szIn);
    size_t iOutIndex = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (szIn[i] >= chMin && szIn[i] <= chMax)
        {
            WORD w = szIn[i] + delta;
            w = REVERSE2(w); 
            int t = sizeof(w);
            memcpy (szOut + iOutIndex, (void*)&w, t);
           *( szOut + iOutIndex + t) = 0; // 
            iOutIndex += 2;
        }
        else
        {
            szOut[iOutIndex] = szIn[i];
            iOutIndex++;
        }
    }

}


//=======================================================
// utf8  [2012-2-15]


/*
UTF-8

107unicodeUTF-8ASCII

2nn>1n1n+1010unicode

x

UnicodeUTF-8 :
UCS-4					 UTF-8  
-----------------------------------------------------------------------------------
U+00000000 – U+0000007F		|	0xxxxxxx  
U+00000080 – U+000007FF		|	110xxxxx 10xxxxxx  
U+00000800 – U+0000FFFF		|	1110xxxx 10xxxxxx 10xxxxxx  
U+00010000 – U+001FFFFF		|	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  
U+00200000 – U+03FFFFFF		|	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
U+04000000 – U+7FFFFFFF		|	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  

*/

//	utf8
size_t Utf8StringLen(const char* pUtf8String)
{
	unsigned char* p = (unsigned char*)pUtf8String;
	size_t iLen = 0;
	while(*p != 0)
	{
		int iCount = 0;
		unsigned char ch = *p;
		if((ch >> 7) == 0)		//	0
		{
			// ACSII
			iCount = 1;
		}
		else if((ch >> 5) == 0x6)	// 110B
		{
			// 2
			iCount = 2;
		}
		else if((ch >> 4) == 0xe)	// 1110B
		{
			// 3
			iCount = 3;
		}
		else if((ch >> 3) == 0x1e)	//	11110B
		{
			// 4
			iCount = 4;
		}
		else if((ch >> 2) == 0x3e)	//	111110B
		{
			// 5
			iCount = 5;
		}
		else if((ch >> 1) == 0x7e)	//	1111110B
		{
			// 6
			iCount = 6;
		}
		else
		{
			ASSERT(0);
			break;
		}

		p += iCount;
		iLen++;

	}


	return iLen;
}

//	utf 8 -> unicode 32 / 16
int ConvertUtf82Unicode(IN const char* szUtf8, IN size_t iUtf8Size, OUT const wchar_t* wszUnicode)
{
	unsigned char* psrc = (unsigned char*)szUtf8;
	wchar_t* pDst = (wchar_t*)wszUnicode;
	int iUnIndex = 0;
	kn_uint iUtf8Index = 0;

	while(*psrc != 0 && iUtf8Index < iUtf8Size)
	{
		int iCount = 0;
		unsigned char ch = *psrc;
		if((ch >> 7) == 0)		//	0
		{
			// ACSII
			iCount = 1;
			pDst[iUnIndex] = ch;
		}
		else if((ch >> 5) == 0x6)	// 110B
		{
			// 2
			iCount = 2;

			//	utf8
			ASSERT((psrc[1] >> 6) == 0x2);	//	10B

			//	110xxxxx 10xxxxxx  
			pDst[iUnIndex] = ((psrc[0] & 0x1f) << 6) | (psrc[1] & 0x3f);


		}
		else if((ch >> 4) == 0xe)	// 1110B
		{
			// 3
			iCount = 3;

			//	utf8
			ASSERT((psrc[1] >> 6) == 0x2);	//	10B
			ASSERT((psrc[2] >> 6) == 0x2);

			//	1110xxxx 10xxxxxx 10xxxxxx  
			pDst[iUnIndex] = ((psrc[0] & 0xf) << 12) | ((psrc[1] & 0x3f) << 6) | (psrc[2] & 0x3f);

		}
		else if((ch >> 3) == 0x1e)	//	11110B
		{
			// 4 
			iCount = 4;

			ASSERT((psrc[1] >> 6) == 0x2);
			ASSERT((psrc[2] >> 6) == 0x2);
			ASSERT((psrc[3] >> 6) == 0x2);

			//	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[iUnIndex] = ((psrc[0] & 0x7) << 18) | ((psrc[1] & 0x3f) << 12) |  ((psrc[2] & 0x3f) << 6) | (psrc[3] & 0x3f);
		}
		else if((ch >> 2) == 0x3e)	//	111110B
		{
			// 5 
			iCount = 5;

			ASSERT((psrc[1] >> 6) == 0x2);
			ASSERT((psrc[2] >> 6) == 0x2);
			ASSERT((psrc[3] >> 6) == 0x2);
			ASSERT((psrc[4] >> 6) == 0x2);

			// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[iUnIndex] = ((psrc[0] & 0x3) << 24) | ((psrc[1] & 0x3f) << 18) |  ((psrc[2] & 0x3f) << 12) | ((psrc[3] & 0x3f) << 6) |(psrc[4] & 0x3f);


		}
		else if((ch >> 1) == 0x7e)	//	1111110B
		{
			// 6 
			iCount = 6;

			ASSERT((psrc[1] >> 6) == 0x2);
			ASSERT((psrc[2] >> 6) == 0x2);
			ASSERT((psrc[3] >> 6) == 0x2);
			ASSERT((psrc[4] >> 6) == 0x2);
			ASSERT((psrc[5] >> 6) == 0x2);

			//	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[iUnIndex] = ((psrc[0] & 0x1) << 30) | ((psrc[1] & 0x3f) << 24) |  ((psrc[2] & 0x3f) << 18) | ((psrc[3] & 0x3f) << 12) | ((psrc[4] & 0x3f) << 6) | (psrc[5] & 0x3f);

		}
		else
		{
			ASSERT(0);
			break;
		}

		psrc += iCount;
		iUtf8Index += iCount;

		iUnIndex++;

	}

	pDst[iUnIndex] = 0;

	return iUnIndex;

}

//	unicode 32 / 16 -> utf 8,   
int ConvertUnicode2Utf8(IN const wchar_t* wszUnicode, IN size_t iUnLen, OUT const char* szUtf8, OUT int& iUtf8BufSize)
{
	kn_uint iUnIndex = 0;	//	
	unsigned char* pDst = (unsigned char*)szUtf8;

	while(wszUnicode[iUnIndex] != 0 && iUnIndex < iUnLen)
	{
		wchar_t wch = wszUnicode[iUnIndex];
		int iCharLen = 0;	//	utf8 

		if(wch <= 0x7F)
		{
			// 	U+00000000 – U+0000007F
			pDst[0] = wch;
			iCharLen = 1;
		}
		else if(wch <= 0x7FF)
		{
			//	U+00000080 – U+000007FF		|	110xxxxx 10xxxxxx  
			pDst[0] = (0x6 << 5) | (wch >> 6);
			pDst[1] = (0x2 << 6) | (wch & 0x3f);

			iCharLen = 2;

		}
		else if(wch <= 0xFFFF)
		{
			//	U+00000800 – U+0000FFFF		|	1110xxxx 10xxxxxx 10xxxxxx  
			pDst[0] = (0xe << 4) | (wch >> 12);
			pDst[1] = (0x2 << 6) | ((wch >> 6) & 0x3f);
			pDst[2] = (0x2 << 6) | (wch & 0x3f); 

			iCharLen = 3;

		}
		else if(wch <= 0x1FFFFF)
		{
			//	U+00010000 – U+001FFFFF		|	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[0] = (0x1e << 3) | (wch >> 18);
			pDst[1] = (0x2 << 6) | ((wch >> 12) & 0x3f);
			pDst[2] = (0x2 << 6) | ((wch >> 6) & 0x3f);
			pDst[3] = (0x2 << 6) | (wch & 0x3f);

			iCharLen = 4;


		}
		else if(wch <= 0x3FFFFFF)
		{
			//	U+00200000 – U+03FFFFFF		|	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[0] = (0x3e << 2) | (wch >> 24);
			pDst[1] = (0x2 << 6) | ((wch >> 18) & 0x3f);
			pDst[2] = (0x2 << 6) | ((wch >> 12) & 0x3f);
			pDst[3] = (0x2 << 6) | ((wch >> 6) & 0x3f);
			pDst[4] = (0x2 << 6) | (wch & 0x3f);

			iCharLen = 5;
		}
		else if(wch <= 0x7FFFFFFF)
		{
			//	U+04000000 – U+7FFFFFFF		|	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
			pDst[0] = (0x7e << 1) | (wch >> 30);
			pDst[1] = (0x2 << 6) | ((wch >> 24) & 0x3f);
			pDst[2] = (0x2 << 6) | ((wch >> 18) & 0x3f);
			pDst[3] = (0x2 << 6) | ((wch >> 12) & 0x3f);
			pDst[4] = (0x2 << 6) | ((wch >> 6) & 0x3f);
			pDst[5] = (0x2 << 6) | (wch & 0x3f);

			iCharLen = 6;
		}
		else
		{
			ASSERT(0);
		}

		iUnIndex++;
		pDst += iCharLen;



	}

	iUtf8BufSize = (pDst- (unsigned char*)szUtf8);

	//	
	*pDst = 0;

	return iUnIndex;

}


//	SJIS -> utf8 ,
int ConvertSJIS2Utf8(IN const char* pszSjis, IN int iSjisSize, OUT const char* pszUtf8)
{
	const int TEMP_SIZE = 512;
	wchar_t szTemp[TEMP_SIZE] = {0};
	wchar_t* pWBuf = szTemp;
	if(iSjisSize >= TEMP_SIZE)
	{
		pWBuf = new wchar_t[iSjisSize + 1];
		memset(pWBuf, 0, sizeof(wchar_t) * (iSjisSize + 1));
	}

	//	sjis -> unicode
	int iCharCount = ConvertSJIS2Unicode(pszSjis, iSjisSize, pWBuf);

	int iUtf8Size = 0;
	//	unicode -> utf8
	int iCharCount2 = ConvertUnicode2Utf8(pWBuf, iCharCount, pszUtf8, iUtf8Size);

	ASSERT(iCharCount == iCharCount2);

	if(iSjisSize >= TEMP_SIZE)
	{
		delete [] pWBuf;
	}
	
	return iCharCount2;


}

//	GBK -> utf8 ,
int ConvertGBK2Utf8(IN const char* pszGBK, IN int iGBKSize, OUT const char* pszUtf8)
{
	const int TEMP_SIZE = 512;
	wchar_t szTemp[TEMP_SIZE] = {0};
	wchar_t* pWBuf = szTemp;
	if(iGBKSize >= TEMP_SIZE)
	{
		pWBuf = new wchar_t[iGBKSize + 1];
		memset(pWBuf, 0, sizeof(wchar_t) * (iGBKSize + 1));
	}

	//	gbk -> unicode
	int iCharCount = ConvertGBK2Unicode(pszGBK, iGBKSize, pWBuf);

	int iUtf8Size = 0;
	//	unicode -> utf8
	int iCharCount2 = ConvertUnicode2Utf8(pWBuf, iCharCount, pszUtf8, iUtf8Size);

	if(iGBKSize >= TEMP_SIZE)
	{
		delete [] pWBuf;
	}

	ASSERT(iCharCount == iCharCount2);

	return iCharCount2;


}

//	API MultiByteToWideChar
//	lpMultiByteStr0cbMultiByte
int KNMultiByteToWideChar(
                          UINT CodePage, 
                          DWORD dwFlags, 
                          LPCSTR lpMultiByteStr, 
                          int cbMultiByte, 
                          LPWSTR lpWideCharStr, 
                          int cchWideChar 
                          )
{
	if (!lpMultiByteStr || !lpWideCharStr)
	{
		return 0;
	}

	int iMulLen = cbMultiByte;
	if (iMulLen  <= 0)
	{
		iMulLen = strlen(lpMultiByteStr);
	}

    if (cchWideChar == 0)
    {
        return (iMulLen * sizeof(wchar_t) + sizeof(wchar_t));
    }

    int ret = 0;
	
	if(CodePage == CP_ACP)
	{
		//	ANSI
		if(ANSI_CODE == CHARSET_GBK)
		{
			ret = ConvertGBK2Unicode ((char* )lpMultiByteStr, iMulLen, lpWideCharStr);
		}
		else if(ANSI_CODE == CHARSET_SJIS)
		{
			ret = ConvertSJIS2Unicode((char* )lpMultiByteStr, iMulLen, lpWideCharStr);
		}
		else
		{
			LOGE ("KNMultiByteToWideChar CodePage = CP_ACP ERROR ");
		}

	}
	else if(CodePage == CHARSET_GBK)
	{
		ret = ConvertGBK2Unicode ((char* )lpMultiByteStr, iMulLen, lpWideCharStr);
	}
	else if(CodePage == CHARSET_SJIS)
	{
		ret = ConvertSJIS2Unicode((char* )lpMultiByteStr, iMulLen, lpWideCharStr);
	}
	else if(CodePage == CP_UTF8)
	{
		ret = ConvertUtf82Unicode (lpMultiByteStr, iMulLen, lpWideCharStr);
	}
	else
	{
		LOGE ("KNMultiByteToWideChar ERROR CodePage = %d", CodePage);
	}

    // 	LOG ("ConvertGBK2Unicode r = %d, iMulLen = %d, lpMultiByteStr = %s, lpWideCharStr = %S", 
    // 		ret, iMulLen, lpMultiByteStr, lpWideCharStr);
    // 
    return ret;

}

//	API WideCharToMultiByte
int KNWideCharToMultiByte(
                          UINT CodePage, 
                          DWORD dwFlags, 
                          LPCWSTR lpWideCharStr, 
                          int cchWideChar, 
                          LPSTR lpMultiByteStr, 
                          int cbMultiByte, 
                          LPCSTR lpDefaultChar, 
                          LPBOOL lpUsedDefaultChar 
                          )
{



    int iWideLen = wcslen(lpWideCharStr);

    //	printf ("1. iWideLen  = %d, cchWideChar = %d\n", iWideLen, cchWideChar);

    //	If cbMultiByte is zero, the required size, in bytes, for a buffer that can receive the translated string indicates success. 
    if (cbMultiByte == 0)
    {
        return (iWideLen * 2  + 2);
    }


    if (cchWideChar >= 0 && cchWideChar < iWideLen)
    {
        iWideLen = cchWideChar;
    }

	int ret = 0;

	if(CodePage == CP_ACP)
	{
		//	ANSI
		if(ANSI_CODE == CHARSET_GBK)
		{
			ret = ConvertUnicode2GBK ((wchar_t* )lpWideCharStr, iWideLen, lpMultiByteStr);
		}
		else if(ANSI_CODE == CHARSET_SJIS)
		{
			ret = ConvertUnicode2SJIS((wchar_t* )lpWideCharStr, iWideLen, lpMultiByteStr);
		}
		else
		{
			LOGE ("KNMultiByteToWideChar CodePage = CP_ACP ERROR ");
		}

	}
	else if(CodePage == CHARSET_GBK)
	{
		ret = ConvertUnicode2GBK ((wchar_t* )lpWideCharStr, iWideLen, lpMultiByteStr);
	}
	else if(CodePage == CHARSET_SJIS)
	{
		ret = ConvertUnicode2SJIS((wchar_t* )lpWideCharStr, iWideLen, lpMultiByteStr);
	}
	else if(CodePage == CP_UTF8)
	{
		int iUtf8BufSize = 0;
		ret = ConvertUnicode2Utf8(lpWideCharStr, iWideLen, lpMultiByteStr, iUtf8BufSize);
	}
	else
	{
		LOGE ("KNMultiByteToWideChar ERROR CodePage = %d", CodePage);
	}


    // 	LOG ("ConvertUnicode2GBK r = %d, iWideLen = %d, lpMultiByteStr = %s, lpWideCharStr = %S", 
    // 		ret, iWideLen, lpMultiByteStr, lpWideCharStr);

    return ret;

}


void ConvertSlash(wchar_t* wsz)
{
    wchar_t* p = wsz;
    while (*p != 0)
    {
        if (*p == L'\\')
        {
            *p = L'/';
        }
        p++;
    }
}


void ConvertSlash(char* sz)
{
    char* p = sz;
    while (*p != 0)
    {
        if (*p == '\\')
        {
            *p = '/';
        }
        p++;
    }
}


void KnChar2WChar(IN const kn_char* pszKN, OUT wchar_t* pszWCHAR, IN int iOutLen)
{

#ifdef _UNICODE
    _tcscpy (pszWCHAR, pszKN);

#else

    MultiByteToWideChar(CP_ACP, 0, pszKN, -1, pszWCHAR, iOutLen);

#endif
}

kn_string Char2KnString(const char* sz)
{
	kn_string strRet;
#ifdef _UNICODE
	wchar_t wszTemp[1024] = {0};
	MultiByteToWideChar(CP_ACP, 0, sz, -1, wszTemp, 1024);
	strRet = wszTemp;
#else
	strRet = sz;
#endif

	return strRet;
}

kn_string Utf16ToKnString(const kn_char* pBuff, int iBytelen)
{

	wchar_t szTemp[1024] = {0};
	kn_string strRet;

#ifdef _UNICODE
	// pbuff -> wchar*
	if(sizeof(wchar_t) == 2)
	{
		strRet = (kn_char*)pBuff;

	}
	else if(sizeof(wchar_t) == 4)
	{
		// utf16 -> utf32
		int iCount = 0;
		WORD* pWord = (WORD*)pBuff;
		while (*pWord != 0 && iCount < 1023)
		{
			szTemp[iCount] = *pWord;

			pWord ++;
			iCount++;
		}

		strRet = szTemp;

	}

#else

	// ANSI
	int iCount = 0;
	WORD* pWord = (WORD*)pBuff;
	while (*pWord != 0 && iCount < 1023)
	{
		szTemp[iCount] = *pWord;

		pWord ++;
		iCount++;
	}

	char szMul[1024] = {0};

    WideCharToMultiByte(CP_ACP, 0, szTemp, -1,  szMul, 512, NULL, NULL);

	strRet = szMul;


#endif

	return strRet;

}


//	kn_string -> String 
void KnString2String(const kn_string& strKn, string& strMutiByte, UINT CodePage)
{
#ifdef UNICODE
	kn_int iLen = (strKn.length()+1)*6;
	char* szBuf = new char[iLen];
	memset(szBuf, 0, iLen * sizeof(char));

	WideCharToMultiByte(CodePage, NULL, strKn.c_str(), -1, szBuf, iLen-1, NULL, NULL);

	strMutiByte = szBuf;
	delete[] szBuf;
#else
	strMutiByte = strKn;
#endif

}
//	String -> kn_string 
void String2KnString(const string& strMutiByte, kn_string& strKn, UINT CodePage )
{
#ifdef UNICODE
	kn_int iLen = (strMutiByte.length()+1) *2;
	wchar_t* szBuf = new wchar_t[iLen];
	memset(szBuf, 0, iLen * sizeof(wchar_t));

	MultiByteToWideChar(CodePage, NULL, strMutiByte.c_str(), -1, szBuf, iLen-1);
	strKn = szBuf;
	delete[] szBuf;
#else
	strKn = strMutiByte;
#endif	
}

//	kn_string -> String 
string KnChars2String(const kn_char* p, UINT CodePage)
{
	const kn_string kstr = p;
	string strRet;
	KnString2String(kstr, strRet, CodePage);
	return strRet;
}

kn_string Chars2KnString(const char* p, UINT CodePage)
{
	const string str = p;
	kn_string strRet;
	String2KnString (str, strRet, CodePage);
	return strRet;
}
	

//  knstring  utf8string
string Knstring2Utf8String(const kn_string& wstr)
{
	char szTemp[1024] = {0};


	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), szTemp, sizeof(szTemp) - 1, NULL, NULL);

	string str = szTemp;
	return str;


}


//  knstring ANSIstring
string Knstring2String(const kn_string& wstr)
{
	char szTemp[1024] = {0};


	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), szTemp, sizeof(szTemp) - 1, NULL, NULL);

	string str = szTemp;
	return str;

}

// kn_string WChar2KnString(const kn_char* pwszKds, const int& iLen)
// {
// 	kn_string str;
// 
// #ifdef _UNICODE
// 	str = pwszKds;
// #else
// 	char szTemp[1024] = {0};
// 	//wcstombs ((char *)szFileName, strFileName.c_str(), strFileName.length());
// 	WideCharToMultiByte(CP_ACP, 0, pwszKds, iLen, szTemp, 1024, NULL, NULL);
// 	str = szTemp;
// #endif
// 
// 	return str;
// }

#ifdef WIN32
const wchar_t* ConvertWCHAR (const kn_char* pwszKds)
{
	return pwszKds;
}

#else

//	linuxwchar4 kds4
const wchar_t* ConvertWCHAR (const WORD* pwszKds)
{
	static wchar_t s_wsz[MAX_PATH] = {0};
	memset (s_wsz, 0, sizeof(s_wsz));

	WORD* pWord = (WORD*)pwszKds;
	wchar_t* pWChar = (wchar_t*)s_wsz;

	int iCount = 0;
    while (*pWord != 0 && iCount < MAX_PATH)
	{
		*pWChar = *pWord;
		pWord ++;
		pWChar ++;

		iCount++;
	}

	*pWChar = 0;

	return (wchar_t*)s_wsz;
}



#endif

// android  wcstombs , wcstol , 
//	android-ndk-r9\platforms\android-8\arch-arm\usr\include\wchar.h
size_t	kn_wcstombs(char * dst, const wchar_t * src, size_t len)
{

	size_t i = 0;
	while(i < len && src[i] != 0)
	{
		dst[i] = (char)src[i];
		i++;
	}

	//LOGI ("kn_wcstombs i = %d dst = %s", i, dst);
	return i;
}

size_t kn_mbstowcs(wchar_t * dst, const char * src, size_t len)
{

	size_t i = 0;
	while(i < len && src[i] != 0)
	{
		dst[i] = (wchar_t)src[i];
		i++;
	}
	//LOGI ("kn_mbstowcs i = %d, src = %s", i, src);

	return i;
}

const char* UnicodeToLocale(const wchar_t* _in, char* _out,size_t outlen)
{
	int ret = WideCharToMultiByte(CP_ACP , 0 , _in , (int)wcslen(_in) , _out , (int)outlen , NULL , NULL);
	return _out;
}


