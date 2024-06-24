//  **************************************
//  File:        KWaveEffectDrawable.cpp
//  ***************************************

///////----------------- AreaBlurDrawable ------------------
#include "KWaveEffectDrawable.h"

KWaveEffectDrawable::KWaveEffectDrawable()
{
//	m_b_clip_rect = FALSE;
//	m_paint.setMaskFilter(REBlurMaskFilter::Create(25, REBlurMaskFilter::kNormal_BlurStyle, REBlurMaskFilter::kHighQuality_BlurFlag))->unref();
//	m_paint.setColor(ARGB(255,50,100,150));
	m_i_frame = 0;
	m_rect.setXYWH(0,0,1,1);
}

KWaveEffectDrawable::KWaveEffectDrawable(const kn_string& strFile):KImageDrawable(strFile)
{
	if(m_p_surface ) 
	{
		setRect(0,0, m_p_surface->GetWidth(), m_p_surface->GetHeight()*2);
	}
}
KWaveEffectDrawable::KWaveEffectDrawable(IRESurface* pSurface, kn_bool b_out):KImageDrawable(pSurface, b_out)
{
	if(m_p_surface) 
	{
		setRect(0,0, m_p_surface->GetWidth(), m_p_surface->GetHeight()*2);
	}
}

KWaveEffectDrawable::~KWaveEffectDrawable()
{
	
}

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

void KWaveEffectDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX, int iDstY)
{
	readLock lock(m_drawable_draw_mutex); 
	if (! BeginDraw(pDstSurface, pMatrix, iDstX, iDstY ) )
	{
		return;
	}

	if(m_p_surface == NULL) 
	{
		EndDraw(pDstSurface, pMatrix);
		return ;
	}
	int iTarX = iDstX + m_rect.left();
	int iTarY = iDstY + m_rect.top();
	RERect rectDst = RERect::MakeXYWH(iTarX, iTarY, m_rect.width(), m_rect.height());
	RERect rectsrc = RERect::MakeXYWH(0, 0, m_p_surface->GetWidth(), m_p_surface->GetHeight());

	pDstSurface->DrawBitmap(m_p_surface, iTarX, iTarY, &m_paint);

// draw wave
	int iWidthsrc = m_p_surface->GetWidth();
	int iHeightsrc = m_p_surface->GetHeight();

	int iHeightDest = pDstSurface->GetHeight();

	int iNumFrames = WAVE_EFFECT_TOTALFRAME;
	int iWaveHeight = 100;
	int iRippleGranularity = 40;


	int iTargetLine = 0;
	int iSourceLine = 0;
	double dRipples = 0; 
	double dFrameAsRadians = 0;

	dRipples = iHeightsrc / iRippleGranularity; 

	int iFrame = m_i_frame % iNumFrames;
	dFrameAsRadians = 2 * PI * (double)iFrame / (double)iNumFrames;

	 for (int y = 0; y < iHeightsrc; y++)
	{

		int iDisplacement = (int)(dRipples * 5 / 3 						
			* sin((double)((dRipples) * (iHeightsrc - y) * 8 / (double)(y + 1) / 2 )  + dFrameAsRadians) 
			* (y + iWaveHeight) * 3 / (double) iHeightsrc / 2) ;

		if (y < iHeightsrc/10) 
		{
			iDisplacement = iDisplacement *2 / 5;
		}

		if (y < iHeightsrc/5) 
		{
			iDisplacement = iDisplacement*3/5;
		}

		iSourceLine = (y < iDisplacement) ? y : y - iDisplacement;
		iSourceLine = max(0, min( iSourceLine, iHeightsrc - 1));

		

		if ((y < 1) || (iHeightsrc <  y ))
		{
			continue;
		}

		//iTargetLine = iTarY + y ;
		RERect draw_rectDst = RERect::MakeXYWH(iTarX, iTarY + y + iHeightsrc-2, iWidthsrc, 1);
		RERect draw_rectsrc = RERect::MakeXYWH(0, iHeightsrc - iSourceLine, iWidthsrc, 1);

		pDstSurface->DrawBitmapRectToRect(m_p_surface, &draw_rectsrc, draw_rectDst, &m_paint);

	}

	//m_i_frame++;
	EndDraw(pDstSurface, pMatrix);
}

void KWaveEffectDrawable::setFrame(int n)
{
	writeLock lock(m_drawable_draw_mutex); 
	m_i_frame = n;
}

int KWaveEffectDrawable::getFrame()
{
	return m_i_frame ;
}
