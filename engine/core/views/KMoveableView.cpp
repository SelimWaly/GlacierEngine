﻿//  **************************************
//  File:        KMoveableView.cpp
//  ***************************************
#include "KMoveableView.h"
#include "DataSync.h"
#include "KScreen.h"
#include "KEasingCurve.h"

KMoveableView::KMoveableView()
{

	m_e_viewtype = KVIEW_MOVEABLE;
	m_b_x = TRUE;
	m_b_y = TRUE;

	//
	m_move_area.set(-100,-100,5000,5000);
}


KMoveableView::~KMoveableView()
{
	
}

void KMoveableView::enableXY(kn_bool b_x, kn_bool b_y)
{
	m_b_x = b_x;
	m_b_y = b_y;
}

void KMoveableView::setMovArea(RERect& r)
{
	m_move_area = r;
}

void KMoveableView::OnMove(kn_int _x, kn_int _y, KMessageMouse* pMsg)
{
	if(m_b_mouse_picked)
	{
		// 
		kn_int x = m_rect.left();
		kn_int y = m_rect.top();
		if (m_b_x)
		{
			x = _x - m_down_pos.x();
			if (x < m_move_area.left())
			{
				x = m_move_area.left();
			}
			else if (x > m_move_area.right() )
			{
				x = m_move_area.right();
			}

		}

		if (m_b_y)
		{
			y = _y - m_down_pos.y();
			if (y < m_move_area.top())
			{
				y = m_move_area.top();
			}
			else if (y > m_move_area.bottom() )
			{
				y = m_move_area.bottom();
			}
		}

		if (m_rect.x() != x || m_rect.y() != y)
		{//
			setRect( x, y, m_rect.width(), m_rect.height() );
			UpdateUI();
			m_sign_view_move.emit();
		}

	}

}

void KMoveableView::OnDown(kn_int x, kn_int y, KMessageMouse* pMsg)
{
	if(m_b_mouse_picked)
	{
		// 
		//((KViewGroup*)GetParent() )->changeViewLayerTop(this);
		//setViewFocus();
		m_down_pos.set( pMsg->m_pos_x - m_rect.x(), pMsg->m_pos_y - m_rect.y() );
	}
}

void KMoveableView::OnUp(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg)
{
//	unSetViewFocus();

}

/////////////////////////////////////

KMoveBackView::KMoveBackView()
{


}

KMoveBackView::~KMoveBackView()
{
	
}

void KMoveBackView::setStackPoint(int x, int y)
{
	m_stack_point.set(x, y);
}

REPoint KMoveBackView::getStackPoint()
{
	return m_stack_point;
}

void KMoveBackView::OnUp(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg)
{
	 KMoveableView::OnUp(iScreenX, iScreenY, pMsg);
	 if (!m_mov_ani_thread.isPlaying())
	 {
		 m_mov_ani_thread.clearAnimation();
		 if (m_rect.left() != m_stack_point.x() )
		 {
			 m_mov_ani_thread.addAnimationHelper(shared_from_this(), PropertyPARA_ID_POS_X, m_stack_point.x(), 600,0,0, KEasingCurve::OutElastic);
		 }

		 if (m_rect.top() != m_stack_point.y())
		 {
			 m_mov_ani_thread.addAnimationHelper(shared_from_this(), PropertyPARA_ID_POS_Y, m_stack_point.y(), 600,0,0, KEasingCurve::OutElastic);
		 }

		 m_mov_ani_thread.Start();
	 }

}
