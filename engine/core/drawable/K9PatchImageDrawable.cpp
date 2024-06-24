//  **************************************
//  File:        K9PatchImageDrawable.cpp
//  ***************************************
#include "K9PatchImageDrawable.h"

K9PatchImageDrawable::K9PatchImageDrawable()
{
	Initialize();
}

K9PatchImageDrawable::K9PatchImageDrawable(const kn_string& strFile)
{
	Initialize();
	kn_bool bOK = CreateFromFile(strFile);
	GetsrcRect();  //rect

	ASSERT(bOK);
}

K9PatchImageDrawable::K9PatchImageDrawable(IRESurface* pSurface,  kn_bool b_out )
{
	Initialize();
	CreateFromSurface(pSurface, b_out);
	GetsrcRect();  //rect

}

K9PatchImageDrawable::~K9PatchImageDrawable(void)
{
	m_Row = 0;
	m_Col = 0;
	m_DesRect.clear();
	m_srcRect.clear();
	Release();
}

void K9PatchImageDrawable::Initialize()
{
	KImageDrawable::Initialize();
	m_Row = 0;
	m_Col = 0;
	m_DesRect.clear();
	m_srcRect.clear();

	m_type = KDrawable::KDRAWABLE_9PATCH_IMAGE;

	setAutoSize(TRUE);
}

typedef struct stLINE_
{
    int x1;
    int x2;
    stLINE_()
    {
        x1 = x2 = 0;
    }
    stLINE_(int a,int b)
    {
        x1 = a;
        x2 = b;
    }
}stLINE;

void K9PatchImageDrawable::GetsrcRect()
{
	m_srcRect.clear();



	vector<stLINE> xLine;
	vector<stLINE> yLine;

	kn_byte* pBuff = m_p_surface->GetBitmapBuffer();
	int xpitch = m_p_surface->GetXPitch();
	int ypitch = m_p_surface->GetYPitch();
	int x1 = 1;
	int x2 = 1;
	int pw=m_p_surface->GetWidth();
	int ph=m_p_surface->GetHeight();
	bool bBlackLine = false;
	
	//
	for(int i = 1; i < pw;i++)
	{
		//
		int addr = i*xpitch;
		if(pBuff[addr] == 0 && pBuff[addr+1] == 0 && pBuff[addr+2] == 0 && pBuff[addr+3] != 0)
		{
			if(!bBlackLine)
			{
				xLine.push_back(stLINE(x1,x2 - 1));  //
				x1 = x2;
			}
			bBlackLine = true;
		}
		else
		{
			if(bBlackLine)
			{
				xLine.push_back(stLINE(x1,x2 - 1)); //
				x1 = x2;
			}
			bBlackLine = false;
		}

		x2++;
	}
	xLine.push_back(stLINE(x1,x2 )); //+1 forx2+1  zhic

	//
	x1 = 1;
	x2 = 1;
	bBlackLine = false;
	for(int i = 1; i < ph;i++)
	{
		//
		int addr = i*ypitch;
		if(pBuff[addr] == 0 && pBuff[addr+1] == 0 && pBuff[addr+2] == 0 && pBuff[addr+3] != 0)
		{
			if(!bBlackLine)
			{
				yLine.push_back(stLINE(x1,x2 - 1));
				x1 = x2;
			}
			bBlackLine = true;
		}
		else
		{
			if(bBlackLine)
			{
				yLine.push_back(stLINE(x1,x2 - 1));
				x1 = x2;
			}
			bBlackLine = false;
		}

		x2++;
	}
	yLine.push_back(stLINE(x1,x2));


	//rect
	m_Row = yLine.size();
	m_Col = xLine.size();
	for(int i = 0; i < m_Row; i++)
	{
		for(int j = 0; j < m_Col; j++)
		{
			m_srcRect.push_back(RERect::MakeXYWH(xLine[j].x1, yLine[i].x1, xLine[j].x2-xLine[j].x1, yLine[i].x2-yLine[i].x1));
		}
	}
}

void K9PatchImageDrawable::GetDesRect()
{
	m_DesRect.clear();

	float xScale = 1.0f;
	float yScale = 1.0f;

	int fix_w=0;   // 
	int fix_h=0;

	int zoom_w=0;   // 
	int zoom_h=0;
	for(int i = 0; i < m_Col; i++)
	{
		if((i & 0x01) == 0)
		{
			fix_w += m_srcRect[i].width();  // 
		}
		else
		{
			zoom_w += m_srcRect[i].width(); // 
		}
	}

	for(int j = 0; j < m_Row; j++)
	{
		if((j & 0x01) == 0)
		{
			fix_h += m_srcRect[j*m_Col].height(); // 
		}
		else
		{
			zoom_h += m_srcRect[j*m_Col].height();// 
		}
	}


	//if(fix_w > m_rectScaleBound.width() || fix_h > m_rectScaleBound.height())
	//{
	//	//
	//	xScale = 1.0f;
	//	yScale = 1.0f;

	//	m_Row = 1;
	//	m_Col = 1;

	//	m_srcRect.clear();
	//	int W = m_p_surface->GetWidth();
	//	int H = m_p_surface->GetHeight();
	//	m_srcRect.push_back(RERect::MakeXYWH(1, 1, W, H));
	//	m_DesRect.push_back(RERect::MakeXYWH(0, 0, m_rectScaleBound.width(), m_rectScaleBound.height()));
	//	return;
	//}
	//else
	{
		//
		xScale = (float)(m_rectScaleBound.width() - fix_w) / zoom_w;
		yScale = (float)(m_rectScaleBound.height() - fix_h) / zoom_h;

		//rect
		bool xzoom = false;  //
		bool yzoom = false;
		float x = 0;//m_srcRect[0].fLeft;  //rect
		float y = 0;//m_srcRect[0].fTop;   //rect
		for(int i = 0; i < m_Row; i++)
		{
			x = 0;//m_srcRect[0].fLeft;
			xzoom = false;
			for(int j = 0; j < m_Col; j++)
			{
				RERect& rt = m_srcRect[j + i * m_Col];
				if(xzoom && yzoom)  //xY
				{
					RERect trt = RERect::MakeXYWH(x, y, rt.width() * xScale, rt.height() * yScale);
					x += rt.width() * xScale;  // rectx
					m_DesRect.push_back(trt);				
				}
				else if(xzoom)  //x
				{
					RERect trt = RERect::MakeXYWH(x, y, rt.width() * xScale, rt.height());
					x += rt.width() * xScale;
					m_DesRect.push_back(trt);
				}
				else if(yzoom) //Y
				{
					RERect trt = RERect::MakeXYWH(x, y, rt.width(), rt.height() * yScale);
					x += rt.width();
					m_DesRect.push_back(trt);
				}
				else
				{
					RERect trt = RERect::MakeXYWH(x, y, rt.width(), rt.height());
					x += rt.width();
					m_DesRect.push_back(trt);
				}

				xzoom = !xzoom;  //
			}

			if(yzoom)
			{
				y += m_srcRect[i * m_Col].height() * yScale;  // recty
			}
			else
			{
				y += m_srcRect[i * m_Col].height();  // recty
			}

			yzoom = !yzoom;  //
		}
	}
}

void K9PatchImageDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX, int iDstY)
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

	m_rectScaleBound = m_rect;
	RERect rectDst = RERect::MakeXYWH(iTarX, iTarY, m_rectScaleBound.width(), m_rectScaleBound.height());
	pDstSurface->ClipRect(rectDst);


	GetDesRect();  //rect


	//if (m_Row == 3 && m_Col == 3)
	//{
	//	RERect r_dst;
	//	r_dst.fLeft = m_DesRect[0].left() + iTarX;
	//	r_dst.fTop = m_DesRect[0].top() + iTarY;
	//	r_dst.fRight = m_DesRect[8].right() + iTarX;
	//	r_dst.fBottom = m_DesRect[8].bottom()+ iTarY;


	//	pDstSurface->drawBitmapNine( m_p_surface, m_srcRect[4], r_dst, &m_paint );
	//}
	//else
	{
		//
		for(int i = 0; i < m_Row; i++)
		{
			for(int j = 0; j < m_Col; j++)
			{
				RERect rectDst1 = m_DesRect[i*m_Col+j];
				rectDst1.fLeft += iTarX;
				rectDst1.fTop += iTarY;
				rectDst1.fRight += iTarX;
				rectDst1.fBottom += iTarY;

				RERect rectsrc1 = m_srcRect[i*m_Col+j];
				pDstSurface->DrawBitmapRectToRect(m_p_surface, &rectsrc1, rectDst1, &m_paint);
			}
		}

	}

	EndDraw(pDstSurface, pMatrix);
}

