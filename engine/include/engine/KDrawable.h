//  **************************************
//  File:        KDrawable.h
//  ***************************************
#ifndef K_DRAWABLE_H
#define K_DRAWABLE_H

#include "NE_pubhead.h"
#include "KObject.h"
#include "boost/shared_ptr.hpp"
#include <boost/thread/thread.hpp>

#include "renderingengine.h"
#include "RERect.h"
#include "REMatrix.h"

using namespace skia_surface;
typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost::unique_lock<boost::shared_mutex> writeLock;

enum LRMethod
{
	KVIEW_LRMethod_Parent_Left = 0,
	KVIEW_LRMethod_Parent_Right  = 1,
	KVIEW_LRMethod_Parent_LRMiddle = 2,
	KVIEW_LRMethod_Parent_LRNone = 3
};
enum BTMethod
{
	KVIEW_BTMethod_Parent_Top = 0,
	KVIEW_BTMethod_Parent_Bottom  = 1,
	KVIEW_BTMethod_Parent_BTMiddle = 2,
	KVIEW_BTMethod_Parent_BTNone = 3
};


class API KShowObject: public KObject
{
public:
	KShowObject();
	virtual ~KShowObject();
	virtual RERect GetRect();
	virtual RERect getRectOrigin();
	virtual void SetRect(const RERect& rect);
	virtual void setRect(int l, int t, int w, int h);

	virtual void sizeChange(RERect& parent_rect, RERect& parent_rect_origin);
	//clip  
	virtual RERect calcSizeChange(RERect& src,  RERect& parent_rect, RERect& parent_rect_origin);
	virtual void SetViewChangeType(IN LRMethod LeftType,IN LRMethod RightType,IN BTMethod TopType,IN BTMethod BottomType);
	virtual void SaveOriginalViewRect();
	void SetClip(RERect);
	RERect GetClip ();
	void SetClipEnable(kn_bool);
	virtual void setOpacity(kn_byte);
	kn_byte getOpacity();

	virtual kn_bool isShow();
	virtual void SetShow(kn_bool bShow);


protected:
	RERect m_rect;				// view, 
	// view
	kn_bool m_b_clip;
	RERect m_rect_clip;
	kn_bool m_b_show;

	//
	LRMethod m_LRMethod_left;
	LRMethod m_LRMethod_right;
	BTMethod m_BTMethod_top;
	BTMethod m_BTMethod_bottom;
	RERect m_rect_origin;
	RERect m_rect_clip_origin;

	kn_byte  m_i_opacity;

};

class API KDrawable : public KShowObject
{

public:

	enum KDRAWABLETYPE
	{
		KDRAWABLE_BASE = 0,
		KDRAWABLE_COLOR = 1,
		KDRAWABLE_TEXT = 2,
		KDRAWABLE_IMAGE = 3,
		KDRAWABLE_SHAPE = 4,
		KDRAWABLE_9PATCH_IMAGE = 5,
		KDRAWABLE_TEXTMULTILINE = 6,
		KDRAWABLE_TEXTBITMAP = 7,
	};
protected:

	REPaint m_paint;

	// m_rect
	kn_bool m_b_clip_rect;
	//drawable

	KDRAWABLETYPE m_type;

	//view
	kn_bool m_b_auto_size;

	//drawable
	boost::shared_mutex m_drawable_draw_mutex; 
public:

	KDrawable();

	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	///BeginDraw EndDrawdrawable draw draw
	virtual bool BeginDraw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);
	virtual void EndDraw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0);

	virtual REPaint* GetPaint();
	virtual void SetPaint(REPaint* pPaint);
	virtual void SetViewChangeType(IN LRMethod LeftType,IN LRMethod RightType,IN BTMethod TopType,IN BTMethod BottomType);

	virtual ~KDrawable();
	void CreateFromResource();
	KDRAWABLETYPE getType();

	//drawable
	virtual kn_bool checkPoint(int x, int y);

	kn_bool getAutoSize();
	void setAutoSize(kn_bool bShow);
};

typedef boost::shared_ptr<KDrawable> KDrawable_PTR;
typedef vector<KDrawable_PTR> VEC_DRAWABLE;

#endif
