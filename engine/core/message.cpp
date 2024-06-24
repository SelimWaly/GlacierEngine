﻿//  **************************************
//  File:        message.cpp
//  ***************************************
#include "message.h"
#include "KLog.h"
 

KMessage::KMessage()
{
	m_msg_class_type = KMSG_TYPE_NONE;
	m_msg_type = KMSG_BEGIN;
	m_b_idle = KMSG_RETURN_DEFAULT;

	m_wParam = 0;
	m_lParam = 0;

}

kn_bool KMessage::HasPos()
{
	if (m_msg_class_type == KMSG_TYPE_MOUSE || m_msg_class_type == KMSG_TYPE_TOUCH)
	{
		return TRUE;
	}

	return FALSE;
}


KMessagePos::KMessagePos(void)
{
    m_msg_class_type = KMSG_TYPE_POS;
}

KMessageKey::KMessageKey()
{
    m_msg_class_type = KMSG_TYPE_KEY;
    m_msg_type = KMSG_BEGIN;
}

KMessageMouse::KMessageMouse()
{
    m_msg_class_type = KMSG_TYPE_MOUSE;
    m_msg_type = KMSG_BEGIN;
}

KMessageMouseWheel::KMessageMouseWheel()
{
    m_msg_class_type = KMSG_TYPE_MOUSE_WHELL;
    m_msg_type = KMSG_MOUSEWHEEL;
}

KMessageTouch::KMessageTouch(HWND hwnd)
{
    m_msg_class_type = KMSG_TYPE_TOUCH;
    m_msg_type = KMSG_BEGIN;
    m_touch_id = -1;

	m_wnd = hwnd;

	m_iPointCount = 0;
	m_ids = NULL;	// point id
	m_xs = NULL;
	m_ys = NULL;

 
}


KMessageTouch* KMessageTouch::deepCopy()
{
	KMessageTouch* pMsgCopy = new KMessageTouch(m_wnd);

	pMsgCopy->m_msg_class_type = m_msg_class_type;
	pMsgCopy->m_msg_type = m_msg_type;
	pMsgCopy->m_touch_id = m_touch_id;
	pMsgCopy->m_iPointCount = m_iPointCount;

	if(m_iPointCount > 0)
	{
		pMsgCopy->m_ids = new int [m_iPointCount];
		pMsgCopy->m_xs = new int [m_iPointCount];
		pMsgCopy->m_ys = new int [m_iPointCount];

		memcpy(pMsgCopy->m_ids, this->m_ids, sizeof(int) * m_iPointCount);
		memcpy(pMsgCopy->m_xs, this->m_xs, sizeof(int) * m_iPointCount);
		memcpy(pMsgCopy->m_ys, this->m_ys, sizeof(int) * m_iPointCount);
   
	}

	return pMsgCopy;
 
}

KMessageTouch::~KMessageTouch()
{
	m_iPointCount = 0;
	SAFE_DELETE_GROUP(m_ids);
	SAFE_DELETE_GROUP(m_xs);
	SAFE_DELETE_GROUP(m_ys);

}
  

void KMessage3Dx::transMsgForWin32( UINT message, WPARAM wParam, LPARAM lParam )
{
	m_msg_class_type = KMSG_TYPE_3DX; //
	m_msg_type = KMSG_3DX; //
	m_wParam = wParam;
	m_lParam = lParam;
	m_message  = message;
}


KMessageInput::KMessageInput()
{

}


void KMessageInput::transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam)
{

}

KMessageEditTextIME::KMessageEditTextIME()
{
	m_i_start = 0;
	m_i_before = 0;
	m_i_count = 0;
}
////////////////////// 
KMessageDrag::KMessageDrag()
{
	m_msg_class_type = KMSG_TYPE_DRAG;
}


//void KMessageDrag::transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch(message)
//	{
//	case KGLACIERMSG_DRAG:
//		m_msg_type = KMSG_DRAG;
//		break;
//	case KGLACIERMSG_DRAG_UP:
//		m_msg_type = KMSG_DRAG_UP;
//		break;
//	default:
//		return;
//	}
//	
//	KMessageDrag* p = (KMessageDrag*)wParam;
//	m_p_drag_view = p->m_p_drag_view;
//	m_drag_type = p->m_drag_type;
//	
//	m_pos_x = p->m_pos_x;
//	m_pos_y = p->m_pos_y;
//
//	delete p;
//}
