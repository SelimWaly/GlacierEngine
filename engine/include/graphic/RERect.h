//  **************************************
//  File:        RERect.h
//  ***************************************
#ifndef RERect_DEFINED
#define RERect_DEFINED

#include <list>
#include <vector>
#include "core/SkRect.h"

typedef SkIRect REIRect;
typedef SkRect RERect;
typedef std::list<REIRect> LSTIRECT;
typedef std::list<RERect> LSTRECT;
typedef std::vector<REIRect> REIRectSet;
typedef std::vector<RERect> RERectSet;

namespace RERectHelper
{
	bool CheckAndJoinIntersetRect( LSTIRECT& lsRects );
	void Merge( LSTIRECT& lsRects );
	bool CheckAndJoinIntersetRect( LSTRECT& lsRects );
	void Merge( LSTRECT& lsRects );

	// RERect, , top <bottom
	// , RERect, 
	inline void InvertRect(REIRect& rct) {std::swap(rct.fTop, rct.fBottom);}
	inline void InvertRect(RERect& rct) {std::swap(rct.fTop, rct.fBottom);}
}
#endif

