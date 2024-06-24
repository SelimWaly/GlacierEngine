//  **************************************
//  File:        KColorDrawable.h
//  ***************************************
#ifndef K_COLOR_DRAWABLE_H
#define K_COLOR_DRAWABLE_H

#include "KDrawable.h"
#include "REColor.h"

class API KColorDrawable :	public KDrawable
{
public:
	KColorDrawable(REColor color);
	//virtual ~KColorDrawable(void);

	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	void setColor(REColor color);
	REColor getColor();
	virtual void setColorAlpha(kn_byte);
private:

	REColor m_color;
	//颜色填充会忽略当前透明度设置，增加一个alpha变量记录外部alpha
	BYTE	m_alpha;
};

typedef boost::shared_ptr<KColorDrawable> KColorDrawable_PTR;

#endif	//	K_COLOR_DRAWABLE_H
