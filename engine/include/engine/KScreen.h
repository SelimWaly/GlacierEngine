//  **************************************
//  File:        KScreen.h
//  ***************************************
#ifndef K_SCREEN_H
#define K_SCREEN_H

#include "sigslot.h"
#include "KLog.h"
#include "KView.h"
#include "DataSync.h"
#include "KViewGroup.h"
#include "KMenuView.h"
#include "KTipView.h"
#include "KTimer.h"
#include <map>

#define SCREEN_RENDER_MAIN_THREAD 0
#define SCREEN_RENDER_MULTI_THREAD 1

#define WIN_DEVICE          0
#define DDRAW_DEVICE        1
#define GL_DEVICE           2
#define LAYER_WIN_DEVICE    3
#define GL_LAYER_WIN_DEVICE 4
#define ANDROID_DEVICE      5
#define QT_SOFT_DEVICE      6
#define QT_GL_DEVICE        7
#define IOS_DEVICE          8
#define SKIAGL_DEVICE		9

class CGLACIERInstance;

//
class API KGLACIERInitPara
{
public:
	KGLACIERInitPara();
	~KGLACIERInitPara();
	kn_int m_w;
	kn_int m_h;
	REBitmap::Config m_format;
	HWND m_wnd;
	kn_int m_render_mode;// = SCREEN_RENDER_MULTI_THREAD;
	kn_int m_device_type;// = WIN_DEVICE;
};


#ifdef _WIN32_WCE
class API KScreen : public KObject , public has_slots<>
#else
class API KScreen : public KObject , public has_slots<multi_threaded_local>
#endif
{
protected:
	KGLACIERInitPara m_init_para;
	kn_int m_width;
	kn_int m_height;
	IRESurface* m_p_screen_surface;

	KViewGroup_PTR m_view_group;
	//menutip
	KMenuBase_PTR m_view_menu;
	KTipBase_PTR m_view_tip;
	//	
	HWND m_hwnd;
	HDC m_hdc;

	//
	boost::shared_mutex m_render_flag_mutex;
	kn_bool m_render_flag;

	//
	kn_bool m_b_draw_clip;
	//SCREEN_RENDER_MULTI_THREAD SCREEN_RENDER_MAIN_THREAD
	kn_int m_render_mode;
	// wnd GL
	kn_int m_render_device_type;

	//false
	kn_bool m_render_run_flag;
	boost::thread* m_p_thread;
	// 
	kn_bool m_b_draw_drawing;

	CDataSync	m_data_sync;

	LSTVIEW m_lst_modal_view;
	//
	//
	KView_PTR	m_focus_view;
	LSTVIEW	m_temp_focus_view;
	//active
	KView_PTR	m_active_view;

	LSTTIMER	m_lst_timer;
	
	//id
	boost::shared_mutex m_stop_id_mutex;
	map<kn_int, kn_int>	m_stop_id_map; // id, msg id

	void dealAniStopMsg(); //zhic 20151213  

	static kn_int renderThread(LPVOID lpPara);
	void Draw(kn_bool bFullRefresh);
	void Flip(LSTRECT &lst);
	//
	void OnDraw();
	void	RunRenderThread();
	void stopRenderThread();
	CGLACIERInstance* m_p_instance;
public:
	KScreen();
	~KScreen();
	kn_bool Create(kn_int iWidth, kn_int iHeight, REBitmap::Config format, HWND hWnd,  kn_int render_mode = SCREEN_RENDER_MULTI_THREAD, kn_int device_type = WIN_DEVICE);
	kn_bool Create(KGLACIERInitPara& );
	void Release();

	void setDrawClip(kn_bool);
	kn_bool DoMessage(KMessage* pMsg);
	kn_int GetWidth();
	kn_int GetHeight();

	kn_bool GetRenderFlag();
	void	SetRenderFlag(kn_bool);

	kn_bool GetRenderRunFlag();
	void	SetRenderRunFlag(kn_bool);

	void	AddView(KView_PTR p);

	void	DeleteView(KView_PTR p);

	////// b_check_change
	kn_bool	addProperty(CPropertyBase* p, kn_bool b_check_change=TRUE);
	//id
	kn_int getNewID();
	//ID
	kn_bool checkID(kn_int&);
	//ID
	void addID(kn_int&);
	/////
	void	UI_DoSyncDataList();

	void setClipDraw(kn_bool b);

	//
	void sendGLACIERMessage(kn_int msgid, KMessage* msg = NULL);
	void sendSystemMessage(kn_int msgid,  WPARAM, LPARAM );

	//DoModal demodal
	void addModalView(KView_PTR pView);
	void delModalView(KView_PTR pView);
	void clearModalView();
	///////////////////
	//bviewunfocusview
	void setFocusView(KView_PTR v, kn_bool b = TRUE);
	KView_PTR getFocusView();
	KView_PTR getActiveView();
	KView_PTR getModalView();
	
	//Focusviewfocusview
	KView_PTR getTempFocusView();
//	KView* getTempModalView();

	void setViewActive(KView_PTR v, kn_bool b = TRUE);

	//menu
	void showMenu(KMenuBase_PTR );
	void showTip(KTipBase_PTR );
	//idid tipid -1
	void hideTip(int id = NO_TIMER);

	void resize(int w, int h);
	HWND getWnd();
	void setWnd(HWND);

	void setGLACIERInstance(CGLACIERInstance* p);
	CGLACIERInstance* getGLACIERInstance();

	void addStopId(kn_int& id, kn_int& msg_id);

};


#endif
