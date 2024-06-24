//  **************************************
//  File:        GLACIERAnimation.cpp
//  ***************************************
#include "GLACIERAnimation.h"
#include "KView.h"
#include "KScreen.h"


//////////////////////////CPropertyAnimationData/////////////////
CPropertyAnimationData::CPropertyAnimationData(CPropertyBase* tar, KEasingCurve::Type type)
{
	m_p_source = tar->copyProperty();
	m_p_target = tar;
	m_easing.SetType(type);
}

CPropertyAnimationData::CPropertyAnimationData(CPropertyBase* src, CPropertyBase* tar, KEasingCurve::Type type)
{
	m_p_source = src;
	m_p_target = tar;
	m_easing.SetType(type);
}

CPropertyAnimationData::~CPropertyAnimationData()
{
	SAFE_DELETE( m_p_source);
	SAFE_DELETE( m_p_target);

}

//
CPropertyBase* CPropertyAnimationData::getCurrent(kn_double v)
{
	 return m_p_source->getCurrent(m_p_target, v, &m_easing);
}

KScreen* CPropertyAnimationData::getScreen()
{
	return m_p_source->getView()->GetScreen();
}

///////////////////////////CGLACIERAnimation///////////////////////////////////////////////////

CGLACIERAnimation::CGLACIERAnimation(void)
{
	init();
}

void CGLACIERAnimation::init()
{
	m_e_runing = STOP;

	// 
	m_duration = 0;

	// 
	m_frame_time = 30;

	m_pause_time = 0;

	//
	m_wait_time = 0;
	m_last_elapsed = 0;

	m_loop_times = 1;
	m_current_loop = 0;
	m_loop_wait_time = 0;
	m_loop_type = LOOP_TIME;
}

CGLACIERAnimation::CGLACIERAnimation(kn_int duration, kn_int wait_time, kn_int loop_wait_time)
{
	init();

	// 
	m_duration = duration;

	//
	m_wait_time = wait_time;
	//
	m_loop_wait_time = loop_wait_time;
}

void CGLACIERAnimation::setDuration(kn_int v)
{
	m_duration = v;
}
CGLACIERAnimation::~CGLACIERAnimation(void)
{
		for(CPropertyAnimationDataList::iterator ite = m_ani_data_lst.begin();ite!=m_ani_data_lst.end();ite++)
		{
			SAFE_DELETE(*ite);
		}
		m_ani_data_lst.clear();
}


kn_bool  CGLACIERAnimation::addAnimationData(CPropertyAnimationData* p)
{
	if ( m_e_runing == STOP )
	{
		writeLock lock(m_ani_data_mutex);
		m_ani_data_lst.push_back(p);
		return TRUE;
	}

	return FALSE;
}



void CGLACIERAnimation::Stop()
{
	setRunState(STOP);
	m_pause_time = 0;
}

void CGLACIERAnimation::Play()
{
	using boost::timer::cpu_times;
	switch (m_e_runing)
	{
	case PAUSE:
		{
			cpu_times const elapsed_times(m_pause_timer.elapsed());
			m_pause_time += (elapsed_times.wall)/(1000000LL) ;
			m_pause_timer.stop();
		}
		break;
	case STOP:

		break;
	case PLAYING:
		return;
		break;
	}

	setRunState(PLAYING);
}

void CGLACIERAnimation::Pause()
{
	setRunState(PAUSE);
	m_pause_timer.start();
}

void CGLACIERAnimation::setRunState(RunState s)
{
	boost::mutex::scoped_lock lock(m_runing_mutex);
	m_e_runing = s;
}
CGLACIERAnimation::RunState CGLACIERAnimation::getRunState()
{
	return m_e_runing;
}

void CGLACIERAnimation::setLoopType(LoopType e)
{
	if ( m_e_runing == STOP )
	{
		m_loop_type = e;
	}
	
}

//
kn_bool CGLACIERAnimation::onPlay(kn_int elapsed)
{
	if (m_e_runing == PAUSE)
	{
		return FALSE;
	}
	if (m_e_runing == STOP)
	{
		m_last_elapsed = elapsed;
		return FALSE;
	}
	kn_int time = elapsed - m_wait_time - m_pause_time - m_last_elapsed;
	if (time >= 0)
	{//
		kn_double  dv = 0; //
		kn_bool ret;
		dv = getPercent(time);
		ret = updateFrame(dv);
		if (m_loop_times != LOOP_ALWAYS)
		{
			if(time > m_loop_times * (m_duration + m_loop_wait_time) )
			{//
				Stop();
			}
		}
		return ret;
	}
	return FALSE;
}

kn_bool CGLACIERAnimation::updateFrame(kn_double dv, kn_bool b_draw)
{
	CPropertyBase* p_pb = NULL;
	KScreen* screen = NULL;

	readLock lock(m_ani_data_mutex);
	for(CPropertyAnimationDataList::iterator ite = m_ani_data_lst.begin();ite!=m_ani_data_lst.end();ite++)
	{
		CPropertyAnimationData*  p_a_data = (*ite);
		p_pb = p_a_data->getCurrent(dv);
		if (p_pb==NULL)
		{
			return FALSE;
		}
		ASSERT(p_pb->getView() ) ;
		
		if (screen==NULL)
		{//
			screen = p_pb->getView()->GetScreen();
		}
		
		if (screen ) screen->addProperty(p_pb);
	}

	if(b_draw && screen != NULL)
	{//
		screen->SetRenderFlag(TRUE);	
	}

	return TRUE;
}

kn_double CGLACIERAnimation::getPercent(kn_int current)
{//current
	kn_double dv = 0;
	//,0
	m_current_loop = current/(m_duration+m_loop_wait_time);
	//
	kn_int current_duration = (m_duration+m_loop_wait_time)*(m_current_loop) + m_duration;
	switch (m_loop_type)
	{
	case LOOP_TIME:
		if ( m_current_loop >= m_loop_times) // current >= current_duration )
		{//
			if (m_loop_times != LOOP_ALWAYS)
			{
				//
				dv = 1;
			} 
			else
			{ //
				dv = 0;
			}
		}
		else 
		{//
			//
			if (m_loop_times != LOOP_ALWAYS)
			{
				dv = (kn_double)(current % (m_duration + m_loop_wait_time) )/(kn_double)m_duration;
			}
			else
			{
				dv = (kn_double)(current % (m_duration) )/(kn_double)m_duration;
			}
		}
		break;
	case LOOP_PINGPONG:
		if (m_loop_times != LOOP_ALWAYS && m_current_loop >= m_loop_times) //current >= current_duration )
		{//
			if (m_loop_times%2 == 0 )
			{//
				dv = 0;
			}
			else
			{//end
				dv = 1;
			}
		}
		else
		{//
			if ( m_current_loop%2 == 0 )
			{//
				dv = (kn_double)(current % (m_duration + m_loop_wait_time) )/(kn_double)m_duration;
			}
			else
			{//
				dv = 1 - (kn_double)(current % (m_duration + m_loop_wait_time) )/(kn_double)m_duration;
			}
		}
		break;
	}

	return dv;
}

void CGLACIERAnimation::setLoopTimes(kn_int n)
{
	m_loop_times = n;
}

KScreen* CGLACIERAnimation::getScreen()
{
	KScreen* screen = NULL;
	readLock lock(m_ani_data_mutex);
	for(CPropertyAnimationDataList::iterator ite = m_ani_data_lst.begin();ite!=m_ani_data_lst.end();ite++)
	{
		CPropertyAnimationData*  p_a_data = (*ite);
		screen = p_a_data->getScreen();
		break;
	}

	return screen;
}

void CGLACIERAnimation::setFrameTime(kn_uint v)
{
	m_frame_time = v;
}
