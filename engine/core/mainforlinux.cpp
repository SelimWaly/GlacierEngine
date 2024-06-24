//  **************************************
//  File:        mainforlinux.cpp
//  ***************************************
#ifdef KOTEI_LINUX

// for linux_qt / android / ios


#include "KScreen.h"
#include "mainforwindows.h"
#include "KView.h"

 
void CGLACIERInstance::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	KMessage*  msg = KMessage::getMsgForWin32 (hWnd,message,wParam,lParam);
	if (msg)
	{
		m_screen.DoMessage(msg);
		SAFE_DELETE(msg);
	}

 
}


int CGLACIERInstance::RunModalEventLoop(bool& bExit)
{
	return 0;
}

// , WindowClasscursor
void SetMouseCursorStyle(kn_dword dwStyleID)
{ 
 

}
 


void SystemClipboard::copyTextToClipboard (const kn_string& text)
{
 
}

kn_string SystemClipboard::getTextFromClipboard()
{
 

	return _T("");
}


#endif // KOTEI_LINUX
