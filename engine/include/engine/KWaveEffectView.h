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

	virtual void init( kn_string file); //tipviewscreen
	virtual void init( IRESurface* pSurface, kn_bool b_out = FALSE); 

	//speed 40
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
//
typedef boost::shared_ptr<KWaveEffectView> KWaveEffectView_PTR;

#endif

