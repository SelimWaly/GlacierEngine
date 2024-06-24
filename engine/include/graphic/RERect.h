﻿//  **************************************
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

	// RERect用于屏幕显示, 因此正常情况下, top <bottom
	// 假如用于地图数据范围, 并需要调用RERect的算法, 则需要先上下颠倒
	inline void InvertRect(REIRect& rct) {std::swap(rct.fTop, rct.fBottom);}
	inline void InvertRect(RERect& rct) {std::swap(rct.fTop, rct.fBottom);}
}
#endif

