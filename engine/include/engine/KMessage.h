//  **************************************
//  File:        KMessage.h
//  ***************************************

#ifndef __KKOTEI_MESSAGE_H__
#define __KKOTEI_MESSAGE_H__

#include "NE_pubhead.h"
#include "message.h"

//#define WM_NAVI_BASE (WM_USER + 1000)	//	
//enum KKoteiMessage
//{
//	WM_NAVI_HMI_SETSPECBOOK_FINISHED = 1,		//	HMI
//    WM_NAVI_GET_POSITION,
//    WM_NAVI_SET_POSITION
//};


kn_dword SendKMessage(KMessage* pMsg);
kn_dword PostKMessage(KMessage* pMsg);
KMessage* GetKMessage();



// 
class API KMsgQueue
{
public:

	// 
    void AddUserMessage(KMessage* pMsg);

	// 
    KMessage* GetUserMessage();

 

protected:

    // 
    deque<KMessage*> m_dqUserMsg;


	// 
    //KMutex m_mutex;
    boost::shared_mutex m_mutex;
 

};


#endif // __KKOTEI_MESSAGE_H__
