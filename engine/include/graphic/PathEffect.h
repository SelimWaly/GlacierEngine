//  **************************************
//  File:        PathEffect.h
//  ***************************************
#ifndef PathEffect_DEFINED
#define PathEffect_DEFINED

#include "SkPathEffect.h"
#include "effects/Sk1DPathEffect.h"
#include "effects/Sk2DPathEffect.h"
#include "effects/SkCornerPathEffect.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"

typedef SkPathEffect REPathEffect;
typedef Sk1DPathEffect RE1DPathEffect;
typedef SkPath1DPathEffect REPath1DPathEffect;
typedef Sk2DPathEffect RE2DPathEffect;
typedef SkPath2DPathEffect REPath2DPathEffect;
typedef SkCornerPathEffect RECornerPathEffect;
typedef SkDashPathEffect REDashPathEffect;
typedef SkDiscretePathEffect REDiscretePathEffect;
typedef SkSumPathEffect RESumPathEffect;
typedef SkComposePathEffect REComposePathEffect;

#endif
