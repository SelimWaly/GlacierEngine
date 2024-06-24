// CalendarDemo.cpp : ����Ӧ�ó������ڵ㡣
//


#include "GLACIERMainView.h"


#include "mainforwindows.h"

#ifdef WIN32
#include "resource.h"
#include "FilePath.h"
#endif

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
HWND g_hWnd = 0;
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

int g_iScreenWidth = 1024; // ��Ļ����
int g_iScreenHeight = 768; // ��Ļ�߶�
// bool		g_bMoveWindow = FALSE;
int g_mouse_down_flag = FALSE;
CGLACIERInstance  g_instance;

#ifdef WIN32
void CreateView();
// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GLACIERApp, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDD_GLACIERApp_DIALOG));

	// GLACIER�ӹ�����Ϣѭ��:
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	// ����Ϣѭ��:
	kn_bool bExit = FALSE;
	g_instance.RunEventLoop(bExit);

	g_instance.release();
	return  0;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴��������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GLACIERApp));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HMI);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GLACIERApp));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd =  CreateWindow(
	   szWindowClass,
	   szTitle,
	   WS_POPUP,
	   (GetSystemMetrics(SM_CXSCREEN) - g_iScreenWidth) / 2,
	   (GetSystemMetrics(SM_CYSCREEN) - g_iScreenHeight) / 2,
	   g_iScreenWidth, g_iScreenHeight,
	   NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   KGLACIERInitPara para;
   para.m_w = g_iScreenWidth;
   para.m_h = g_iScreenHeight;
   para.m_wnd = hWnd;
   para.m_render_mode = SCREEN_RENDER_MULTI_THREAD;

   para.m_device_type = WIN_DEVICE;


   g_instance.create(para );
   kn_string strPath;
   GetFilePath(strPath);
   strPath += _T("../img/");
   SetCurrentPath(strPath.c_str());
   CreateView();
   g_hWnd = hWnd;

   g_instance.getScreen()->SetRenderFlag(TRUE);
   ShowWindow( hWnd, nCmdShow );
   UpdateWindow( hWnd );

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
		//case WM_PAINT:
		//	hdc = BeginPaint(hWnd, &ps);
		//	EndPaint(hWnd, &ps);
		//	break;
	case WM_DESTROY:
		//�첽��Ⱦ��Ҫ�ڴ˽�����Ⱦ�߳�
		PostQuitMessage( 0 );
		break;
	case WM_KEYDOWN:


		break;
	default:
		break;
	}

	g_instance.GLACIERWndProc( hWnd, message, wParam, lParam );

	return DefWindowProc( hWnd, message, wParam, lParam );
}

// �����ڡ������Ϣ��������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
#endif

void CreateView()
{
	////  ��������


	KMainView_PTR main_view = KMainView_PTR(new KMainView() );
	main_view->Create(RERect::MakeXYWH(0, 0, (SkScalar)g_iScreenWidth , (SkScalar)g_iScreenHeight));
	g_instance.getScreen()->AddView( main_view );
	main_view->init();

}

//====================================================================
// for  andorid &  ios
void ResizeWindow(void* dst, int w, int h)
{
	g_instance.ResizeWindow(dst, w, h);
	g_iScreenWidth = w;
	g_iScreenHeight = h;
}

void SendOSMessage(int message, int wParam, int lParam)
{
	if(message == KMSG_TIMER)
	{
		g_instance.SendTimerEvent(0);

	}
	else
	{
		g_instance.GLACIERWndProc(0, message, wParam, lParam);

	}

}
