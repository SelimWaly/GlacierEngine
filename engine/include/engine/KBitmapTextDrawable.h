//  **************************************
//  File:        KBitmapTextDrawable.h
//  ***************************************
#ifndef K_BITMAP_TEXT_DRAWABLE_H
#define K_BITMAP_TEXT_DRAWABLE_H

#include "KTextDrawable.h"
#include <vector>

typedef struct  BITMAPCHAR_
{
	TCHAR word;
	int x;
	int y;
	int w;
	int h;
	BITMAPCHAR_()
	{
		word = 0;
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
}BITMAPCHAR;


class API KBitmapTextDrawable : public KTextDrawable
{
public:
	KBitmapTextDrawable(const kn_char* szText, REColor color,  kn_int iFontSize, REPaint::Align align);
	~KBitmapTextDrawable();

	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	virtual int getTextWidth();

	kn_bool LoadProfile(const kn_string& strFile);
	BITMAPCHAR* getBITMAPChar(TCHAR c);

	std::vector<BITMAPCHAR> m_chartable;
	IRESurface* m_bitmap_surface;

	int m_BitmapCharSetNum;
	int m_CharAverageWidth;
	int m_CharAverageHeight;
};

typedef boost::shared_ptr<KBitmapTextDrawable> KBitmapTextDrawable_PTR;

#endif
