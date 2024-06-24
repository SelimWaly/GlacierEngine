//  **************************************
//  File:        KImageDrawable.h
//  ***************************************
#ifndef K_IMAGE_DRAWABLE_H
#define K_IMAGE_DRAWABLE_H

#include "KDrawable.h"
#include "SkShader.h" //huw 
class API KImageDrawable : public KDrawable
{


public:
	enum FillType
	{
		FILL_NORMAL,
		FILL_ALL,
		FILL_NOSCALE,
		FILL_TILE//huw
	};
	KImageDrawable();
	KImageDrawable(const kn_string& strFile);
	KImageDrawable(IRESurface* pSurface,  kn_bool b_out = FALSE);
	void Initialize();


	virtual ~KImageDrawable(void);
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);

	kn_bool CreateFromFile(const kn_string& strFile);
	kn_bool CreateFromSurface(IRESurface* pSurface, kn_bool b_out = FALSE);
	bool GetImageBound(RERect& rct);
	bool IsNull();
	void SizeToImage(); 
	void Release();
	
	void SetFillType(FillType type);

	void SetBorder(kn_bool bEnable, REColor color = RE_ColorLTGRAY, int iStrokeWidth = 1);
	//huw
	void setTileModeX(SkShader::TileMode mode);
	void setTileModeY(SkShader::TileMode mode);
	void setTileModeXY(SkShader::TileMode xmode, SkShader::TileMode ymode);
	
	virtual kn_bool checkPoint(int x, int y);
protected:
	IRESurface* m_p_surface;
	kn_int m_iFillType;
	//
	kn_bool m_b_out_resource;

	kn_bool m_b_border;
	REColor m_cl_border_color;
	kn_int m_i_border_width;

	//huw
	SkShader::TileMode m_xmode;
	SkShader::TileMode m_ymode;

};

typedef boost::shared_ptr<KImageDrawable> KImageDrawable_PTR;


class API KDBufferDrawable: public KImageDrawable
{

public:
	KDBufferDrawable(int w, int h);
	virtual ~KDBufferDrawable(void);

	IRESurface* drawBegin();

	void drawEnd();
	void swapBuffer();

protected:
	IRESurface* m_p_bk_surface;
	kn_bool m_lock_bk;

};
typedef boost::shared_ptr<KDBufferDrawable> KDBufferDrawable_PTR;

class API KImagePartDrawable: public KImageDrawable
{

public:
	KImagePartDrawable( const kn_string& strFile, const RERect& srcRect);
	virtual ~KImagePartDrawable(void);

	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);

	void setsrcRect(const RERect& srcRect);

protected:
	RERect m_src_rect;
};
typedef boost::shared_ptr<KImagePartDrawable> KImagePartDrawable_PTR;

#endif
