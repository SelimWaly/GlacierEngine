//  **************************************
//  File:        KTimer.h
//  ***************************************
#ifndef KTimer_DEFINED
#define KTimer_DEFINED

#include "NE_type.h"
#include <boost/enable_shared_from_this.hpp>  
#include <boost/timer/timer.hpp>
#include <boost/thread.hpp>
#include "sigslot.h"
//#include "KView.h"
class KScreen;
typedef kn_int TimerID;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;

class KView;
typedef boost::weak_ptr<KView> KView_WEAK_PTR;

class API KTimer:public boost::enable_shared_from_this<KTimer>
{
public:
	KTimer(); 
	KTimer(int interval, int times = -1); //   -1  
	~KTimer();

	bool isActive() const; // start stop

	void setInterval(int v);
	kn_int getInterval() const;

	void setTimes(int value);
	int getTimes();

	bool start(); //screenm_p_viewscreenm_p_view
	void restart(); 
	void stop();
	bool check(); //

	kn_int64 elapsedTime();

	//view
	void setView(KView_WEAK_PTR);
	typedef sigslot::signal1<kn_int> TimeOutSignal;	
	TimeOutSignal m_timeout_signal;

private:
	KView_WEAK_PTR m_p_view;
	boost::timer::cpu_timer m_timer;

	kn_int m_interval;
	int m_times;
	int m_time; // 
	kn_bool m_b_run;
	nanosecond_type m_last_time;
};
typedef boost::shared_ptr<KTimer> KTimer_PTR;
typedef std::list<KTimer_PTR> LSTTIMER;

//
void AddGLACIERTimer(KTimer_PTR);
void CheckGLACIERTimer();
/////////////////////////////////////////////

class API KThreadTimer:public boost::noncopyable
{
public:
	KThreadTimer();
	~KThreadTimer();



	// 
	bool IsActive() const;
	TimerID GetTimerID() const;
	kn_int Interval() const;

	void SetSingleShot(bool value);
	bool IsSingleShot() const;

	bool Start(TimerID id, kn_int msec);
	void Stop();
	kn_int64 ElapsedTime();

	typedef sigslot::signal1<kn_int> TimeOutSignal;	
	TimeOutSignal m_timeoutSignal;

private:
	static void ThreadProc(KThreadTimer* p);

	boost::timer::cpu_timer m_timer;
	boost::thread* m_pThread;
	TimerID m_id;
	kn_int m_interval;
	bool m_bSingleShot;
};


#endif
