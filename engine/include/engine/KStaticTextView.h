//  **************************************
//  File:        KStaticTextView.h
//  ***************************************
#ifndef _K_STATIC_TEXT_VIEW_H_
#define _K_STATIC_TEXT_VIEW_H_

#include <boost/shared_ptr.hpp>
#include "KTextView.h"
class API KStaticTextView : public KStaticView
{
public:
	KStaticTextView(void);
	virtual ~KStaticTextView(void);
public:
	SkTypeface* GetFont();
	void SetFont(SkTypeface* pTypeFace);
};

typedef boost::shared_ptr<KStaticTextView> KStaticTextView_PTR;
#endif // _K_STATIC_TEXT_VIEW_H_
