//  **************************************
//  File:        KColorTextDrawable.cpp
//  ***************************************
#include "KColorTextDrawable.h"


KFocusColorTextDrawable::KFocusColorTextDrawable(const kn_char* szText, REColor color,  kn_int iFontSize, REPaint::Align align):KTextDrawable(szText,  color ,  iFontSize, align)
{
	m_focus_color = RE_ColorRED;
}

void KFocusColorTextDrawable::SetFocusText(const kn_string &szText)
{
	m_focus_text = szText;
}

void KFocusColorTextDrawable::setFocusColor(REColor color)
{
	m_focus_color = color;
}

void KFocusColorTextDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX, int iDstY)
{
	if (! BeginDraw(pDstSurface, pMatrix, iDstX, iDstY ) )
	{
		return;
	}

	int iTarX = m_rect.left() + iDstX;
	int iTarY = m_rect.top() + iDstY;

	REPaint::Align align = m_paint.getTextAlign();
	if(align == REPaint::kCenter_Align )
	{
		iTarX += m_rect.width() / 2;
	}
	else if(align == REPaint::kRight_Align)
	{
		iTarX += m_rect.width();
	}

	// 
	// , baseline ,
	REPaint::FontMetrics fm; 
	m_paint.getFontMetrics(&fm);

	//
	int iTextHeight = ceil (fm.fDescent - fm.fAscent);

	// baseline
	int iBaseline = abs((int)fm.fAscent);

	iTarY =  (m_rect.height() - iTextHeight) / 2 + iBaseline + iTarY;

	try
	{
		if ( m_focus_text.empty())
		{//
			pDstSurface->DrawText(m_strText.c_str(), m_strText.length() * sizeof(kn_char), iTarX, iTarY, m_paint);
		}
		else
		{
			std::size_t find_pos = m_strText.find(m_focus_text);
			if (find_pos == string::npos)
			{// not find
				pDstSurface->DrawText(m_strText.c_str(), m_strText.length() * sizeof(kn_char), iTarX, iTarY, m_paint);
			}
			else
			{
				//
				//
				int x_step = 0;
				if (find_pos > 0)
				{
					pDstSurface->DrawText(m_strText.c_str(), find_pos* sizeof(kn_char), iTarX, iTarY, m_paint);
					x_step = m_paint.measureText(m_strText.c_str(), find_pos* sizeof(kn_char));
				}
				// 
				REColor clr = m_paint.getColor();
				m_paint.setColor(m_focus_color); //
				pDstSurface->DrawText(m_focus_text.c_str(), m_focus_text.length()* sizeof(kn_char), iTarX + x_step, iTarY, m_paint);
				x_step += m_paint.measureText(m_focus_text.c_str(),  m_focus_text.length() * sizeof(kn_char));
				m_paint.setColor(clr); //

				//
				kn_string str = m_strText.substr(find_pos+ m_focus_text.size());
				pDstSurface->DrawText(str.c_str(), str.length()* sizeof(kn_char), iTarX + x_step, iTarY, m_paint);
			}
		}
	}
	catch (...)
	{
		iTarX = iTarX;
	}

	EndDraw(pDstSurface, pMatrix);
 
}


REColor KFocusColorTextDrawable::getFocusColor()
{
	return m_focus_color;
}

const kn_string& KFocusColorTextDrawable::GetFocusText()
{
	return m_focus_text;
}
