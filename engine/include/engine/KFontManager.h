//  **************************************
//  File:        KFontManager.h
//  ***************************************
#ifndef K_FONT_MANAGER_H
#define K_FONT_MANAGER_H

#include "boost/unordered_map.hpp"
#include "KTextDrawable.h"

//#define	FontProperty boost::unordered_map<string,kn_string>
#define mapFontNameMap boost::unordered_map<string, RETypeface*>
#define mapFontFileMap boost::unordered_map<kn_string, RETypeface*>


typedef struct FontPropertyStruct{
	kn_string	strFileSize;
	kn_string	strFontFilePath;
	kn_string	strStyle;
	kn_string	strUniqueIdentifier;
	kn_string	strGlyphCount;
	kn_string	strUnitsPerEm;
	kn_string	strSmallestRectPixel;
	kn_string	strTypoAscender;
	kn_string	strTypoDescender;
	kn_string	strLineGap;
	kn_string	strMaxWidth;
	kn_string	strPlatform;
	kn_string	strEncoding;
	kn_string	strLanguage;
	kn_string	strEnglishName;
	kn_string	strEnglishSampleText;
	kn_string	strEnglishCopyright;
	kn_string	strEnglishTrademark;
	kn_string	strVersion;
	kn_string	strChineseName;
	kn_string	strChineseSampleText;
	kn_string	strChineseCopyright;
	kn_string	strChineseTrademark;

}stFontProperty;

#define mapFontPropMap boost::unordered_map<kn_string, stFontProperty*>


class API KFontManager
{
private:
	// 	boost::unordered_map<string, RETypeface*> m_FontNameMap;
	// 	boost::unordered_map<kn_string, RETypeface*> m_FontFileMap;
	mapFontNameMap m_FontNameMap;
	mapFontNameMap m_FontBoldNameMap; //粗体和非粗体需要区分
	mapFontFileMap m_FontFileMap;
	mapFontPropMap m_FontPropMap;

	std::vector<RETypeface*> m_FontVector;
public:
	KFontManager();
	~KFontManager();
	RETypeface* GetFontFromName( char* szName, SkTypeface::Style s = RETypeface::kNormal);
	RETypeface* GetFontFromFile(kn_string strFilePath);
	RETypeface* GetFontByID(int nFontID);
	stFontProperty* GetFontPropFromFile(kn_string strFilePath);

	int AddFont(RETypeface* pTypeface);

};

extern KFontManager* GetFontManagerSingleton();
extern void DeleteFontManagerSingleton();
#endif