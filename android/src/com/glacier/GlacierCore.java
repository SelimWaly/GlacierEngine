package com.voltra;

import android.graphics.Bitmap;

//cd D:\SVN\papaya\trunk\03Code\GLACIERNaviBase\android_build\bin\classes
//javah -jni -classpath . com.voltra.NaviCore
 
public class GlacierCore 
{
	public static final int CB_FLIP = 0; 
	public static final int CB_SEND_JAVAMSG = 1;
	public static final int CB_SIZE = 2;
	public static native void lockBitmap();
	public static native void unlockBitmap();
	public static native void initializeEngine(String strDataPath, String savPath, Bitmap image,  int iDeviceWidth, int iDeviceHeight);
	public static native void drawIntoBitmap(Bitmap image,  int iDeviceWidth, int iDeviceHeight, long elapsedTime);
	public static native void sendGLACIERMessage(int message, int wParam, int lParam);  
	public static native void sendGLACIERMessageBuf(int message, int wParam, int lParam, int iBufSize, byte[] buff);
	public static native int registerStaticCallback(String strClassName, String strMethodName, String strMethodSign, int iCallbackID);	
	public static native int unregisterCallback(int iCallbackID);
	public static native int setAppActive(int bActive);
	
}
