//  **************************************
//  File:        GLACIERAnimation.h
//  ***************************************
#pragma once
#include "NE_type.h"
#include <vector>
#include "KEasingCurve.h"
#include "DataSync.h"
#include <boost/timer/timer.hpp>
class KScreen;
class API CPropertyAnimationData:public KObject
{
public:
	CPropertyAnimationData(CPropertyBase* tar, KEasingCurve::Type= KEasingCurve::InOutCirc); //targetsrcpview
	CPropertyAnimationData(CPropertyBase* src, CPropertyBase* tar, KEasingCurve::Type = KEasingCurve::InOutCirc);
	virtual ~CPropertyAnimationData(void);	
	CPropertyBase* getCurrent(kn_double v);
	KScreen* getScreen();
private:
	CPropertyBase* m_p_source;
	CPropertyBase* m_p_target;
	//
	KEasingCurve m_easing;
};
typedef vector<CPropertyAnimationData*> CPropertyAnimationDataList;

#define LOOP_ALWAYS 9999999
class API CGLACIERAnimation :public KObject
{
public:
	CGLACIERAnimation(void);
	CGLACIERAnimation(kn_int duration, kn_int wait_time, kn_int loop_wait_time=0);
	virtual ~CGLACIERAnimation(void);

	enum RunState
	{
		PLAYING,
		PAUSE,
		STOP,
		NO_START
	};

	enum LoopType
	{
		LOOP_TIME,
		LOOP_PINGPONG
	};
	void init();
	//pause
	kn_bool addAnimationData(CPropertyAnimationData*);
	void Play();
	void Stop();
	void Pause();

	KScreen* getScreen();

	void setRunState(RunState e);
	RunState getRunState();
	void setLoopType(LoopType e);	//STOP
	void setLoopTimes(kn_int);
	void setLoopWaitTime(kn_int);
	//
	void setFrameTime(kn_uint);

	void setDuration(kn_int);

	kn_bool onPlay(kn_int);
private:

	boost::shared_mutex m_ani_data_mutex;
	CPropertyAnimationDataList m_ani_data_lst;

	kn_bool updateFrame( kn_double percent, kn_bool b_draw = FALSE);

	//
	kn_double getPercent(kn_int current);

//	CPropertyBase* m_p_current;
	boost::mutex m_runing_mutex;
	RunState m_e_runing;

	// 
	kn_int m_duration;

	// 
	kn_uint m_frame_time;

	//
	kn_int m_pause_time;

	// stopplay
	kn_int m_last_elapsed;

	boost::timer::cpu_timer m_pause_timer;

	//
	kn_int m_wait_time;

	//
	LoopType m_loop_type;
	//
	kn_int	m_loop_times;
	//
	kn_int m_current_loop;
	// 
	kn_int	m_loop_wait_time;
};
typedef vector<CGLACIERAnimation*> CGLACIERAnimationDataList;
