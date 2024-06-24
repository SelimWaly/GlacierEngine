//  **************************************
//  File:        message.h
//  ***************************************
#ifndef K_MESSAGE_H
#define K_MESSAGE_H

#include <boost/thread/thread.hpp>
#include "KObject.h"
void MyTrace(LPCTSTR lpsz, ...);
//
enum KMSGTYPE
{
	KMSG_TYPE_NONE, //,
	KMSG_TYPE_KEY, //
	KMSG_TYPE_POS, //
	KMSG_TYPE_MOUSE, //
	KMSG_TYPE_MOUSE_WHELL, //
	KMSG_TYPE_TOUCH, //
	KMSG_TYPE_3DX,	//	3Dx
	KMSG_TYPE_USER,	//
	KMSG_TYPE_INPUT,  //
	KMSG_TYPE_DRAG  //
	
};

enum KMESSAGETYPE
{
	KMSG_BEGIN,

	KMSG_KEYDOWN,
	KMSG_KEYUP,
	
	KMSG_MOUSE_START,
	KMSG_LBBUTTONDOWN,
	KMSG_LBBUTTONUP,
	KMSG_RBBUTTONDOWN,
	KMSG_RBBUTTONUP,
	KMSG_MBBUTTONDOWN,
	KMSG_MBBUTTONUP,
	KMSG_MOUSEMOVE,
	KMSG_LBUTTONDBLCLK,
	KMSG_MBUTTONDBLCLK,
	KMSG_RBUTTONDBLCLK,
	KMSG_MOUSEWHEEL,

	KMSG_MOUSE_END,
	
	KMSG_TIMER,

	KMSG_TOUCH_UP,
	KMSG_TOUCH_MOVE,
	KMSG_TOUCH_DOWN,

	KMSG_3DX,

	KMSG_SCREEN_DRAW,

	KMSG_TYPE_INPUT_ING,  // 
	KMSG_TYPE_INPUT_END,  // 
	KMSG_TYPE_CHAR,

	KMSG_TYPE_IME_UPDATE, // Edit
	KMSG_DRAG, //
	KMSG_DRAG_UP, //up

	KMSG_END,
	KMSG_USER = 10000

};

enum KMESSAGETYPE
{//windows
	//KGLACIERMSG_DRAW = 20000,
	//KGLACIERMSG_DRAG = 20001, //
	//KGLACIERMSG_DRAG_UP = 20002, //up
	KGLACIERMSG_USER=30000
};

#define KMSG_KEYFLAG_CONTROL 8
#define KMSG_KEYFLAG_SHIFT	 4
#define KMSG_KEYFLAG_ALT	 2

enum KMESSAGE_RETURN_TYPE
{
	
	KMSG_RETURN_DEFAULT, // 
	KMSG_RETURN_DILE,  //
	KMSG_RETURN_CONTINUE, //
};
class KView;
typedef boost::shared_ptr<KView> KView_PTR;

class API KMessage : public KObject
{
public:
	KMessage();
	virtual ~KMessage(){};

	KMSGTYPE m_msg_class_type; //
	KMESSAGETYPE m_msg_type; //
	kn_uint m_wParam;
	kn_uint m_lParam;
	KView_PTR  m_p_view;
	KMESSAGE_RETURN_TYPE m_b_idle;
	static KMessage* getMsgForWin32( HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam);
	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam){};
	//
	kn_bool HasPos();
	void setIdle(KMESSAGE_RETURN_TYPE idle){m_b_idle = idle;};
	KMESSAGE_RETURN_TYPE getIdle(){return m_b_idle;};
};

class API KMessageKey : public KMessage
{
public:
	KMessageKey();
	virtual ~KMessageKey(){};

	kn_int m_key_id;
	kn_int m_key_flag;//
	kn_int m_repeat_count;//
	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
};

class API KMessagePos : public KMessage
{//
public:
	KMessagePos();
	virtual ~KMessagePos(){};

	kn_int m_pos_x; 
	kn_int m_pos_y;
};

class API KMessageMouseWheel : public KMessagePos
{
public:
	KMessageMouseWheel();
	virtual ~KMessageMouseWheel(){};
	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	kn_int m_roll;
	kn_int m_key_flag;//
};


class API KMessageMouse : public KMessagePos
{
public:
	KMessageMouse();
	virtual ~KMessageMouse(){};

	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
};

class API KMessageTouch : public KMessagePos
{
public:
	KMessageTouch(HWND hwnd);
	virtual ~KMessageTouch();

	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	KMessageTouch* deepCopy();

public:

	kn_int m_touch_id;

	HWND m_wnd;


	int m_iPointCount;	//	
	int* m_ids;	// point id
	int* m_xs;	// 
	int* m_ys;
 

 
};

class API KMessage3Dx : public KMessage
{
public:
	virtual ~KMessage3Dx(){};

	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	UINT m_message;
};


class API KMessageInput : public KMessageKey
{
public:
	KMessageInput();
	virtual ~KMessageInput(){};
	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	kn_string m_InputStr;
};

// EditText: onTextChange
//TextWatcher::onTextChanged(CharSequence s, int start, int before, int count)
class API KMessageEditTextIME : public KMessageInput
{
public:
	KMessageEditTextIME();
	virtual ~KMessageEditTextIME(){};
	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	//kn_string m_InputStr;


	 // (0)
	kn_int m_i_start;

	// 
	kn_int m_i_before;

	// 
	kn_int m_i_count;

};
class API KMessageDrag : public KMessagePos
{
public:
	KMessageDrag();
	virtual ~KMessageDrag(){};
//	virtual void transMsgForWin32(UINT message, WPARAM wParam, LPARAM lParam);
	KView_PTR   m_p_drag_view;
	kn_int m_drag_type;
	
};

// createwindow 
bool CheckTouchSupport(HWND wnd);



#endif
