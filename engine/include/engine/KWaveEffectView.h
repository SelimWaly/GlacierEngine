//  **************************************
//  File:        KWaveEffectView.h
//  ***************************************
#ifndef KWaveEffectView_DEFINED
#define KWaveEffectView_DEFINED

#include "KView.h"
#include "KMoveableView.h"
#include "KWaveEffectDrawable.h"
#include "AnimationThread.h" 

#define PropertyPARA_ID_WAVE_FRAME PropertyPARA_ID_View+1

class API KWaveEffectView : public KMoveableView // KView
{
public:
	KWaveEffectView();
	virtual ~KWaveEffectView();

	virtual void init( kn_string file); //传入的是tip针对的view的范围，screen全局坐标
	virtual void init( IRESurface* pSurface, kn_bool b_out = FALSE); 

	//speed 播放速度，40始终，越大越快
	void play(int speed = 40);
	void stop();
	////
	virtual kn_bool isChange(kn_int para_id, kn_double v);
	virtual void doChange(kn_int para_id, kn_double v);
	virtual kn_double getParaValue(kn_int para_id);
protected:
	KWaveEffectDrawable_PTR	m_wave_drawable;
	CAnimationThread m_mov_ani_thread;
	int	m_i_frame;
	int m_speed;
};
//使用智能指针管理
typedef boost::shared_ptr<KWaveEffectView> KWaveEffectView_PTR;

#endif

