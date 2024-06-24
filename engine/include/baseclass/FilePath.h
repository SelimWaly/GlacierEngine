//  **************************************
//  File:        FilePath.h
//  ***************************************


#ifndef _FILEPATH_H_
#define _FILEPATH_H_

#include "NE_pubhead.h"

struct KNMODULEPATH
{
    kn_string strCongigPath;
    kn_string strSavePath;
    kn_string strLogPath;
};

enum KModuleEnum
{
    ME_UNION,
    ME_MAPDISP,
    ME_POI,
    ME_POSITION,
    ME_ROUTEPLAN,
    ME_GUIDE,
};

typedef map<KModuleEnum, KNMODULEPATH> KModulePathMap;



KNAPI void SetDataPath(IN const kn_char *path);
KNAPI const kn_char* GetDataPath(void);

KNAPI void SetSavPath(IN const kn_char *path);
KNAPI const kn_char* GetSavPath(void);

KNAPI void SetSavUserPath(IN const kn_char *path);
KNAPI const kn_char* GetSavUserPath(void);

// 
KNAPI void GetFilePath(INOUT kn_string& strPath);
// 
KNAPI void GetPath(const kn_char *allpath, kn_char *path);

KNAPI void SetCurrentPath(IN const kn_char *path);
KNAPI const kn_char*  GetCurrentPath();

KNAPI void SetDataFile(IN const kn_char *path);
KNAPI const kn_char* GetDataFile(void);

// Set/Get
KNAPI void SetConfigPath(const kn_char* szPath, KModuleEnum eModule = ME_UNION);
KNAPI const kn_char* GetConfigPath(KModuleEnum eModule);

// Set/Get
KNAPI void SetSavePath(const kn_char* szPath, KModuleEnum eModule = ME_UNION);
KNAPI const kn_char* GetSavePath(KModuleEnum eModule);

// Set/Get
KNAPI void SetLogPath(const kn_char* szPath, KModuleEnum eModule = ME_UNION);
KNAPI const kn_char* GetLogPath(KModuleEnum eModule);

bool IsDirectoryExist(LPCTSTR pszDir);

bool CreateDirectory(LPCTSTR pszDir);

kn_bool IsFileExist(const kn_char* strPath);
/**
* ()
*/

void GetFilesArrayOfDirectory(IN const kn_char* strFileName, 
							  IN const kn_char* strFileType,
							  INOUT vector<kn_string>&vStrFileNameArray);

//
kn_int knDeleteFile(const kn_char* sz);

//	0
kn_int ClearDir(kn_char* szUpdatesrc);

//#ifdef NAVI_ENGINE
// 
//#endif

#endif // _FILEPATH_H_
