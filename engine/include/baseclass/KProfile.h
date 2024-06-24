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

	// 打开配置文件
    kn_int Open(const kn_string& strFilename);
	// 关闭配置文件
    void Close(void);

	// 复位文件位置
    kn_int Reset();
	// 保存文件当前位置
    kn_int Mark();
	// 返回先前保存的位置
    kn_int Back();

	// 取得Section名称
    kn_int GetSection(const char* pKey);
	// 读取指定名称的字符串
    kn_int GetString(const char* pKey, char* pBuff, kn_int nCount);
	// 读取指定名称的整型值
    kn_int GetValue(const char* pKey, kn_int& nVvalue);
    // 读取指定名称的整型值
    kn_int GetValue(const char* pKey, kn_ulong& nVvalue);
	// 读取指定名称的双精度值
    kn_int GetValue(const char* pKey, kn_double& dValue);

	// 拆分字符串
    static void Split(const char *pBuff, ...);

	// 读取一行
	kn_int GetLine(char* pBuff, kn_int nCount);
protected:

	// 字符串比较，不区分大小写
    kn_int strnicmp2(const char* pStr1, const char* pStr2, kn_int nCount) const;

    KFile m_File;		// 配置文件
    kn_ulong m_ulMark;	// 保存文件读取的位置
};


#ifdef NAVI_ENGINE
 
#endif

#endif // _KPROFILE_H__
