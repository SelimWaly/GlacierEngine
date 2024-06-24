//  **************************************
//  File:        KShapeDrawable.h
//  ***************************************
#ifndef K_SHAPE_DRAWABLE_H
#define K_SHAPE_DRAWABLE_H


#include "KDrawable.h"
class KSvgAnalyzing;
enum PATHTYPE
{
	PATH_ABS_MOVETO = 0,    //absolute moveto
	PATH_ABS_LINETO,        //absolute lineto
	PATH_ABS_H_LINETO,      //absolute horizontal lineto
	PATH_ABS_V_LINETO,	    //absolute vertical lineto
	PATH_ABS_CURVETO,       //absolute curveto
	PATH_ABS_S_CURVETO,     //absolute smooth curveto
	PATH_ABS_Q_CURVE,       //absolute quadratic Belzier curve
	PATH_ABS_T_CURVETO,      //absolute smooth quadratic Belzier curveto
	PATH_ABS_ARC,			//absolute elliptical Arc
	PATH_REL_MOVETO,        //relative moveto
	PATH_REL_LINETO,        //relative lineto
	PATH_REL_H_LINETO,      //relative horizontal lineto
	PATH_REL_V_LINETO,	    //relative vertical lineto
	PATH_REL_CURVETO,       //relative curveto
	PATH_REL_S_CURVETO,     //relative smooth curveto
	PATH_REL_Q_CURVE,       //relative quadratic Belzier curve
	PATH_REL_T_CURVETO,      //relative smooth quadratic Belzier curveto
	PATH_REL_ARC,			//relative elliptical Arc
	PATH_CLOSEPATH			//relative closepath
};
//
enum SHAPETYPE
{
	SHAPE_RECT = 0,
	SHAPE_CIRCLE,
	SHAPE_ELLIPSE,
	SHAPE_LINE,
	SHAPE_POLYGON,
	SHAPE_PATH
};
//path
struct PathData
{
	PATHTYPE pathType;
	vector<float> PathUnitDataList;

};
class API KShape : public KObject
{
protected:
	REColor m_fill_clr; //
	float m_fillOpacity; //
	REColor m_stroke_clr;//
	int m_stroke_width;//
	int m_stroke_miterlimit;
	float m_strokeOpacity;//
	float m_opacity;//
	bool m_bfill;
	bool m_bstroke;
	SHAPETYPE m_shapeType;
	RERect m_rect;
public:
	REPaint m_fillPaint;
	REPaint m_strokePaint;
	KShape();
	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint) = 0;
	void setFillColor(REColor& fill);
	void setFillOpacity(float fillOpacity);
	float getFillOpacity();
	void setStrokeColor(REColor& stroke);
	void setStrokeWidth(int strokeWidth);
	void setStrokeMiterlimit(int miterlimit);
	void setStrokeOpacity(float opacity);
	float getStrokeOpacity();
	void setShapeType(SHAPETYPE type);
	SHAPETYPE getShapeType();
	void setOpacity(float opacity);
	bool getFillShowFlag();
	bool getStrokeShowFlag();
	void initPaint();
	void setRect(RERect& rect);
	void setRect(int x, int y, int w, int h);
};


class API KRectShape : public KShape
{	
protected:


public:
	KRectShape();
	KRectShape(RERect rect);

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);

};
//
class API KOvalShape : public KRectShape
{
public:
	KOvalShape();
	KOvalShape(RERect rect);

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);
};

//
class API KArcShape : public KRectShape
{
protected:
	int m_start_angle;
	int m_sweep_angle;

public:
	KArcShape();
	KArcShape(RERect rect);

	void setStartAngle(int );
	void setSweepAngle(int );

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);



};

//
class API KRoundRectShape : public KRectShape
{
protected:
	float m_rx;	// x
	float m_ry;	//y

public: 
	KRoundRectShape(){};
	KRoundRectShape(RERect rect, float rx, float ry): KRectShape(rect) 
	{
		m_rx = rx;
		m_ry = ry;
	}

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);
	void SetRX(float rx);
	void SetRY(float ry);
};
//
class API KCircleShape : public KShape
{
protected:
	float m_cx;    //x
	float m_cy;	//y
	float m_r;	//


public: 
	KCircleShape();
	KCircleShape(int cx, int cy,int r) ;
	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);
	void SetCX(float cx);
	void SetCY(float cy);
	void SetCR(float cr);
};
//
class API KLineShape : public KShape
{
protected:
	REPoint m_p1;
	REPoint m_p2;

public: 
	KLineShape();
	KLineShape(REPoint p1, REPoint p2);

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);
	void SetStartPoint(REPoint p1);
	void SetEndPoint(REPoint p2);
};
//
class API KPolygonShape : public KShape
{
protected:

	REPoint* m_p_points;
	int m_i_points_count;
	kn_bool m_b_close;

public:
	KPolygonShape();
	KPolygonShape(REPoint* pPoints, int count, kn_bool bClose) ;

	~KPolygonShape();

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);
	void SetPoints(vector<REPoint>& pointList);
	void SetCloseFlag(bool bClose);
	void Release();
	
};
//
class API KPathShape : public KShape
{
protected:

	REPath m_path;

public:
	KPathShape(){};
	KPathShape(REPath& path);

	~KPathShape();


	void Release();

	virtual void Draw(IRESurface* pDstSurface, const REPaint& paint);

	REPath* GetPath();
	
	void SetPath(REPath& path);
};

class API KShapeDrawable : public KDrawable
{
protected:
	KShape* m_p_shape;

public :
	KShapeDrawable();
	KShapeDrawable(KShape* pShape);
	virtual ~KShapeDrawable();
	virtual void SetRect(const RERect& rect);
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	void Release();
	void setShape(KShape* pShape);
	KShape* getShape();
	
};
typedef boost::shared_ptr<KShapeDrawable> KShapeDrawable_PTR;

class API KSVGDrawable : public KDrawable
{
protected:
	vector<KShapeDrawable_PTR> m_vec_shape_drawables;
	vector<KShape*> m_pShapeList;
protected:

	void addShape(KShape* pShape, REPaint* pPaint);

public:

	KSVGDrawable();
	KSVGDrawable(kn_string svgFilePath);
	KSVGDrawable(kn_string svgFilePath, RERect& rect);

	virtual ~KSVGDrawable();
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	void Release();

	void addLine(REPoint p1, REPoint p2, REPaint* pPaint);
	void addPolygon(REPoint* pPoints, int count,  kn_bool bClose, REPaint* pPaint);
	void addPath(REPath& path, REPaint* pPaint);
	void addLine(KShape* pShape, REPaint* pPaint);

	// addPolygon,addPath,addRoundRect,addCircle,addEllipse
	void addSVGShape(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);

	void addPolygon(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);
	void addPath(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);
	void addRoundRect(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);
	void addCircle(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);
	void addEllipse(KShape* pShape, REPaint* pFillPaint,REPaint* pStorkPaint);


protected:
	void CreateOfSvg(RERect& rect);

};

typedef boost::shared_ptr<KSVGDrawable> KSVGDrawable_PTR;
void MyTraceA(const char* szFormat, ... );
#endif
