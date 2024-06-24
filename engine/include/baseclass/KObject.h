//  **************************************
//  File:        KObject.h
//  ***************************************
#ifndef _KOBJECT_H_
#define _KOBJECT_H_

#include "NE_pubhead.h"
#include "KLog.h"
class API KObject
{


public:
	KObject(){};
	virtual ~KObject(){};
	virtual kn_string toString() {return kn_string();};


	
};
#endif //  _CKOBJECT_H_
