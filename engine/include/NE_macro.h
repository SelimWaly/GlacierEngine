//  **************************************
//  File:        NE_macro.h
//  ***************************************


#ifndef _NE_MACRO_H_
#define _NE_MACRO_H_

#define KNAPI               // API调用协议

#define IN      // 输入参数
#define OUT     // 输出参数
#define INOUT   // 输入、输出参数

// 安全删除一个需调用delete释放的对象
#define SAFE_DELETE(pObject) if(pObject) {delete (pObject); (pObject) = NULL;}
// 安全删除一组需调用delete[]释放的对象
#define SAFE_DELETE_GROUP(pObject) if(pObject) {delete[] (pObject); (pObject) = NULL;}

#ifndef PI
    #define PI		(3.14159265358979323846f)
#endif





#endif // _NE_MACRO_H_
