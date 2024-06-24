//  **************************************
//  File:        KColorDrawable.cpp
//  ***************************************
#include "KColorDrawable.h"


KColorDrawable::KColorDrawable(REColor color)
{
	m_type = KDrawable::KDRAWABLE_COLOR;
	m_color = color;
	m_paint.setColor(m_color);

//	m_rect.setXYWH(0, 0, 800, 480);
	
}


//KColorDrawable::~KColorDrawable(void)
//{
//}


void  KColorDrawable::setColorAlpha(kn_byte a)
{
	m_alpha = a; // ColorSetA(m_color, a);
}

void KColorDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX, int iDstY)
{
	readLock lock(m_drawable_draw_mutex); 
	// 
	if (! BeginDraw(pDstSurface, pMatrix, iDstX, iDstY ) )
	{
		return;
	}
	if (m_b_clip_rect)
	{
		RERect rect = RERect::MakeXYWH(m_rect.left() + iDstX, m_rect.top() + iDstY, m_rect.width(), m_rect.height());
		pDstSurface->ClipRect(rect);
	}
	//
	REColor clr = ColorSetA(m_color, ColorGetA(m_color)*m_alpha/255 );
	pDstSurface->DrawColor(clr);


	//pDstSurface->Restore();
	EndDraw(pDstSurface, pMatrix);
}

void KColorDrawable::setColor( REColor color )
{
	writeLock lock(m_drawable_draw_mutex); 
	m_color = color;
}

REColor KColorDrawable::getColor()
{
	return m_color;
}

