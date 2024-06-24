//  **************************************
//  File:        NE_error.h
//  ***************************************

// WinError.h

#ifndef _NE_ERROR_H_
#define _NE_ERROR_H_

#include "NE_type.h"

// 
// #define  RESULT(CLASS, COM, FAC, CODE) (KNRESULT)((class API API << 29) | (COM << 25) | (FAC << 16) | CODE) 

// 0(0x00000000)
#define  RESULT_OK KNRESULT(EC_SUCCESS, SC_NONE, EF_NONE, KN_ERROR_NONE) 

// F(0xFFFFFFFF)
#define  RESULT_UNKNOW KNRESULT(EC_UNKNOW, SC_UNKNOW, EF_UNKNOW, KN_ERROR_UNKNOW)

//
//  Values are 32 bit values layed out as follows:
//
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-----+-------+-----------------+-------------------------------+
//  |Class|   Com |     Facility    |               Code            |
//  +-----+-------------------------+-------------------------------+
//
//  where
//
//      class API API - is the class API code
//
//          000 - Success
//          001 - Informational
//          010 - Warning
//          011 - Error
//
//      Com - is the component code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

// .
struct KNRESULT
{
    kn_dword dwCode     : 16;  // .
    kn_dword dwFacility : 9;   // .
    kn_dword dwComponent : 4;  // .
    kn_dword dwclass  : 3;   // .

    KNRESULT(kn_dword dwResult)	
    {
        dwclass = (dwResult >> 29) & 0x7;
        dwComponent = (dwResult >> 25) & 0xF;
        dwFacility = (dwResult >> 16) & 0x1FF;
        dwCode = dwResult & 0xFFFF;
    }

    KNRESULT(kn_dword A, kn_dword B, kn_dword C, kn_dword D)
    {
        dwclass = A;
        dwComponent = B;
        dwFacility = C;
        dwCode = D;
    }

    KNRESULT()
    {
        dwclass = 0;
        dwComponent = 0;
        dwFacility = 0;
        dwCode = 0;
    }

    operator kn_dword()
    {
        return ((dwclass << 29) | (dwComponent << 25) | (dwFacility << 16) | dwCode);
    }

};

// 
KNRESULT GetLastErrorCode();

// 
void SetLastErrorCode(KNRESULT theErrorCode);

kn_bool operator==(const KNRESULT& lhs, const KNRESULT& rhs);

kn_bool operator!=(const KNRESULT& lhs, const KNRESULT& rhs);


// . 3 Bits : 8. << 29
enum KNERRORCLASS
{
    EC_SUCCESS     = 0,		// .
    EC_INFORMATION = 1,		// .
    EC_WARNING     = 2,		// .
    EC_ERROR       = 3,		// .
    EC_UNKNOW      = 0x7,	// 
};

// . 4 Bits : 16. << 25
enum KNSYSCOM
{
    SC_NONE				= 0,
    SC_UNKNOW			= 0xF,	// 
    SC_GLACIER				= 1,	// HMI
	SC_BASELIB			= 2
};

// . 9 Bits : 512. << 16
enum KNERRORFACILITY
{
    EF_NONE		  = 0,
    EF_UNKNOW     = 0x1FF,	// 
    EF_MEMORY     = 1,		// .
    EF_FILE       = 2,		// .
    EF_SERIALPORT = 3,		// .
	EF_PROTOCOL   = 4,		// .
};

// . 16Bits.
enum KNERRORSTATUSCODE
{
    KN_ERROR_NONE								= 0,		// 

    KN_ERROR_UNKNOW								= 0xFFFF,	// 

    // Memory.
    KN_ERROR_NOT_ENOUGH_MEMORY					= 0xFFFF,	// .

    // File.
    KN_ERROR_OPEN_FAILED						= 110,		// .
    KN_ERROR_OPEN_REPEAT,                                   // 
    KN_ERROR_READ_FAIL,                                     // 
    KN_ERROR_WRITE_FAIL,                                    // 
    KN_ERROR_NOT_OPEN,                                      // 

    // Serial Port.
    KN_ERROR_EXECUTE_EXTENT_COMMAND_INCOMPLETE	= 800,		// .

    KN_ERROR_WRITE_SERIAL_PORT_EXCEPTION		= 801,		// .

	// Protocol.
	KN_ERROR_PROTOCOL_PARM_ERROR				= 900,		// .
	KN_ERROR_PROTOCOL_DB_ERROR					= 901,		// DB.
	KN_ERROR_PROTOCOL_UNKNOW_ERROR				= 902,		// .
	KN_ERROR_PROTOCOL_DBCONNECT_ERROR			= 980,		// DB.
	KN_ERROR_PROTOCOL_DBGET_ERROR				= 981,		// DB.
	KN_ERROR_PROTOCOL_DBADD_ERROR				= 982,		// DB.
	KN_ERROR_PROTOCOL_DBUPDATE_ERROR			= 983,		// DB.
	KN_ERROR_PROTOCOL_DBDELETE_ERROR			= 984,		// DB.
	KN_ERROR_PROTOCOL_SESSIONDISCONNECTED_ERROR	= 910,		// session .
	KN_ERROR_PROTOCOL_ACCOUNTPASSWORD_ERROR		= 911,		// account/password.
	KN_ERROR_PROTOCOL_AIDDISMATCHDID_ERROR		= 912,		// accountID.
	KN_ERROR_PROTOCOL_ACCOUNTLOGICDELETE_ERROR	= 913,		// account.
	KN_ERROR_PROTOCOL_ACCOUNTEXIST_ERROR		= 915,		// account.
	KN_ERROR_PROTOCOL_DEVICEIDEXIST_ERROR		= 916,		// ID.
	KN_ERROR_PROTOCOL_ACCOUNTLENGTH_ERROR		= 917,		// accounterror.
	KN_ERROR_PROTOCOL_PASSWORDLENGTH_ERROR		= 918,		// passworderror.
	KN_ERROR_PROTOCOL_NICKNAMELENGTH_ERROR		= 919,		// Nick nameerror.
	KN_ERROR_PROTOCOL_ACCOUNTROLE_ERROR			= 920,		// accounterror.
	KN_ERROR_PROTOCOL_PASSWORDROLE_ERROR		= 921,		// passworderror.
	KN_ERROR_PROTOCOL_NICKNAMEROLE_ERROR		= 922,		// Nick nameerror.
	KN_ERROR_PROTOCOL_NICKNAMEEXIST_ERROR		= 923,		// Nick name.
	KN_ERROR_PROTOCOL_NOFRIEND_ERROR			= 930,		// friend.
	KN_ERROR_PROTOCOL_NOTFINDFRIEND_ERROR		= 931,		// friend.
	KN_ERROR_PROTOCOL_OVERFRIENDSLENGTH_ERROR	= 932,		// friend.
	KN_ERROR_PROTOCOL_NOLOCATION_ERROR			= 933,		// .
	KN_ERROR_PROTOCOL_FRIENDALREADYIN_ERROR		= 934,		// .
	KN_ERROR_PROTOCOL_FRIENDALREADYAPPLY_ERROR	= 935,		// .
	KN_ERROR_PROTOCOL_FRIENDISMYSELF_ERROR		= 936,		// .
	KN_ERROR_PROTOCOL_OVERGROUPFRIENDSNUM_ERROR	= 940,		// Groupfriend.
	KN_ERROR_PROTOCOL_CANNOTDELETEMANAGER_ERROR	= 941,		// .
	KN_ERROR_PROTOCOL_FRIENDALREADYINGROUP_ERROR= 942,		// .
	KN_ERROR_PROTOCOL_GROUPFRIENDOVERNUMS_ERROR	= 943,		// Groupfriend.
	KN_ERROR_PROTOCOL_MESSAGELENGTH_ERROR		= 960,		// .
	KN_ERROR_PROTOCOL_MESSAGENOTFRIEND_ERROR	= 961,		// friend.
};

#endif // _NE_ERROR_H_
