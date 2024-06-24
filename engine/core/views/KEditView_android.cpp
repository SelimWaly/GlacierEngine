//  **************************************
//  File:        KEditView_android.cpp
//  ***************************************

/************************************************************************/
/* Android   [2015-7-3]

0. Java EditText SurfaceView

1. C++ KEditView ClickJava JMSG_IME_ON 
2. Java JMSG_IME_ON EditText showIME
3. Java  EditText textchange sendGLACIERMessageBufC++
4. C++ KEditView  KMSG_TYPE_IME_UPDATE  KEditView


1. KEditViewKEditView
2. sendsearch JavaIMEWraper::onEditorAction, C++ 

*/
/************************************************************************/

#ifdef ANDROID_NDK
#include "KEditView.h"
#include "mainforwindows.h"
#include "KTextMultiLineDrawable.h"
#include "CharSet.h"

// java message , java
#define  JMSG_IME_ON  100
#define  JMSG_IME_OFF  101

 

int JNI_SendJavaMsg(int iMsgID, int iArg1, int iArg2, const char* pszArg);

// android java,
void KEditView::showIME(kn_bool b)
{
	char szArg [] = "0";

	if(b)
	{
		 
		string strText = Knstring2Utf8String(this->getText());
		JNI_SendJavaMsg(JMSG_IME_ON, m_Index, m_input_max_length, strText.c_str());
	}
	else
	{
		JNI_SendJavaMsg(JMSG_IME_OFF, 0, 0, szArg);
	}


}




#endif // ANDROID_NDK
