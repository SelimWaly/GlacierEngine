//  **************************************
//  File:        KImageDrawable.cpp
//  ***************************************

#include "KImageDrawable.h"
#include "KLog.h"

void KImageDrawable::Initialize()
{
	m_type = KDrawable::KDRAWABLE_IMAGE;
	m_p_surface = NULL;
	m_iFillType = FILL_NORMAL;
	m_b_clip = false;

#ifdef WIN32
	//	 Linux kMedium_FilterLevel 
	m_paint.setFilterLevel(SkPaint::kMedium_FilterLevel); 
#else
	m_paint.setAntiAlias(true);
#endif

	m_b_border = false;
	m_cl_border_color = 0;
	m_i_border_width = 0;
	m_b_out_resource = FALSE;
	m_xmode = SkShader::kRepeat_TileMode;
	m_ymode = SkShader::kRepeat_TileMode;
}


KImageDrawable::KImageDrawable()
{
	Initialize();
}


kn_bool KImageDrawable::checkPoint(int x, int y)
{
	if (m_p_surface)
	{
		if (x >= 0 && x < m_p_surface->GetWidth() && y >=0 && y <  m_p_surface->GetHeight() )
		{
			SkColor c = m_p_surface->GetBitmap()->getColor(x, y);
			if (SkColorGetA(c) > 3)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

KImageDrawable::KImageDrawable(const kn_string& strFile)
{
	Initialize();
	kn_bool bOK = CreateFromFile(strFile);
	ASSERT(bOK);
	SizeToImage();
}

KImageDrawable::KImageDrawable(IRESurface* pSurface, kn_bool b_out)
{
	Initialize();
	CreateFromSurface(pSurface, b_out);
	SizeToImage();
}

void KImageDrawable::SetFillType(FillType type)
{
	m_iFillType = type;
}

KImageDrawable::~KImageDrawable(void)
{
	Release();
}


// 
void KImageDrawable::SetBorder(kn_bool bEnable, REColor color, int iStrokeWidth)
{
	m_b_border = bEnable;
	m_cl_border_color = color;
	m_i_border_width = iStrokeWidth;
}

void KImageDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX, int iDstY)
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

	//if(m_paint.HasShadow())
	//{
	//	// 
	//	REScalar radius; 
	//	REScalar  dx; 
	//	REScalar dy; 
	//	REColor  color; 
	//	kn_dword  flags;
	//	m_paint.GetBlurEffect(radius, dx, dy, color, flags);

	//	RERect rectShadow = rectDst;

	//	// dx, dy0
	//	rectDst.inset(radius * 2, radius *2);

	//	pDstSurface->ClipRect(rectShadow);
	//}
	//else
	//{
		pDstSurface->ClipRect(rectDst);
	//}

//	m_paint.SetDither(true);
//	m_paint.setAntiAlias(true);
	if(m_iFillType == FILL_NORMAL)
	{
		if(rectDst.width() != rectsrc.width() || rectDst.height() != rectsrc.height())
		{
			// 
			pDstSurface->DrawBitmapRectToRect(m_p_surface, &rectsrc, rectDst, &m_paint);

		}
		else
		{
			pDstSurface->DrawBitmap(m_p_surface, iTarX, iTarY, &m_paint);
		}
	}
	else if(m_iFillType == FILL_ALL)
	{
		// 
		pDstSurface->DrawBitmapRectToRect(m_p_surface, &rectsrc, rectDst, &m_paint);
	}
	else if(m_iFillType == FILL_NOSCALE)
	{
		// 
		pDstSurface->DrawBitmap(m_p_surface, iTarX, iTarY, &m_paint);
	}
	else if (m_iFillType == FILL_TILE)
	{
		//huw
		REBitmap Bitmap = *(m_p_surface->GetBitmap());
		REPaint paint;
		SkShader * pSkShader = SkShader::CreateBitmapShader(Bitmap ,m_xmode, m_ymode);
		paint.setShader(pSkShader)->unref();
		pDstSurface->DrawPaint(paint);

	}
	else
	{
		ASSERT(0);

	}


	// 
	if(m_b_border)
	{
		REPaint paintRect;
		paintRect.setColor(m_cl_border_color);
		paintRect.setAntiAlias(true);
		paintRect.setStyle( REPaint::kStroke_Style);
		paintRect.setStrokeWidth(m_i_border_width);

		RERect rectFrame = m_rect;
		rectFrame.offset(iDstX, iDstY);
		pDstSurface->DrawRect(rectFrame,  paintRect);
	}
	
	

	//pDstSurface->Restore();
	EndDraw(pDstSurface, pMatrix);
}



//	
TCHAR g_szPEDir[MAX_PATH] = {0};

//	
BOOL GetPEDir ()
{
	//	
	TCHAR szPEFileName [MAX_PATH] = {0};

	//	
	if (0 == GetModuleFileName (NULL, szPEFileName, MAX_PATH))
	{
		printf ("GetModuleFileName ERROR Code = %d\n", GetLastError ());
		return FALSE;
	}

	//	
	TCHAR szPEDir [MAX_PATH] = {0};
	int index = -1;

	for (int i = _tcslen (szPEFileName); i > 0; i--)
	{
		if (szPEFileName[i] == _T('\\'))
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		_tcsncpy (g_szPEDir, szPEFileName, index + 1);
		return TRUE;

	}
	else
	{
		return FALSE;
	}
}

kn_bool KImageDrawable::CreateFromFile(const kn_string& strFile)
{
	Release();

#ifdef _WIN32_WCE
	if(g_szPEDir[0] == 0)
	{
		GetPEDir();
	}

	kn_string strFullFile = g_szPEDir;
	strFullFile += strFile;

	//LOG("KImageDrawable CreateFromFile strFullFile = %S", strFullFile.c_str());

	m_p_surface = RESurfaceFactory::CreateRESurface(strFullFile);

	//LOG ("m_p_surface = %p", m_p_surface);

#else
	m_p_surface = RESurfaceFactory::CreateRESurface(strFile);
	m_b_out_resource = FALSE;
#endif
	SizeToImage();
	return (m_p_surface != NULL);
}

kn_bool KImageDrawable::CreateFromSurface(IRESurface* pSurface, kn_bool b_out )
{
	writeLock lock(m_drawable_draw_mutex); 
	if(pSurface == m_p_surface)
	{
		return true;
	}
	Release();
	m_p_surface = pSurface;
	m_b_out_resource = b_out;
	SizeToImage();
	return  (m_p_surface != NULL);
}

void KImageDrawable::Release()
{
	if (!m_b_out_resource)
	{//
		SAFE_DELETE(m_p_surface);
	}
}

bool KImageDrawable::IsNull()
{
	return m_p_surface == 0;
}

bool KImageDrawable::GetImageBound( RERect& rct )
{
	if (IsNull())
	{
		return false;
	}
	else
	{
		rct.setXYWH(0, 0, m_p_surface->GetWidth(), m_p_surface->GetHeight());
		return true;
	}
}

void KImageDrawable::SizeToImage()
{
	if (!IsNull())
	{
		if (m_rect.isEmpty())
		{
			m_rect.setXYWH(0, 0, m_p_surface->GetWidth(), m_p_surface->GetHeight());
		} 
		else
		{
			m_rect.setXYWH(m_rect.left(), m_rect.top(), m_p_surface->GetWidth(), m_p_surface->GetHeight());
		}
	}
}

void KImageDrawable::setTileModeX(SkShader::TileMode mode)
{
	m_xmode = mode;
}
void KImageDrawable::setTileModeY(SkShader::TileMode mode)
{
	m_ymode = mode;
}
void KImageDrawable::setTileModeXY(SkShader::TileMode xmode, SkShader::TileMode ymode)
{
	m_xmode = xmode;
	m_ymode = ymode;
}


/////////////////  KDBufferDrawable  //////////////////////

KDBufferDrawable::KDBufferDrawable(int w, int h)
{
	m_p_surface = RESurfaceFactory::CreateRESurface(w, h, REBitmap::kARGB_8888_Config);
	m_p_bk_surface= RESurfaceFactory::CreateRESurface(w, h, REBitmap::kARGB_8888_Config);

	m_lock_bk = FALSE;

	setRect(0,0,w,h);
}

KDBufferDrawable::~KDBufferDrawable(void)
{
	SAFE_DELETE(m_p_bk_surface);
}

//void KDBufferDrawable::Draw(IRESurface* pDstSurface, const REMatrix* pMatrix, int iDstX , int iDstY )
//{
//	readLock lock(m_draw_mutex);
//
//	KImageDrawable::Draw( pDstSurface, pMatrix, iDstX, iDstY );
//}

//buffer draw_end
IRESurface* KDBufferDrawable::drawBegin()
{
	if (m_lock_bk)
	{
		return NULL;
	}
	m_lock_bk = TRUE;
	return m_p_bk_surface;
}

//
void KDBufferDrawable::drawEnd()
{
	m_lock_bk = FALSE;
}

//buffer
void KDBufferDrawable::swapBuffer()
{
	writeLock lock(m_drawable_draw_mutex);
	IRESurface* tmp = m_p_bk_surface;

	m_p_bk_surface = m_p_surface;

	m_p_surface = tmp;

}
