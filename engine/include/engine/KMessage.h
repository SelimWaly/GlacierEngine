//  **************************************
//  File:        KMessage.h
//  ***************************************

#ifndef __KKOTEI_MESSAGE_H__
#define __KKOTEI_MESSAGE_H__

#include "NE_pubhead.h"
#include "message.h"

//#define WM_NAVI_BASE (WM_USER + 1000)	//	消息起始
//enum KKoteiMessage
//{
//	WM_NAVI_HMI_SETSPECBOOK_FINISHED = 1,		//	通知HMI设置特殊收藏点完成
//    WM_NAVI_GET_POSITION,
//    WM_NAVI_SET_POSITION
//};


kn_dword SendKMessage(KMessage* pMsg);
kn_dword PostKMessage(KMessage* pMsg);
KMessage* GetKMessage();



// 自定义消息队列
class API KMsgQueue
{
public:

	// 加入用户消息
    void AddUserMessage(KMessage* pMsg);

	// 获取用户消息
    KMessage* GetUserMessage();

 

protected:

    // 自定义消息列表
    deque<KMessage*> m_dqUserMsg;


	// 操作消息的互斥
    //KMutex m_mutex;
    boost::shared_mutex m_mutex;
 

};


#endif // __KKOTEI_MESSAGE_H__
