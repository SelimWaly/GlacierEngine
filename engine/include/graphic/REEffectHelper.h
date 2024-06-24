//  **************************************
//  File:        REEffectHelper.h
//  ***************************************
#ifndef REEffectHelper_DEFINED
#define REEffectHelper_DEFINED

#include "renderingengine.h"
#include "DrawLooper.h"
#include "MaskFilter.h"

class API REEffectHelper
{
public:
	// , , 
	static void AddStrokeAndFilledEffect(REPaint& paint, REScalar strokeWidth = 3, REScalar filledAlpha = 0x20);
	// , (shadowDeviation). , (bUseGap, gap)
	static void AddShadowEffect(REPaint& paint, REScalar shadowDeviation = 3, REScalar shadowAlpha = 0x60, bool bUseGap = true, REScalar gap = 3 / 2);
	// , 
	static void AddBlurShadowEffect(REPaint& paint, REScalar radius = 3, REScalar deviation = 3,
		REBlurMaskFilter::BlurStyle blurStyle = REBlurMaskFilter::kNormal_BlurStyle, REBlurMaskFilter::BlurFlags blurFlags = REBlurMaskFilter::kAll_BlurFlag);
	// 
	enum DiscreteTextStyle
	{
		DTS_Clear,	// , 
		DTS_Fill			// , 
	};
	static void AddDiscreteEffect(REPaint& paint, DiscreteTextStyle style = DTS_Clear, REScalar segLength = 4, REScalar deviation = 3 );
};

#endif
