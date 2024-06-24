//  **************************************
//  File:        KWaveEffectDrawable.h
//  ***************************************
#ifndef K_WAVEEFFECT_DRAWABLE_H
#define K_WAVEEFFECT_DRAWABLE_H


#include "KImageDrawable.h"

#define WAVE_EFFECT_TOTALFRAME 64
class API KWaveEffectDrawable : public KImageDrawable
{
public :
	KWaveEffectDrawable();
	KWaveEffectDrawable(const kn_string& strFile);
	KWaveEffectDrawable(IRESurface* pSurface, kn_bool b_out = FALSE);
	virtual ~KWaveEffectDrawable();
	unsigned char* m_p_data;
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	void setFrame(int n);
	int getFrame();
protected:
	int m_i_frame;
	IRESurface* m_wave_surface;
};
typedef boost::shared_ptr<KWaveEffectDrawable> KWaveEffectDrawable_PTR;

#endif
