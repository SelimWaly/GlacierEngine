//  **************************************
//  File:        KStaticTextView.cpp
//  ***************************************
#include "KStaticTextView.h"


KStaticTextView::KStaticTextView(void)
{
}


KStaticTextView::~KStaticTextView(void)
{
}

SkTypeface* KStaticTextView::GetFont()
{
	return m_text_drawable->GetFont();
}

void KStaticTextView::SetFont( SkTypeface* pTypeFace )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setFont(pTypeFace);
}
 
