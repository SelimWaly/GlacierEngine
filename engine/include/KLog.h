//  **************************************
//  File:        KLog.h
//  ***************************************

#ifndef _KLOG_H_
#define _KLOG_H_
#include "Platform.h"
void BeginLog();

void EndLog();

void WriteLogNoTime(const char *szFormat, ...);

void WriteLog(const char *szFormat, ...);

void LogAssert(char* szFileName, long iLine, char* szFuncName);

void MyTrace(LPCTSTR lpsz, ...);
//  auto log
class API AutoLog
{
private:

    char m_szFuncName[256];
public:

    AutoLog(const char* szFuncName);


     ~AutoLog();

};

#if defined(QT_WINDOWS_LIB) || defined(QT_LIB) || defined(QT_LINUX_LIB)
void LogInfo(const char *szFormat, ...);

void LogInfo(const wchar_t *szFormat, ...);
#endif

#define LOG WriteLog
#define LOG_ASSERT LogAssert
#define LOGNT WriteLogNoTime
#define LOG_FUNC AutoLog logAutoFuncc (__FUNCTION__) ;

#endif // _KLOG_H_
