//  **************************************
//  File:        AnimationThread.h
//  ***************************************
#pragma once
#include "NE_type.h"
#include <vector>
#include <list>
#include "GLACIERAnimation.h"

using boost::timer::cpu_times;

class API CAnimationThread :public KObject
{
public:
	CAnimationThread(void);
	virtual ~CAnimationThread(void);

	enum RunState
	{
		//		NO_START,
		PLAYING,
		PAUSE,
		STOP
	};

	enum LoopType
	{
		LOOP_TIME,
		LOOP_PINGPONG
	};
	void init();
	kn_bool addAnimation(CGLACIERAnimation*);

	kn_bool clearAnimation();

	virtual void Stop();
	virtual void Start(RunState e=PLAYING);
	void Pause();
	void Play();

	void runInit();
	void run();

	void setRunState(RunState e);
	RunState getRunState();

	void setAutoClearAni(kn_bool e);
	KScreen* getScreen();
	void setFrameTime(kn_uint);

	kn_bool isPlaying();

	void waitAnimationStop();


	void setStopMsg(kn_int id);

	CGLACIERAnimation* addAnimationHelper(KView_PTR, kn_int PARA_ID, double v, kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

	CGLACIERAnimation* addAnimationHelper(KView_PTR, kn_int PARA_ID, double v1, double v2,kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

	CGLACIERAnimation* addRectAnimationHelper(KView_PTR, RERect rect, kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

protected:
	boost::shared_mutex m_ani_data_mutex;
	CGLACIERAnimationDataList m_ani_data_lst;


	boost::mutex m_runing_mutex;
	RunState m_e_runing;
	kn_bool m_auto_clear_ani;
	kn_int m_stop_msg;
	KScreen* m_p_screen;
	kn_uint m_last;
	boost::timer::cpu_timer* m_p_timer;
	kn_int m_ani_id;
	kn_bool m_b_update ;
	kn_bool m_b_pause ;

	kn_uint	m_frame_time;
};

class API CAnimationOwnThread :public CAnimationThread
{
public:
	CAnimationOwnThread(void);
	virtual ~CAnimationOwnThread(void);

	virtual void Stop();
	virtual void Start(RunState e=PLAYING);
	void setAutoKillThread(kn_bool e);
	static void AnimationThreadProc(CAnimationOwnThread* p , RunState e);
	void releaseThread();

private:
	boost::thread* m_pThread;

	kn_bool m_auto_kill_thread;


};


typedef list<CAnimationThread*> CGLACIERAnimationThreadList;

class API CAnimationThreadRun :public KObject
{
public:
	CAnimationThreadRun(void);
	virtual ~CAnimationThreadRun(void);

	void addAnimationThread( CAnimationThread*);

	void removeAnimationThread(CAnimationThread*);
	static void AnimationThreadProc(CAnimationThreadRun*);

private:
	boost::shared_mutex m_ani_data_mutex;
	CGLACIERAnimationThreadList m_ani_data_lst;

	boost::thread* m_pThread;
	bool m_b_run;

	kn_int	m_frame_time;
};

CAnimationThreadRun* getAnimationThreadRun();
void releaseAnimationThreadRun();
