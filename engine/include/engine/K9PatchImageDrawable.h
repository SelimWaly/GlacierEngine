//  **************************************
//  File:        K9PatchImageDrawable.h
//  ***************************************
#ifndef K_9PATCH_IMAGE_DRAWABLE_H
#define K_9PATCH_IMAGE_DRAWABLE_H

#include "KImageDrawable.h"

class API K9PatchImageDrawable : public KImageDrawable
{
public:
	K9PatchImageDrawable();
	K9PatchImageDrawable(const kn_string& strFile);
	K9PatchImageDrawable(IRESurface* pSurface, kn_bool b_out = FALSE);
	void Initialize();

	virtual ~K9PatchImageDrawable(void);
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);


	void GetsrcRect();
	void GetDesRect();
	
	vector<RERect> m_srcRect;
	int m_Row;
	int m_Col;
	vector<RERect> m_DesRect;

	RERect m_rectScaleBound;
};

typedef boost::shared_ptr<K9PatchImageDrawable> K9PatchImageDrawable_PTR;

#endif
