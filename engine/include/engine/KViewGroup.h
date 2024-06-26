﻿//  **************************************
//  File:        KViewGroup.h
//  ***************************************
#ifndef K_PAGE_VIEW_H
#define K_PAGE_VIEW_H

#include "KView.h"
#include "KDrawable.h"
//#include "KButtonView.h"
//#include "KEditView.h"
#include <boost/thread/thread.hpp>
#include "KTextView.h"
#include "KButtonView.h"
#include "KEditView.h"


#define ICON_SENTER 2000

class KTextView;
class KStaticView;
class KEditView;
class KImgButtonView;

//class API KViewGroup : public KObject
class API KViewGroup : public KView
{
protected:
	boost::shared_mutex m_lst_view_mutex;
	LSTVIEW m_lst_view;
	IRESurface* m_pSurface;

	LSTVIEW m_del_lst_view; //viewview

	kn_bool m_b_do_clip_msg;//Clip

	//viewSizeChangeviewviewSizeChangegrid listviewSizeChange
	kn_bool m_b_change_child_size;

public:
	KViewGroup();
	virtual ~KViewGroup();
	virtual void Release();

	virtual void Draw(IRESurface* pDstSurface, kn_int x, kn_int y);
	virtual void Draw(IRESurface* pDstSurface, LSTRECT& lst_rect, kn_int x, kn_int y);

	virtual void AddView(KView_PTR v);
	virtual void AddViewToDel(KView_PTR v);

	virtual void SaveOriginalViewRect();

	//
	virtual void SleepPage();
	virtual void Wakeup();

	virtual LSTRECT GetInvalidRect();
	kn_bool DoMessage(KMessage* pMsg);

	//
//	virtual kn_bool isRef();

	//view
	kn_int findViewIndex(KView_PTR v);
	void swapViewLayer(KView_PTR v1, KView_PTR v2);
	void changeViewLayerTop(KView_PTR v);
	void changeViewLayerBottom(KView_PTR v);
	void changeViewLayerUp(KView_PTR v);
	void changeViewLayerDown(KView_PTR v);
	void moveViewLayer(kn_int old_index, kn_int new_index);

	virtual void eraseView(KView_PTR v);

	KView_PTR getViewByIndex(kn_int index);
	kn_int getViewCount();

	virtual void viewSizeChange();
	virtual void resize(RERect);
	RERect getDrawRectBaseOnChild();
	
	//view, 
	void createImgViewHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath, const kn_string& focusPath,kn_int x,kn_int y);
	void createImgView9PatchHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath, const kn_string& focusPath,kn_int x,kn_int y, kn_int w, kn_int h);
	// icon_x = ICON_SENTER 
	void createImgView9PatchIconHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath, const kn_string& focusPath,const kn_string& iconPath, kn_int x,kn_int y, kn_int w, kn_int h, kn_int icon_x, kn_int icon_y);
	
	//
	void createTextViewHelper(KTextView_PTR* view,const kn_string& imgPath,kn_int x,kn_int y,  kn_int w=100, kn_int h=50);

	void createImageHelper(KStaticView_PTR* view,const kn_string& path, kn_int x,kn_int y);
	void createTextHelper(KStaticView_PTR* view,const kn_string& txt, int fontsize, kn_int x,kn_int y, kn_int w, kn_int h);
	void createEditViewHelper(KEditView_PTR* view, int fontsize, kn_int x,kn_int y, kn_int w, kn_int h);
	void EnableClipMessage(kn_bool b);
};

typedef boost::shared_ptr<KViewGroup> KViewGroup_PTR;
//group 
typedef boost::weak_ptr<KViewGroup> KViewGroup_WEAK_PTR;
#endif
