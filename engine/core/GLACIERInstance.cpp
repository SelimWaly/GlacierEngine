//  **************************************
//  File:        GLACIERInstance.cpp
//  ***************************************

#include "KScreen.h"
#include "mainforwindows.h"
#include "KView.h"
#include "KTimer.h"
#include "KMessage.h"

CGLACIERInstance::CGLACIERInstance()
{
	m_hWnd = 0;
}

CGLACIERInstance::~CGLACIERInstance()
{

}

void CGLACIERInstance::release()
{
	m_screen.Release();
}

KScreen* CGLACIERInstance::getScreen()
{
	return &m_screen;
}


void  CGLACIERInstance::create(KGLACIERInitPara& para)
{
	m_screen.Create(para);
	m_screen.setGLACIERInstance(this);
	m_hWnd = para.m_wnd;

}


void CGLACIERInstance::SendTimerEvent(int num)
{
	KMessage* pMsg = GetKMessage();
	while(pMsg)
	{
	  
		LOGI("CGLACIERInstance::SendTimerEvent 2222 CORE_INITIAL_PROGRESS m_msg_type (%d)", pMsg->m_msg_type);
		GLACIERWndProc(m_hWnd, KMSG_USER, (WPARAM)pMsg, 0 );
		pMsg = GetKMessage();

	}
//	GLACIERWndProc(m_hWnd, KMSG_TIMER, GetTickCount() / 10, 0 );

	CheckGLACIERTimer();

}


int CGLACIERInstance::RunEventLoop(bool& bExit)
{
	return this->RunModalEventLoop(bExit);
}

// for android & ios
void CGLACIERInstance::SendOSMessage(int message, int wParam, int lParam)
{
	if(message == KMSG_TIMER)
	{
		SendTimerEvent(0);

	}
	else
	{
		GLACIERWndProc(0, message, wParam, lParam);

	}

}

void CGLACIERInstance::ResizeWindow(void* dst, int w, int h)
{
	m_screen.setWnd((HWND)dst);
	m_screen.resize(w , h);
 
}



kn_int KView::runModalLoop()
{
  
	KScreen* pScreen = GetScreen();

	if(pScreen == NULL)
	{
		ASSERT(0);
		return -1;
	}

	CGLACIERInstance* pGLACIERInstance = pScreen->getGLACIERInstance();
	if(pGLACIERInstance == NULL)
	{
		ASSERT(0);
		return -1;
	}


	pGLACIERInstance->RunModalEventLoop(m_b_modal_exit);
	return m_i_modal_result;


	//return -1;
}

 
