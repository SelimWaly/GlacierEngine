//  **************************************
//  File:        AnimationThread.h
//  ***************************************
#pragma once
#include "NE_type.h"
#include <vector>
#include <list>
#include "GLACIERAnimation.h"

using boost::timer::cpu_times;

//使用统一线程挂载
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
	//加入动画数据，动画播放过程中包括pause是不能加入的
	kn_bool addAnimation(CGLACIERAnimation*);

	kn_bool clearAnimation();

	virtual void Stop();
	virtual void Start(RunState e=PLAYING);
	void Pause();
	void Play();

	//run的预处理
	void runInit();
	//运行一帧
	void run();

	void setRunState(RunState e);
	RunState getRunState();

	void setAutoClearAni(kn_bool e);
	KScreen* getScreen();
	void setFrameTime(kn_uint);

	//判断是否正在播放
	kn_bool isPlaying();

	//等待动画线程播放结束
	void waitAnimationStop();


	void setStopMsg(kn_int id);

	//以下是方便应用层使用的，封装了动画参数处理的函数，一个函数即可完成动画设置
	CGLACIERAnimation* addAnimationHelper(KView_PTR, kn_int PARA_ID, double v, kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

	CGLACIERAnimation* addAnimationHelper(KView_PTR, kn_int PARA_ID, double v1, double v2,kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

	CGLACIERAnimation* addRectAnimationHelper(KView_PTR, RERect rect, kn_int duration, kn_int wait_time, kn_int loop_wait_time, KEasingCurve::Type = KEasingCurve::InOutCirc);

protected:
	boost::shared_mutex m_ani_data_mutex;
	CGLACIERAnimationDataList m_ani_data_lst;


	boost::mutex m_runing_mutex;
	RunState m_e_runing;

	//动画完成后自动清除动画数据
	kn_bool m_auto_clear_ani;

	//动画停止后发送消息
	kn_int m_stop_msg;

	////////// 动画线程运行时的一些状态量，改为统一线程运行后作为成员
	KScreen* m_p_screen;
	kn_uint m_last; //最后时间
	boost::timer::cpu_timer* m_p_timer;  //cpu_timer构造函数会调用start() 所以改用指针
	kn_int m_ani_id; //screen中的动画id标识
	kn_bool m_b_update ;
	kn_bool m_b_pause ;

	//每帧间隔等待时间 微秒单位
	kn_uint	m_frame_time;
};

//使用独立线程启动, 你知道自己在干什么才使用
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

	//是否动画全部stop后自动退出线程
	kn_bool m_auto_kill_thread;


};


typedef list<CAnimationThread*> CGLACIERAnimationThreadList;

//统一为一个线程驱动动画
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

	//每帧间隔等待时间 微秒单位
	kn_int	m_frame_time;
};

//通过单例获取动画线程实例
CAnimationThreadRun* getAnimationThreadRun();
void releaseAnimationThreadRun();
