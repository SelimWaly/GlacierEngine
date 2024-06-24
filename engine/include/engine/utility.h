//  **************************************
//  File:        utility.h
//  ***************************************
#ifndef utility_h__
#define utility_h__

#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
//#include <tchar.h>
#include <functional>
#include <boost/token_iterator.hpp>
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "CharSet.h"

//WINERROR.H
#ifndef _WINERROR_
#define NO_ERROR                         0L      // dderror
#define ERROR_FILE_NOT_FOUND             2L   
#define ERROR_PATH_NOT_FOUND             3L
#define ERROR_INVALID_PARAMETER          87L    // dderror
#define ERROR_FILE_INVALID               1006L  
#define ERROR_FUNCTION_FAILED            1627L  
#define ERROR_CREATE_FAILED              1631L
#endif

//
using std::vector;
using std::string;
using std::wstring;

#ifdef _UNICODE
typedef wchar_t kn_char;
#else
typedef char kn_char;
#endif // _UNICODE
typedef std::basic_string <kn_char> kn_string;

#ifdef WIN32
 #undef MultiByteToWideChar   //MultiByteToWideChar
 #undef WideCharToMultiByte   //MultiByteToWideChar
#endif // WIN32

wstring UTF8ToUnicode( const string& str );

string UnicodeToUTF8( const wstring& str );

//stringkn_string
kn_string s2ns( const std::string& ansiStr );

//kn_stringstring
string ns2s( const kn_string& str );

std::wstring s2ws( const std::string& ansiStr);

//ptimestring 2013-08-07 13:27:18
string ptime2str(const boost::posix_time::ptime& ptm, bool is_iso_format = false );

//ptime
string ptime2datestr( boost::posix_time::ptime& ptm );

//ptime
string ptime2timeStr(const boost::posix_time::ptime& time ) ;

boost::posix_time::ptime timestr2ptime(kn_string& str_time ) ;

bool isTimeValid( kn_string &_time );

//intvector
vector <int> splitString2IntVec( const char* lpstr );

//
vector <kn_string> splitString2Vect( const kn_char* lpstr ) ;

//
kn_string wipeOutStringLineBreak(const kn_string& str);

kn_string GetAttributeString( TiXmlElement* pElement, const char* name );

kn_string GetXMLNodeValueString(TiXmlElement* pElement);
//xmlInt
int GetAttributeInt( TiXmlElement* pElement, const char* name ) ;

//xmlStringintVector
std::vector<int> GetAttribute2IntVector( TiXmlElement* pElement, const char* name );

string IntVector2str( const vector <int>& vec );  

//xmstringunicodeutf-8
void SetAttributeStr( TiXmlElement* pElement, const char* name, const kn_string & value );

void SetAttributeStr( TiXmlElement* pElement, const char* name, const char* value );
//xml
kn_string getXmlElementValue( TiXmlElement* p_element );

//
kn_string getChildNodeText(TiXmlElement* p_parent_elem , const char* elem_name);

//xml
int getXmlNodeValue(TiXmlElement* p_element );

//
int getChildNodeValue(TiXmlElement* p_parent_elem , const char* elem_name );

//Excelptimeexcel1900  1  1 
boost::posix_time::ptime excelTime2ptime(int i_date,double d_time);

//XML NODE,NODE
TiXmlElement* add_node(TiXmlElement* parent, const char* node_name,  const char* value);

TiXmlElement* add_node(TiXmlElement* parent, const char* node_name, const kn_string & value);
//
kn_string GetTextString( TiXmlElement* pElement );
// TEMPLATE STRUCT less_nprjobject
// 
template<class _Ty>
struct less_nprjobject
    : public binary_function<_Ty, _Ty, bool>
{	// functor for operator<
    bool operator()(const _Ty& _Left, const _Ty& _Right) const
    {	// apply operator< to operands
        return (_Left.getId() < _Right.getId() );
    }
};

#endif // utility_h__
