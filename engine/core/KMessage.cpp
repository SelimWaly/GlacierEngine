//  **************************************
//  File:        KMessage.cpp
//  ***************************************

#include "KMessage.h"
#include "DataSync.h"



// 
void KMsgQueue::AddUserMessage(KMessage* pMsg)
{
    writeLock lock(m_mutex);
    m_dqUserMsg.push_back(pMsg);

}

// 
KMessage* KMsgQueue::GetUserMessage()
{
	//	
	if(m_dqUserMsg.empty())
	{
		return false;
	}



    //KAutoMutex amLock(m_mutex);

    writeLock lock(m_mutex);

    KMessage* pMsg = NULL;

	if(!m_dqUserMsg.empty())
	{
        pMsg = m_dqUserMsg.front();
        m_dqUserMsg.pop_front();

	}

    return pMsg;

}
 
// 
KMsgQueue g_UserMsgQueue;


//extern kn_hwnd g_hWndNavi;
kn_dword SendKMessage(KMessage* pMsg)
{
    return PostKMessage(pMsg);


}

kn_dword PostKMessage(KMessage* pMsg)
{

    g_UserMsgQueue.AddUserMessage(pMsg);

	return 0;
}


KMessage* GetKMessage()
{

    return g_UserMsgQueue.GetUserMessage();
}
 
