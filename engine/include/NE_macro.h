//  **************************************
//  File:        NE_macro.h
//  ***************************************


#ifndef _NE_MACRO_H_
#define _NE_MACRO_H_

#define KNAPI

#define IN
#define OUT
#define INOUT

#define SAFE_DELETE(pObject) if(pObject) {delete (pObject); (pObject) = NULL;}
#define SAFE_DELETE_GROUP(pObject) if(pObject) {delete[] (pObject); (pObject) = NULL;}

#ifndef PI
    #define PI		(3.14159265358979323846f)
#endif





#endif // _NE_MACRO_H_
