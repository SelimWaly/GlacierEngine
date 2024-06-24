﻿//  **************************************
//  File:        KSlideView.cpp
//  ***************************************
#include "KSlideView.h"
#include "DataSync.h"
#include "KShapeDrawable.h"
#include "boost/lexical_cast.hpp"

//////////////////////////////////////////////////////////////////////////
// KSlideView
KSlideView::KSlideView()
{
	m_value = 1;
	m_e_dir = PROCESS_Vertical;
	m_drag_flag = FALSE;
	m_max = 100;
	m_min = 0;
	m_spacing1 = 0;
	m_spacing2 = 0;
}

KSlideView::~KSlideView()
{
	 m_silder_value_change_sign.disconnect_all();
}

void KSlideView::init(PROCESS_DIR e,  int spacing1, int spacing2 )
{
	m_e_dir = e;
	if (m_rect.width() > (spacing1 + spacing2) )
	{
		m_spacing1 = spacing1;
		m_spacing2 = spacing2;
	}


	setValue(0);

}

void  KSlideView::setMaxMin( int min, int max)
{
	m_max = max;
	m_min = min;
}

void KSlideView::setValue(float v, kn_bool b_call_back )    //
{
	if (v > m_max)
	{
		v = m_max;
	}
	if (v < m_min)
	{
		v = m_min;
	}

	if (v == m_value)
	{
		return;
	}

	if (m_text_drawable->isShow())
	{
		kn_string str = boost::lexical_cast<kn_string>(v);
		m_text_drawable->SetText(str);
	}

	RERect rect = m_icon_drawable->GetRect();
	int pos = 0;
	switch (m_e_dir)
	{
	case PROCESS_Horizontal: //
		pos = (v -m_min) *  (m_rect.width()-m_spacing1-m_spacing2 - rect.width() )/(m_max - m_min)+ m_spacing1;
		m_icon_drawable->setRect( m_spacing1 + pos, rect.top(), rect.width(), rect.height()  );
		break;
	case PROCESS_Vertical:
		pos = (v -m_min) *  (m_rect.height()-m_spacing1-m_spacing2 - rect.height() )/(m_max - m_min) + m_spacing1;
		m_icon_drawable->setRect( rect.left() , m_spacing1 + pos, rect.width(), rect.height()  );
		break;
	}


	m_value = v;
	if (b_call_back)
	{
		m_silder_value_change_sign.emit(v);
	}
	InvalidateView();
}

int KSlideView::getValue()
{
	return m_value;
}

int KSlideView::getValueArea()
{
	if (m_min == m_max)
	{//0
		return 1;
	}
	return m_max-m_min;
}
void KSlideView::onMoveDirect( kn_int x, kn_int y, KMessageMouse* pMsg )
{

	if ( m_drag_flag )
	{
		RERect rect = m_icon_drawable->GetRect();
		float v;
		if (m_e_dir == PROCESS_Horizontal)
		{
			rect.offsetTo( m_old_pos + x - m_down_point.x(), rect.top() );

			if (m_rect.width() - m_spacing1 - m_spacing2 - rect.width() == 0)
			{
				return;
			}
			v = (float)(rect.fLeft - m_spacing1)*(m_max - m_min)/(m_rect.width() - m_spacing1 - m_spacing2 - rect.width()) + m_min;
		}
		else
		{
			rect.offsetTo( rect.left(), m_old_pos + y - m_down_point.y() );
			if (m_rect.height() - m_spacing1 - m_spacing2 - rect.height() == 0)
			{
				return;
			}
			v = (float)(rect.fTop - m_spacing1)*(m_max - m_min)/(m_rect.height() - m_spacing1 - m_spacing2 - rect.height()) + m_min;
		}
		
		setValue(v, TRUE);
		pMsg->setIdle(KMSG_RETURN_DILE);
	}

}

void KSlideView::onDownDirect( kn_int x, kn_int y , KMessageMouse* pMsg)
{
	RERect rect = m_icon_drawable->GetRect();
	int x1 = x - m_rect.left();
	int y1 = y - m_rect.top();
	if (rect.contains(x1, y1))
	{//
		m_drag_flag = TRUE;
		m_down_point.set(x, y);
		if (m_e_dir == PROCESS_Horizontal)
		{
			m_old_pos = rect.left();
		}
		else
		{
			m_old_pos = rect.top();
		}
	}
}

void KSlideView::onUpDirect( kn_int iScreenX, kn_int iScreenY , KMessageMouse* pMsg)
{
	m_drag_flag = FALSE;
}
