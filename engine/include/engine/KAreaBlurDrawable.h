//  **************************************
//  File:        KAreaBlurDrawable.h
//  ***************************************
#ifndef K_AREABLUR_DRAWABLE_H
#define K_AREABLUR_DRAWABLE_H


#include "KDrawable.h"


class API KAreaBlurDrawable : public KDrawable
{
public :
	KAreaBlurDrawable();
	virtual ~KAreaBlurDrawable();
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	virtual void SetRect(const RERect& rect);
protected:
	IRESurface* m_blur_surface;
};
typedef boost::shared_ptr<KAreaBlurDrawable> KAreaBlurDrawable_PTR;

#endif
