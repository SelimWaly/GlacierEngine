//  **************************************
//  File:        ImageCoder.h
//  ***************************************
#ifndef ImageCoder_DEFINED
#define ImageCoder_DEFINED

#include "SkImageDecoder.h"
#include "SkImageEncoder.h"

typedef SkImageEncoder REImageEncoder;
typedef SkImageDecoder REImageDecoder;

// 缩放模式
enum RESCALEMODE
{
	RE_FIT_WIDTH,	//	适合宽度
	RE_FIT_RECT,	// 适合高度和宽度
	RE_FIT_FULL	// 充满区域

};

#endif
