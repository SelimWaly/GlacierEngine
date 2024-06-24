//  **************************************
//  File:        KConfigManager.h
//  ***************************************
#ifndef K_CONFIG_MANAGER_H
#define K_CONFIG_MANAGER_H

#include "NE_type.h"
#include "boost/unordered_map.hpp"
#ifdef WIN32
#include <comdef.h>
#endif
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include "KProfile.h"
#include <boost/algorithm/string.hpp>
#include "utility.h"
#include "tinyxml.h"

class API KConfigManager
{
private:

		TiXmlDocument *m_pXmldoc;
		
		// config
		TiXmlElement* m_oneLayerElement;	//
		TiXmlElement* m_twoLayerElement;	//()
		/**
		* 
		*/
		kn_bool loadConfigFromFile(kn_string strFilePath);

		string m_file;
		int m_language;
		//
		kn_string m_app_path;
public:
		KConfigManager(kn_string strFilePath);

		~KConfigManager();

		/**
		* 
		*/
		void saveConfig();
		kn_string getAppPath();
		/**
		* 
		*/
		kn_bool setConfig(const kn_string strValue,const kn_string str);
		kn_bool setConfig(const kn_string strValue,const kn_int v);

		/**
		* 
		*/
		kn_string getConfig(const kn_string str);
		kn_int getIntConfig(const kn_string str);
		kn_int getLanguage();
		kn_string getLanguageImagePath();

		/**
		* ()
		*/
		void GetVectorConfig(const kn_string& str, vector<kn_string>& vHistory );
		
		/**
		* 
		*/
		kn_bool addHistoryConfig(const kn_string& str, const kn_string& strHistory );
};

 KConfigManager* getConfigManager();
 void releaseConfigManager();

#endif
