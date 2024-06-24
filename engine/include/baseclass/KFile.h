//  **************************************
//  File:        KFile.h
//  **************************************

#if !defined(EA_500EDE1E_3489_444e_8C79_0F9A07CDB0FC__INCLUDED_)
#define EA_500EDE1E_3489_444e_8C79_0F9A07CDB0FC__INCLUDED_


#include "NE_pubhead.h"
#include "CharSet.h"
#include "NE_error.h"

typedef FILE* KNFILEHANDLE;

/**
 * 
 * @author zhifangh
 * @version 1.0
 * @created 26-Mar-2010 16:42:38
 */
class API KFile
{

public:

	/**
	 * 
	 */
	KFile();
	/**
	 * 
	 */
    virtual ~KFile();

	/**
	 *  API:CreateFile()
	 * 
	 * @param strFileName    
	 * @param dwDesiredAccess
	 * @param dwShareMode    (share/exclusive)
	 * @param dwCreationDisposition
	 * @param dwFlagsAndAttributes 
	 */
	virtual KNRESULT Open(IN const kn_string& strFileName, IN kn_dword dwDesiredAccess = GENERIC_READ, IN kn_dword dwShareMode = FILE_SHARE_READ, IN kn_dword dwCreationDisposition = OPEN_EXISTING, IN kn_dword dwFlagsAndAttributes = FILE_ATTRIBUTE_READONLY);
	/**
	 * 
	 */
	virtual KNRESULT Close();
	/**
	 * 
	 */
	virtual const KNFILEHANDLE& GetHandle() const;
	/**
	 * 
	 * 
	 * @param ulSize    ulSize
	 */
	virtual KNRESULT GetSize(IN kn_ulong& ulSize);
	/**
	 * 
	 */
	virtual kn_long Tell();
	/**
	 * 
	 * 
	 * @param lOffset    
	 * @param dwMoveMethod    SEEK_SET-  SEEK_CUR-  SEEK_END-
	 */
	virtual KNRESULT Seek(IN kn_long lOffset, IN kn_dword dwMoveMethod);
	/**
	 * 
	 */
	virtual KNRESULT Flush();
	/**
	 * 
	 */
	kn_bool IsOpen() const;
	/**
	 * 
	 * 
	 * @param strFileName
	 */
	kn_bool IsExist(IN string strFileName);
	/**
	 * kn_byte
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_byte& value);
	/**
	 * char
	 * 
	 * @param value    
	 */
	//virtual KNRESULT Read(IN char& value);
	/**
	 * kn_char
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_char& value);
	/**
	 * kn_word
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_word& value);
	/**
	 * kn_dword
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_dword& value);
	/**
	 * kn_short
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_short& value);
	/**
	 * kn_int
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_int& value);
	/**
	 * kn_long
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_long& value);
	/**
	 * kn_float
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_float& value);
	/**
	 * kn_double
	 * 
	 * @param value    
	 */
	virtual KNRESULT Read(IN kn_double& value);
	/**
	 * 
	 * 
	 * @param pBuff    
	 * @param ulSize    
	 */
	virtual KNRESULT Read(IN void* pBuff, IN const kn_ulong ulSize);
	/**
	 * 
	 * @param pBuff
	 * @param ulSizeToRead
	 * @param ulSizeReturn    ulSizeReturn
	 */
	virtual KNRESULT Read(IN void* pBuff, IN const kn_ulong ulSizeToRead, IN kn_ulong& ulSizeReturn);
	/**
	 * kn_word
	 * 
	 * @param value    
	 */
	virtual KNRESULT ReadReverse(IN kn_word& value);
	/**
	 * kn_dword
	 * 
	 * @param value    
	 */
	virtual KNRESULT ReadReverse(IN kn_dword& value);
	/**
	 * kn_byte
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_byte& value);
	/**
	 * char
	 * 
	 * @param value    
	 */
	//virtual KNRESULT Write(IN char& value);
	/**
	 * kn_char
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_char& value);
	/**
	 * kn_word
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_word& value);
	/**
	 * kn_dword
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_dword& value);
	/**
	 * kn_short
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_short& value);
	/**
	 * kn_int
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_int& value);
	/**
	 * kn_long
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_long& value);
	/**
	 * kn_float
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_float& value);
	/**
	 * kn_double
	 * 
	 * @param value    
	 */
	virtual KNRESULT Write(IN kn_double& value);
	/**
	 * 
	 * 
	 * @param pBuff    
	 * @param ulSize    
	 */
	virtual KNRESULT Write(IN const void* pBuff, IN const kn_ulong ulSize);

    // >>
    KFile& operator >> (kn_bool &value);
    KFile& operator >> (kn_byte &value);
    //KFile& operator >> (char &value);
    KFile& operator >> (kn_char &value);
    KFile& operator >> (kn_short &value);
    KFile& operator >> (kn_ushort &value);
    KFile& operator >> (kn_int &value);
    KFile& operator >> (kn_uint &value);
    KFile& operator >> (kn_long &value);
    KFile& operator >> (kn_ulong &value);
    KFile& operator >> (kn_float &value);
    KFile& operator >> (kn_double &value);
    KFile& operator >> (string& str);
    KFile& operator >> (wstring& wstr);
    KFile& operator >> (char *&value);
    KFile& operator >> (wchar_t *&value);

    // <<
    KFile& operator << (const kn_bool value);
    KFile& operator << (const kn_byte value);
    //KFile& operator << (const char value);
    KFile& operator << (const kn_char value);
    KFile& operator << (const kn_short value);
    KFile& operator << (const kn_ushort value);
    KFile& operator << (const kn_int value);
    KFile& operator << (const kn_uint value);
    KFile& operator << (const kn_ulong value);
    KFile& operator << (const kn_long value);
    KFile& operator << (const kn_float value);
    KFile& operator << (const kn_double value);
    KFile& operator << (const string& str);
    KFile& operator << (const wstring& wstr);
    KFile& operator << (const char *value);
    KFile& operator << (const wchar_t *value);

protected:

	/**
	* 
	*/
	virtual kn_long TryReOpenFile();

protected:
	/**
	 * 
	 */
	kn_string m_strName;
	/**
	 * 
	 */
	kn_ulong m_ulSize;
	/**
	 * 
	 */
	KNFILEHANDLE m_hFile;
	/**
	 * 
	 */
	kn_long m_lCursor;
	/**
	 * 
	 */
	kn_bool m_bIsOpen;

	/**
	* fopen mode
	*/	
	kn_char m_szMode[8];

	/**
	* ftell position
	*/		
	kn_long m_lPostion;

	/**
	* ,
	*/	
	kn_string m_strRealFileName;

};
#endif // !defined(EA_500EDE1E_3489_444e_8C79_0F9A07CDB0FC__INCLUDED_)
