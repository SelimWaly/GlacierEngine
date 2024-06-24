﻿//  **************************************
//  File:        KStringManager.h
//  ***************************************
#ifndef K_STRING_MANAGER_H
#define K_STRING_MANAGER_H

#include "NE_type.h"
#include "boost/unordered_map.hpp"
#include "CharSet.h"

#ifdef WIN32
#include <comdef.h>
#endif
#define  mapStringMap boost::unordered_map<kn_string, kn_string>

#define LAN_CN 0
#define LAN_EN 1
#define LAN_JP 2
class API KStringManager
{
private:


		mapStringMap m_StringManagerMap;
		kn_bool LoadStringFromFile(kn_string strFilePath);

public:
			KStringManager(kn_string strFilePath);
		~KStringManager();
		
		kn_string GetStringByID(kn_string nStringKey);
		kn_bool AddString(kn_string sKey,kn_string sValue);
		/**
		* stringkn_string
		*/
		inline kn_string s2ns(const std::string& s)
		{

            return Char2KnString(s.c_str());
//#ifdef _UNICODE
//			_bstr_t t = s.c_str();
//			wchar_t*        pwchar = (wchar_t*)t;
//			std::wstring    result = pwchar;
//			return result;
//#else
//			return s;
//#endif
		};


};

 KStringManager* getStringManager();
 void releaseStringManager();

#endif
