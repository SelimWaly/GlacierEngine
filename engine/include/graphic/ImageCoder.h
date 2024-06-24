//  **************************************
//  File:        ImageCoder.h
//  ***************************************
#ifndef ImageCoder_DEFINED
#define ImageCoder_DEFINED

#include "SkImageDecoder.h"
#include "SkImageEncoder.h"

typedef SkImageEncoder REImageEncoder;
typedef SkImageDecoder REImageDecoder;

// 
enum RESCALEMODE
{
	RE_FIT_WIDTH,	//	
	RE_FIT_RECT,	// 
	RE_FIT_FULL	// 

};

#endif
