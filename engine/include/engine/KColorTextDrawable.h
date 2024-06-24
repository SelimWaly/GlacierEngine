//  **************************************
//  File:        KColorTextDrawable.h
//  ***************************************
#ifndef K_COLORTEXT_DRAWABLE_H
#define K_COLORTEXT_DRAWABLE_H

#include "KTextDrawable.h"


class API KFocusColorTextDrawable : public KTextDrawable
{
protected:
	kn_string m_focus_text;
	REColor   m_focus_color;

public:
	KFocusColorTextDrawable(const kn_char* szText, REColor color = RE_ColorBLACK,  kn_int iFontSize = 20, REPaint::Align align = REPaint::kLeft_Align);

	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);

	void SetFocusText(const kn_string &szText);
	const kn_string& GetFocusText();
	void setFocusColor(REColor color);
	REColor getFocusColor();

};

typedef boost::shared_ptr<KFocusColorTextDrawable> KFocusColorTextDrawable_PTR;

#endif
