//  **************************************
//  File:        KPathEffectDrawable.h
//  ***************************************
#ifndef K_PATHEFFECT_DRAWABLE_H
#define K_PATHEFFECT_DRAWABLE_H


#include "KShapeDrawable.h"


class API KPathEffectDrawable : public KShapeDrawable
{
public :
	KPathEffectDrawable();
	virtual ~KPathEffectDrawable();
	
};
typedef boost::shared_ptr<KPathEffectDrawable> KPathEffectDrawable_PTR;


#endif
