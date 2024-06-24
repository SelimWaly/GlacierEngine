﻿//  **************************************
//  File:        mainforwindows.cpp
//  ***************************************
#ifdef WIN32
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

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		//
	//	m_screen.Release();
		break;
	case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		//EndPaint(hWnd, &ps);
// 		LOG ("WM_PAINT 111");
		m_screen.SetRenderFlag(TRUE);
// 		LOG ("WM_PAINT 222");
		break;
	// 
	case WM_MOUSEMOVE:
		if (m_b_move_wnd)
		{
			POINT point;
			GetCursorPos(&point);
			::SetWindowPos(
				hWnd,
				HWND_TOP,
				point.x - m_screen.GetWidth()/2, 
				point.y - m_screen.GetHeight()/2, 
				0,
				0,
				SWP_NOZORDER|SWP_NOSIZE);
		}
		break;	
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		break;

	case WM_MBUTTONDOWN: //
		m_b_move_wnd = TRUE;
		break;
	case WM_MBUTTONUP: //
		m_b_move_wnd = FALSE;
		break;
	case WM_MOUSEWHEEL:
		break;
	default:
		break;
	}
}


bool g_bQuitLoop = false ;//

int CGLACIERInstance::RunModalEventLoop(bool& bExit)
{
	BOOL bRet = FALSE;
	MSG msg;
	long lTicks = 0;

	while(!bExit && !g_bQuitLoop)
	{ 
		bRet = PeekMessage (&msg, NULL, 0, 0 , PM_REMOVE);

		if (bRet)
		{
			if (msg.message == WM_QUIT)
			{
				g_bQuitLoop = true;
				break ;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}

 

		if(GetTickCount() - lTicks > 10)
		{
			SendTimerEvent(0);
			lTicks = GetTickCount();
		}
		Sleep(10);
	} 


	return 0;

}




// , WindowClasscursor
void SetMouseCursorStyle(kn_dword dwStyleID)
{ 
	switch (dwStyleID)
	{
	case CURSOR_ARROW: 	SetCursor(LoadCursor(NULL, IDC_ARROW));	break;
	case CURSOR_HAND: SetCursor(LoadCursor(NULL, IDC_HAND));break;
	case CURSOR_CROSS: SetCursor(LoadCursor(NULL, IDC_CROSS));break;
	default : 	break;
	} 

 
}

 


void SystemClipboard::copyTextToClipboard (const kn_string& text)
{
	if (OpenClipboard (0) != 0)
	{
		if (EmptyClipboard() != 0)
		{
			const size_t bytesNeeded = text.length() * sizeof(TCHAR);

			if (bytesNeeded > 0)
			{
				if (HGLOBAL bufH = GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, bytesNeeded + sizeof (WCHAR)))
				{
					if (WCHAR* const data = static_cast <WCHAR*> (GlobalLock (bufH)))
					{
						_stprintf(data,_T("%s"),text.c_str());
						//text.copyToUTF16 (data, bytesNeeded);
						GlobalUnlock (bufH);

						SetClipboardData (CF_UNICODETEXT, bufH);
					}
				}
			}
		}

		CloseClipboard();
	}
}

kn_string SystemClipboard::getTextFromClipboard()
{
	kn_string result;

	if (OpenClipboard (0) != 0)
	{
		if (HANDLE bufH = GetClipboardData (CF_UNICODETEXT))
		{
			if (const WCHAR* const data = (const WCHAR*) GlobalLock (bufH))
			{
				result = data;
				//result = String (data, (size_t) (GlobalSize (bufH) / sizeof (WCHAR)));
				GlobalUnlock (bufH);
			}
		}

		CloseClipboard();
	}

	return result;
}

#endif // WIN32
