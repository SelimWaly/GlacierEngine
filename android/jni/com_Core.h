/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_Core */

#ifndef _Included_com_Core
#define _Included_com_Core
#ifdef __cplusplus
extern "C" {
#endif
#undef com_Core_CB_FLIP
#define com_Core_CB_FLIP 0L
#undef com_Core_CB_SEND_JAVAMSG
#define com_Core_CB_SEND_JAVAMSG 1L
#undef com_Core_CB_SIZE
#define com_Core_CB_SIZE 2L
/*
 * Class:     com_Core
 * Method:    lockBitmap
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Core_lockBitmap
  (JNIEnv *, jclass);

/*
 * Class:     com_Core
 * Method:    unlockBitmap
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_Core_unlockBitmap
  (JNIEnv *, jclass);

/*
 * Class:     com_Core
 * Method:    initializeEngine
 * Signature: (Ljava/lang/String;Ljava/lang/String;Landroid/graphics/Bitmap;II)V
 */
JNIEXPORT void JNICALL Java_com_Core_initializeEngine
  (JNIEnv *, jclass, jstring, jstring, jobject, jint, jint);

/*
 * Class:     com_Core
 * Method:    drawIntoBitmap
 * Signature: (Landroid/graphics/Bitmap;IIJ)V
 */
JNIEXPORT void JNICALL Java_com_Core_drawIntoBitmap
  (JNIEnv *, jclass, jobject, jint, jint, jlong);

/*
 * Class:     com_Core
 * Method:    sendGLACIERMessage
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_Core_sendGLACIERMessage
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_Core
 * Method:    sendGLACIERMessageBuf
 * Signature: (IIII[B)V
 */
JNIEXPORT void JNICALL Java_com_Core_sendGLACIERMessageBuf
  (JNIEnv *, jclass, jint, jint, jint, jint, jbyteArray);

/*
 * Class:     com_Core
 * Method:    registerStaticCallback
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_Core_registerStaticCallback
  (JNIEnv *, jclass, jstring, jstring, jstring, jint);

/*
 * Class:     com_Core
 * Method:    unregisterCallback
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_Core_unregisterCallback
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
