﻿//  **************************************
//  File:        utility.cpp
//  ***************************************
#include "utility.h"

wstring UTF8ToUnicode( const string& str )
{
    wstring strValue;

    const int len = str.length();

    if ( len > 0 )
    {
        const int unicodeLen = ::MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, NULL, 0 );

        wchar_t * pUnicode = new  wchar_t[unicodeLen+1];
        memset( pUnicode, 0, (unicodeLen+1)*sizeof(wchar_t));

        ::MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen );
        strValue = ( wchar_t* )pUnicode;
        delete  []pUnicode;
    }

    return strValue;
}

string UnicodeToUTF8( const wstring& str )
{
    string strText;

    if ( str.length() == 0 )
    {
        return strText;
    }

    // wide char to multi char
    int iTextLen = ::WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL );
    if( iTextLen > 0 )
    {
        char* pElementText = new char[iTextLen + 1];
        memset(( void* )pElementText, 0, sizeof(char) * (iTextLen + 1));
        ::WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL );
        strText = pElementText;
        delete []pElementText;
    }

    return strText;
}

//stringwstring(UNICDOE)
std::wstring s2ws( const std::string& ansiStr)
{
    kn_string strValue( _T( "" ));
    const int len        = ansiStr.length();
    if(len == 0)
    {
        return strValue;
    }

    const int unicodeLen = MultiByteToWideChar( CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0 );

    wchar_t * pUnicode = new  wchar_t[unicodeLen+1];
    memset( pUnicode, 0, (unicodeLen+1)*sizeof(wchar_t));

    MultiByteToWideChar( CP_ACP, 0, ansiStr.c_str(), -1, (LPWSTR)pUnicode, unicodeLen );
    strValue = pUnicode;
    delete  []pUnicode;
    
    return strValue;
}

//stringwstringstring
kn_string s2ns( const std::string& ansiStr )
{
#ifdef _UNICODE
    return s2ws(ansiStr);
#else
    return ansiStr;
#endif
};

/**
 * kn_stringstring
 */
string ns2s( const kn_string& str )
{
    string strText;

    if ( str.empty())
    {
        return strText;
    }

#ifdef _UNICODE

    // wide char to multi char
    int iTextLen = WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL );

    char* pElementText = new char[iTextLen + 1];
    memset(( void* )pElementText, 0, sizeof(char) * (iTextLen + 1));

    WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL );
    strText = pElementText;
    delete[] pElementText;
    return strText;
#else
    return str;
#endif
}

/**
 *	boost::posix_time::ptimestring 2013-08-07 13:27:18
 */
string ptime2str(const boost::posix_time::ptime& ptm, bool is_iso_format )
{
    std::string strValue;

    if( !ptm.is_not_a_date_time())
    {
        strValue = to_iso_extended_string( ptm );

		if( !is_iso_format ) //MS Project to_iso_extended_string
		{
			int pos = strValue.find( "T" );
			if( -1 != pos )
			{
				string strDate = strValue.substr( 0, pos );
				string strTime = strValue.substr( pos+1 );
				if ( strTime != "00:00:00" )
				{   //000000,
					strValue = strDate + " " + strTime;
				}
				else
				{
					strValue = strDate;
				}
			}
		}       
    }

    return strValue;
}

/**
 *	boost::posix_time::ptimestring
 */
string ptime2datestr( boost::posix_time::ptime& ptm )
{
    std::string s = "";

    if( !ptm.is_not_a_date_time())
    {
        boost::gregorian::date d1 = ptm.date();
        s = to_iso_extended_string( d1 );
    }

    return s;
}

bool isTimeValid( kn_string &_time )
{
    std::vector <kn_string> result;
    kn_string strTime = kn_string( _time );
    boost::split( result, strTime, boost::is_any_of( _T( "/-: .T" )));
    if ( result.empty()) //
    {
        return false;
    }

    int resultsize = result.size();

    //
    if ( resultsize < 3 )
    {
        return false;
    }

    int itemp = 0;
    if ( resultsize == 3 )
    {
        itemp = _tstoi( result.at( 0 ).c_str());

        if ( itemp < 1900 )
        {
            return false;
        }

        itemp = _tstoi( result.at( 1 ).c_str());

        //
        if ((itemp > 12) || (itemp < 1))
        {
            return false;
        }

        itemp = _tstoi( result.at( 2 ).c_str());

        //
        if ((itemp > 31) || (itemp < 1))
        {
            return false;
        }

        _time += _T( " 00:00:00" );
    }
    else if ( resultsize >= 6 ) //66
    {
        itemp = _tstoi( result.at( 3 ).c_str());

        //
        if ((itemp > 24) || (itemp < 0))
        {
            return false;
        }

        itemp = _tstoi( result.at( 4 ).c_str());

        //
        if ((itemp > 60) || (itemp < 0))
        {
            return false;
        }

        itemp = _tstoi( result.at( 5 ).c_str());

        //
        if ((itemp > 60) || (itemp < 0))
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

/**
 *	boost::posix_time::ptimestring
 */
string ptime2timeStr( const boost::posix_time::ptime& time )
{
    std::string strValue = "";

    if ( !time.is_not_a_date_time())
    {
        boost::posix_time::time_duration td = time.time_of_day();
        strValue = to_simple_string( td );
        if( strValue == "00:00:00" )
        {
            strValue.clear();
        }
    }

    return strValue;
}

boost::posix_time::ptime timestr2ptime(kn_string& str_time )
{
    boost::posix_time::ptime time;

    if( !isTimeValid( str_time ))
    {
        return time;
    }

    try
    {
        kn_string str         = str_time;
        string::size_type pos = 0;
        while ((pos = str.find( _T( "/" ), pos )) != string::npos )
        {
            str.replace( pos, 1, _T( "-" ));
            pos++;
        }
        int index = str.find(_T("T"));
        if(index != kn_string::npos)
        {
            str.replace(index,1,_T( " " ));
        }
        time = boost::posix_time::time_from_string( ns2s( str ));
    } catch ( ... ) {
        return time;
    }

    return time;
}

/**
 *	intvector
 */
vector <int> splitString2IntVec( const char* lpstr )
{
    std::vector <int> result;

    if ( lpstr != NULL )
    {
        typedef boost::tokenizer <boost::char_separator <char> > Token;

        boost::char_separator <char> sep( "," );

        std::string str( lpstr );

        Token tok( str, sep );

        for ( Token::iterator it = tok.begin(); it != tok.end(); ++it )
        {
            result.push_back( atoi( it->c_str()));
        }
    }

    return result;
}

/**
 *	
 */
vector <kn_string> splitString2Vect( const kn_char* lpstr )
{
    std::vector <kn_string> result;
    if ( lpstr != NULL )
    {
        kn_string split_str( _T( "," ));
        kn_string strsrc = lpstr;
        boost::split( result, strsrc, boost::is_any_of( split_str ));
    }

    return result;
}

kn_string GetAttributeString( TiXmlElement* pElement, const char* name )
{
    kn_string strValue( _T( "" ));

    if ((NULL == pElement) || (NULL == name))
    {
        return strValue;
    }

    const char* pValue = pElement->Attribute( name );

#ifdef _UNICODE
    if ( pValue != NULL )
    {
        string ansiStr = pValue;

//  #ifdef WIN32
        strValue = UTF8ToUnicode( ansiStr );
//  #else

//        //TODO
//        wchar_t wszUnicode[256] = {0};
//        ConvertUtf82Unicode( strValue.c_str(), strValue.length(), wszUnicode );
//  #endif // WIN32
    }

#else
    if ( pValue != NULL )
    {
        strValue = pValue;
    }
#endif

    return strValue;
}


//kn_string GetXMLNodeValueString(TiXmlElement* pElement)
//{
//    kn_string strValue( _T( "" ));
//
//    if ((NULL == pElement))
//    {
//        return strValue;
//    }
//    //TODO
//    //childvalue
//    //childchild
//    if(!pElement->FirstChildElement())
//    {
//        return strValue;
//    }
//
//    if(!pElement->FirstChildElement()->FirstChildElement())//
//    {       
//        if(!pElement->FirstChildElement()->FirstChild())
//        {
//            return strValue;
//        }
//        const char*   pValue = pElement->FirstChildElement()->FirstChild()->Value();
//
//#ifdef _UNICODE
//        if ( pValue != NULL )
//        {
//            string ansiStr = pValue;
//
//#ifdef WIN32
//            strValue = UTF8ToUnicode( ansiStr );
//#else
//
//            //TODO
//            wchar_t wszUnicode[256] = {0};
//            ConvertUtf82Unicode( strValue.c_str(), strValue.length(), wszUnicode );
//#endif // WIN32
//        }
//
//#else
//        if ( pValue != NULL )
//        {
//            strValue = pValue;
//        }
//#endif
//
//        return strValue;
//    }
//    else//n
//    {
//        //
//        TiXmlElement* pEle = pElement->FirstChildElement()->FirstChildElement();
//        if(!pElement->FirstChildElement()->FirstChild())
//        {
//            return strValue;
//        }
//        string valuestr = pElement->FirstChildElement()->FirstChild()->Value();
//        TiXmlNode *pnode=  pElement->FirstChildElement()->IterateChildren(pElement->FirstChildElement()->FirstChild());
//
//        for(pEle; pEle != NULL;pEle = pEle->NextSiblingElement())
//        {
//            valuestr += pEle->FirstChild()->Value();
//            if(pnode )
//            {
//                string secondestr ;
//                TiXmlNode * ptempnode=pElement->FirstChildElement()->IterateChildren (pnode);
//                if(ptempnode)
//                {
//                    if(ptempnode->Value())
//                    {
//                        secondestr = ptempnode->Value();
//                    }
//                }
//                if((!secondestr.empty())&&(secondestr.find( "Font")== string::npos))//WPS
//                {
//                    valuestr += secondestr;
//                    pnode = pElement->FirstChildElement()->IterateChildren(ptempnode);
//                }
//            }
//        }
//        const char*  pValue = valuestr.c_str();
//#ifdef _UNICODE
//        if ( pValue != NULL )
//        {
//            string ansiStr = pValue;
//
//#ifdef WIN32
//            strValue = UTF8ToUnicode( ansiStr );
//#else
//
//            //TODO
//            wchar_t wszUnicode[256] = {0};
//            ConvertUtf82Unicode( strValue.c_str(), strValue.length(), wszUnicode );
//#endif // WIN32
//        }
//
//#else
//        if ( pValue != NULL )
//        {
//            strValue = pValue;
//        }
//#endif
//
//        return strValue;
//    }
//
//}
//xmlInt
int GetAttributeInt( TiXmlElement* pElement, const char* name )
{
    if ((NULL == pElement) || (NULL == name))
    {
        return 0;
    }
    else
    {
        const char* pValue = pElement->Attribute( name );
        if ( NULL == pValue )
        {
            return 0;
        }
        else
        {
            return atoi( pValue );
        }
    }
}

//xmlStringintVector
std::vector <int> GetAttribute2IntVector( TiXmlElement* pElement, const char* name )
{
    vector <int> result;
    if ((!pElement) || (!name))
    {
        return result;
    }

    const char * group = pElement->Attribute( name );
    if ( !group )
    {
        return result;
    }

    return splitString2IntVec( group );
}

//intVectorstring
string IntVector2str( const vector <int>& vec )
{
    string tstr = ("");

    if ( vec.empty())
    {
        return tstr;
    }

    vector <int>::const_iterator iter;
    for ( iter = vec.begin(); iter != vec.end(); iter++ )
    {
        int singlenum = *iter;
        char buf[10];
        sprintf( buf, "%d,", singlenum );
        tstr += buf;
    }

    string str = tstr.substr( 0, tstr.length()-1 );
    return str;
}

//xmstringunicodeutf-8
void SetAttributeStr( TiXmlElement* pElement, const char* name, const kn_string & value )
{
    if ( pElement && name )
    {
        string strValue = UnicodeToUTF8( value );
        pElement->SetAttribute( name, strValue.c_str());
    }
}

//xmstringunicodeutf-8
void SetAttributeStr( TiXmlElement* pElement, const char* name, const char* value )
{
    if ( pElement && name && value)
    {
        pElement->SetAttribute( name, UnicodeToUTF8( s2ws(value) ).c_str());
    }
}

//xml eg:<Name></Name>
kn_string getXmlElementValue( TiXmlElement* p_element )
{
    kn_string strValue;
	if( p_element )
	{
		TiXmlNode * p_child_elem = p_element->FirstChild();
		if(p_child_elem)
		{
			const char* value = p_child_elem->Value();
			if( value != NULL)
			{
				const string str = value;
                strValue = UTF8ToUnicode( str );
			}
		}
	}
	return strValue;
}

//
kn_string getChildNodeText(TiXmlElement* p_parent_elem , const char* elem_name)
{
    kn_string strValue;

    if(NULL != p_parent_elem && elem_name != NULL)
    {
        TiXmlElement* child_elem = p_parent_elem->FirstChildElement( elem_name );
        strValue = getXmlElementValue(child_elem);
    }

    return strValue;
}

//xml
int getXmlNodeValue(TiXmlElement* p_element )
{
    int i_value(0);

    if( p_element )
	{
		TiXmlNode * p_child_elem = p_element->FirstChild();
		if(p_child_elem)
		{
			const char* value = p_child_elem->Value();
			if( value != NULL)
			{
                i_value = atoi(value);
			}
		}
	}

    return i_value;
}

//
int getChildNodeValue(TiXmlElement* p_parent_elem, const char* elem_name )
{
    int i_value(0);
    if(NULL != p_parent_elem && elem_name != NULL)
    {
        TiXmlElement* child_elem = p_parent_elem->FirstChildElement( elem_name );
        i_value = getXmlNodeValue(child_elem);
    }
    return i_value;
}


//XML NODE,NODE
TiXmlElement* add_node(TiXmlElement* parent, const char* node_name,  const char* value)
{
    if(!node_name)
    {
        return NULL;
    }

    TiXmlElement *pEle = new TiXmlElement(node_name);
    if(!pEle)
    {
        return NULL;
    }

    TiXmlText *pContent = NULL;

    if(value != NULL )
    {
        pContent = new TiXmlText( value );
    }
    else
    {
        pContent = new TiXmlText("");
    }

    if(pContent)
    {
        pEle->LinkEndChild(pContent);
    }

    if(parent)
    {
        parent->LinkEndChild(pEle);
    }

    return pEle;
}

TiXmlElement* add_node(TiXmlElement* parent, const char* node_name, const kn_string & value)
{
    if((!node_name))
    {
        return NULL;
    }

    TiXmlElement *pEle = new TiXmlElement(node_name);
    if( pEle )
    {
        #ifdef _UNICODE 
            TiXmlText *pContent = new TiXmlText( UnicodeToUTF8(value).c_str() );
        #else
            TiXmlText *pContent = new TiXmlText( value.c_str() );
        #endif
        
        if(pContent)
        {
            pEle->LinkEndChild(pContent);
        }
    }

    if(parent)
    {
        parent->LinkEndChild(pEle);
    }
    return pEle;
}

boost::posix_time::ptime excelTime2ptime( int i_date,double d_time )
{
    boost::posix_time::ptime time;

    if(i_date < 2 || d_time < 0)
    {
        return time;
    }
    try
    {
        int hours = d_time*24;
        int minutes = d_time*24*60-hours*60;
        int seconds = d_time*24*60*60-minutes*60-hours*60*60;
        char szBuff[64] = {0};
        sprintf( szBuff, " %02d:%02d:%02d", hours, minutes, seconds );

        boost::gregorian::date basedate(1900,01,01);
        boost::gregorian::date datevalue = basedate + boost::gregorian::days(i_date - 2);
        string datestr = to_simple_string(datevalue);
        datestr += szBuff;
        time = boost::posix_time::time_from_string( ( datestr ));
    } 
    catch ( ... ) 
    {
        return time;
    }

    return time;
}

kn_string GetTextString( TiXmlElement* pElement )
{
    kn_string strValue( _T( "" ));

    if (NULL == pElement)
    {
        return strValue;
    }

    const char* pValue = pElement->GetText();

#ifdef _UNICODE
    if ( pValue != NULL )
    {
        string ansiStr = pValue;

 // #ifdef WIN32
        strValue = UTF8ToUnicode( ansiStr );
 // #else

        //TODO
//        wchar_t wszUnicode[256] = {0};
//        ConvertUtf82Unicode( strValue.c_str(), strValue.length(), wszUnicode );
//  #endif // WIN32
    }

#else
    if ( pValue != NULL )
    {
        strValue = pValue;
    }
#endif

    return strValue;
}

kn_string wipeOutStringLineBreak( const kn_string& str )
{
	kn_string get_str = _T("");
	for (kn_int i = 0; i <  str.size(); ++i)
	{
		if (str[i] != '\n')
		{
			get_str += str[i];
		}
	}
	return get_str;
}
