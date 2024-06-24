//  **************************************
//  File:        KGestureDetector.h
//  ***************************************
#ifndef K_KGESTURE_DETECTOR_H
#define K_KGESTURE_DETECTOR_H

#include "message.h"



enum
{
	GESTURE_UNKNOWN,

	GESTURE_ZOOM_BEGIN,
	GESTURE_ZOOM,
	GESTURE_ZOOM_END,

	GESTURE_RORATE_BEGIN,
	GESTURE_RORATE,
	GESTURE_RORATE_END,

	GESTURE_MAX
};



class API KGesture :  public KObject
{
public:
	KGesture();
	virtual ~KGesture(){};

public:
	// zoom, 
	kn_int m_type;

	// 
	kn_float m_zoom_span;

	// 
	kn_float m_center_x;
	kn_float m_center_y;
	 
};

 
class API KTouchPoint:  public KObject
{
 
public:
	KTouchPoint(KMessageTouch* pMsg);
	virtual ~KTouchPoint();


	void calcDistance();

public:

	KMessageTouch* m_p_msgtouch;

	float m_distance;

	kn_float m_center_x;
	kn_float m_center_y;
	 
};


class API KGestureDetector :  public KObject
{
public:
	KGestureDetector();
	virtual ~KGestureDetector(); 

 
	void addTouchMessge(KMessageTouch* pMsg);

	KGesture recogGesture();

private:

	void Release();

private:

	vector<KTouchPoint*> m_v_touchpoints;

};


#endif
