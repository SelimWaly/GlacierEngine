//  **************************************
//  File:        KView.h
//  ***************************************
#ifndef K_VIEW_H
#define K_VIEW_H

#include "renderingengine.h"
#include "sigslot.h"
#include <boost/thread/thread.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include "REPaint.h"
#include "RERect.h"
#include "REMatrix.h"
#include "KDrawable.h"
#include "KObject.h"
#include "message.h"
#include "KLog.h"
#include "KTimer.h"
#include "KTextDrawable.h"
#include "KColorDrawable.h"
#include "KGestureDetector.h"
using namespace sigslot;
#define NO_TIMER -1
class KViewGroup;
typedef boost::shared_ptr<KViewGroup> KViewGroup_PTR;
typedef boost::weak_ptr<KViewGroup> KViewGroup_WEAK_PTR;
class KMenuBase;
typedef boost::shared_ptr<KMenuBase> KMenuBase_PTR;
enum KVIEWTYPE
{
	KVIEW_BASE = 0,
	KVIEW_WINDOW = 1,
	KVIEW_BUTTON = 2,
	KVIEW_TEXT = 3,
	KVIEW_LIST = 4,
	KVIEW_CHECKBOX = 5,
	KVIEW_RADIOBOX = 6,
	KVIEW_SLIDER = 7,
	KVIEW_PROGRESS = 8,
	KVIEW_IMAGECTRL = 9,
	KVIEW_MOVEABLE = 10,
	KVIEW_STATIC = 11,
	KVIEW_RADIOBOXGROUP = 12,
	KVIEW_GALLERY = 13,
	KVIEW_GALLERY_ITEM = 14,
	KVIEW_LIST_ITEM = 15,
	KVIEW_EDIT = 16,
	KVIEW_MENU = 17,
	KVIEW_GROUP = 18
};

enum VIEW_TRANSFORM_FLAG
{
	VIEW_TRANSFORM_ROTATE = 1,
	VIEW_TRANSFORM_SCALE  = 2,
	VIEW_TRANSFORM_TRANSLATE = 4,
	VIEW_TRANSFORM_SKEW = 8,
	VIEW_TRANSFORM_BOUND = 16,

	VIEW_TRANSFORM_ALL = 0xffff,
};


// 
#define PropertyPARA_ID_POS_X		1
#define PropertyPARA_ID_POS_Y		2
#define PropertyPARA_ID_Opacity		3
#define PropertyPARA_ID_RotateAngle	4
#define PropertyPARA_ID_ScaleX		5
#define PropertyPARA_ID_ScaleY		6
#define PropertyPARA_ID_View		200
#define PropertyPARA_ID_USER		1000 //

//
#define KN_REUSLT_OK			0
#define KN_REUSLT_CANCLE		1
#define KN_REUSLT_USER			100

class KScreen;
class KTextView;
KScreen* GetGlacierScreen();
class API KView : public KShowObject, public sigslot::has_slots<>, public boost::enable_shared_from_this<KView>
{
public:
	KView();
	virtual ~KView();
	virtual void shared_ptr_inited(); 

	virtual void Release();
	virtual kn_bool Create(kn_int iX, kn_int iY, kn_int iWidth, kn_int iHeight);
    virtual kn_bool Create(const RERect& rect);

	//groupview  draw,drawRefreshSurface
	virtual void Draw(IRESurface* pDstSurface, kn_int x, kn_int y);
	virtual void Draw(IRESurface* pDstSurface, LSTRECT& rect, kn_int x, kn_int y);
	virtual kn_bool DoMessage(KMessage* pMsg);
	virtual kn_bool DoFocusMessage(KMessage* pMsg);

	//viewsurfacecachesurfacecachesurface
	virtual void RefreshSurface(IRESurface* pDstSurface, kn_int x, kn_int y);

	virtual void RefreshCache();

	void	enableCache(kn_bool b);
	KScreen* GetScreen();
	void SetScreen(KScreen * p);
	KVIEWTYPE getType();

	//drawable 
    void createTextDrawableHelper(KTextDrawable_PTR* text_da_,kn_string str, int fontsize, kn_int x,kn_int y, kn_int w, kn_int h, REColor r = RE_ColorBLACK, REPaint::Align align= REPaint::kLeft_Align);
	void createColorDrawableHelper(KColorDrawable_PTR* color_da, kn_int x,kn_int y, kn_int w, kn_int h, REColor r = RE_ColorBLACK);

	//
	void	SetShieldMsg(kn_bool b);

	virtual kn_uint addDrawable(KDrawable_PTR); //drawable

	void enableMessage(kn_bool b);

	virtual void GetPosition(kn_int& iX, kn_int& iY);
	virtual REPoint GetPosition();
	virtual void GetScreenXY(kn_int &x, kn_int &y);
	virtual void SetScreenPosition(kn_int iX, kn_int iY);
	virtual void SetPosition(kn_int iX, kn_int iY);
	virtual void SetPositionX(kn_int iX);
	virtual void SetPositionY(kn_int iY);
	virtual kn_bool HasInvalidRect();
	virtual LSTRECT GetInvalidRect();
	virtual void SetParent(KViewGroup_WEAK_PTR pPageView);
	virtual KViewGroup_PTR GetParent();

	////////////  
	void requestSetPosition(kn_int iX, kn_int iY);
	///////////////

	virtual void UpdateUI ();
	// 
	//view
	virtual void InvalidateRect(RERect r);
	//
	virtual void InvalidateView(kn_bool bRefresh=TRUE);
	//view
	virtual void InvalidateForParent(RERect& r);
	virtual void clearInvalidRect();

	// viewview,parent
	virtual kn_bool isPointInView(int x, int y);
	// 
//	virtual RERect GetRect();
	virtual void SetRect(const RERect& rect);
	// 
	// 
	virtual RERect GetBoundRect();
	////////

	// , 
	virtual void SetTranslate(REScalar dx, REScalar dy);
	// , 
	virtual void SetScale(REScalar sx, REScalar sy, REScalar px = 0, REScalar py = 0);
	virtual void SetScalePoint( REScalar px, REScalar py );
	virtual void SetScaleX( REScalar sx );
	virtual void SetScaleY( REScalar sy );

	// , 
	virtual void SetRotatePoint( REScalar px = 0, REScalar py = 0);
	virtual void SetRotateAngle( kn_float degrees);
	virtual void SetRotate(kn_float degrees, REScalar px = 0, REScalar py = 0);
	// , 
	virtual void SetSkew(kn_float sx, kn_float sy, REScalar px = 0, REScalar py = 0);
	virtual void SetBoundRect(const RERect& rect);

	//view
	virtual void getMatrix( REScalar x, REScalar y, REMatrix& mat);


	// Slot
	//group
	virtual void OnMove(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnDown(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnUp(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnDClick(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnRDown(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnRUp(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnRDClick(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg);
	virtual void OnWheel(KMessageMouseWheel* pMsg);

	virtual void OnTouchMove(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg);
	virtual void OnTouchDown(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg);
	virtual void OnTouchUp(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg);

	virtual void OnGesture(KGesture* pGesture);

	//viewimage,TextView
	IRESurface* renderToSurface();
	KTextView* renderToView();

	// DoMessage,,
	virtual void onDownDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onMoveDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onUpDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onWheelDirect(KMessageMouseWheel* pMsg); 
	virtual void onDragDirect(KMessageDrag* mag);
	virtual kn_bool OnUserMsg(KMessage* pMsg);

	virtual void onTouchDownDirect(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg); 
	virtual void onTouchMoveDirect(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg); 
	virtual void onTouchUpDirect(kn_int iScreenX, kn_int iScreenY, KMessageTouch* pMsg); 

	void recogGesture(KMessageTouch* pMsg);

	void enableGesture(kn_bool b);

	void handleMouseDown(KMessage* pMsg);
	void handleMouseMove(KMessage* pMsg);
	void handleMouseUp(KMessage* pMsg);

	kn_bool IsMousePicked();

	REScalar getRotateAngle();
	void getRotatePoint(REScalar& x, REScalar& y);

	//
	virtual void setViewFocus();
	virtual void unSetViewFocus();
	kn_bool bViewFocus();

	virtual void setViewActive();
	virtual void unSetViewActive(kn_bool unsetScreen = TRUE);

	// doModal
	kn_int doModal();
	//b_del_view view
	void endModal(kn_int iResult, kn_bool b_del_view = FALSE);
	//	,,windowsmainforwindows.cpp,KView.cpp 
	int runModalLoop();	

	////
	virtual kn_bool isChange(kn_int para_id, kn_double v);
	virtual void doChange(kn_int para_id, kn_double v);
	virtual kn_double getParaValue(kn_int para_id);

	RERect GetScreenRect(RERect);

	void showMenu(KMenuBase_PTR p_menu, int x, int y);


	virtual void viewSizeChange();
	//void SetViewChangeType(IN LRMethod LeftType,IN LRMethod RightType,IN BTMethod TopType,IN BTMethod BottomType);
	virtual void SaveOriginalViewRect();
	virtual RERect getDrawRectBaseOnChild();

	// 
	//
	//void addRef();
	////
	//void decRef();
	////
	//virtual kn_bool isRef();

    void setName(const kn_string& );
	kn_string& getName();

	void setID(kn_int id);
	kn_int getID();

    void setTip(const kn_string& s, kn_int t1 = NO_TIMER, kn_int t2 = NO_TIMER);
	void enableTip(kn_bool b);
	virtual void showTip(int delay_time, int hide_time);//  -1
	void hideTip();
	void showTipCallback(int);
	void hideTipCallback(int);

	// signs
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_move;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_down;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_up;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_dclick;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_rdown;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_rup;
	sigslot::signal3<kn_int, kn_int,KMessageMouse*> m_sign_rdclick;

	// signal
	sigslot::signal3<kn_int, kn_int, KMessageMouse* > m_clicked_pos_signal;
	sigslot::signal1<KView_PTR> m_clicked_signal;	//	sender view

	sigslot::signal0<> m_sign_focus;
	sigslot::signal0<> m_sign_unfocus;

	sigslot::signal0<> m_sign_active;
	sigslot::signal0<> m_sign_unactive;

	sigslot::signal0<> m_mouse_enter_signal;
	sigslot::signal0<> m_mouse_leave_signal;

	sigslot::signal1<KMessageKey*> m_sign_key_down;
	sigslot::signal1<KMessageKey*> m_sign_key_up;
	sigslot::signal1<KMessageMouseWheel*> m_sign_wheel_down;
	//m_sign_keyboard_inputkeydown
	sigslot::signal1<KMessageInput*> m_sign_keyboard_input;

	sigslot::signal1<KMessage3Dx*> m_sign_3dx;

	// 
	sigslot::signal3<kn_int, kn_int,KMessageTouch*> m_sign_touchmove;
	sigslot::signal3<kn_int, kn_int,KMessageTouch*> m_sign_touchdown;
	sigslot::signal3<kn_int, kn_int,KMessageTouch*> m_sign_touchup;

	//Gesture
	sigslot::signal1<KGesture*> m_sign_gesture;


protected:
	//viewid, view group
	kn_int m_id;

	//viewname
	kn_string m_name;

	////////
	int	m_transform_flag;
	REPoint m_translate_point;
	REPoint m_scale_size;
	REPoint m_scale_xy;
	REScalar m_rotate_angle;
	REPoint m_rotate_point;
	RERect m_skew_para;
	RERect m_rect_bound;

	//	KViewGroup
	KViewGroup_WEAK_PTR m_p_parent;		
	// screenview
	KScreen*	m_p_screen;

	KVIEWTYPE m_e_viewtype;

	kn_dword m_dw_touctpoint_count;		// 
	//view
	kn_bool	m_b_mouse_in_view;


	boost::shared_mutex m_rectInvalid_mutex;
	LSTRECT m_lst_rect_invalid;		//	

	IRESurface* m_pSurface;

	kn_string   m_tip_txt;
	// 
	boost::shared_mutex m_lst_drawable_mutex; //drawabledrawable
	VEC_DRAWABLE m_lst_drawable;

	kn_int m_i_modal_result;

	//  true
	kn_bool m_shield_msg; 
	// 
	kn_bool m_b_modal_exit;
	kn_bool		m_b_cache;
	kn_bool		m_b_update_cache;
	//
	kn_bool m_b_do_msg;
	//
	kn_bool m_b_focus;
	//()
	kn_bool m_b_active;

	// 
	kn_bool m_b_mouse_picked;
	kn_bool m_b_rmouse_picked;

	kn_bool m_b_show_tip;
	kn_int	m_tip_id; // tiptip tip
	kn_int  m_tip_delay_time; //tip
	kn_int  m_tip_hide_time; //
	KTimer_PTR m_delay_timer;
	KTimer_PTR m_hide_timer;

	KGestureDetector* m_p_gesture_detector;

	// 
	kn_bool m_b_enable_gesture;
};

//view
typedef boost::shared_ptr<KView> KView_PTR;
typedef boost::weak_ptr<KView> KView_WEAK_PTR;
typedef vector<KView_PTR> LSTVIEW;

#define VIEW_PTR(T) boost::dynamic_pointer_cast<T>
//typedef vector<KView*>  LSTVIEW;

void MyTraceA(const char* szFormat, ... );


#endif
