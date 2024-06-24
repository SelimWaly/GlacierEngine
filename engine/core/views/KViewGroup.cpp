//  **************************************
//  File:        KViewGroup.cpp
//  ***************************************
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "DataSync.h"
#include "KViewGroup.h"
#include "KScreen.h"
#include "KSurfaceManager.h"
#include "K9PatchImageDrawable.h"
#include "KEditView.h"
#include "KButtonView.h"

KViewGroup::KViewGroup()
{
	m_pSurface = NULL;
	m_b_do_clip_msg = false;
	m_b_change_child_size = TRUE;
	m_e_viewtype = KVIEW_GROUP;

	//groupview
	SetShieldMsg(FALSE);
}
 
KViewGroup::~KViewGroup()
{
	Release();
}

void KViewGroup::Release()
{
	SAFE_DELETE(m_pSurface);
	writeLock lock(m_lst_view_mutex);
	m_lst_view.clear();
}

//kn_bool  KViewGroup::isRef()
//{
//	if (KView::isRef())
//	{
//		return TRUE;
//	}
//	BOOL ref = FALSE;
//	for(LSTVIEW::iterator it = m_lst_view.begin(); it != m_lst_view.end(); it++)
//	{
//		if ( (*it)->isRef() )
//		{//view
//			ref = TRUE;
//			break;
//		}
//	}
//
//	return ref;
//}

//
void KViewGroup::SleepPage()
{
	SetShow(FALSE);
	enableMessage(FALSE);
}

//
void KViewGroup::Wakeup()
{
	SetShow(TRUE);
	enableMessage(TRUE);
}

//
void KViewGroup::Draw(IRESurface*  pDstSurface, kn_int x, kn_int y)
{
	KView::Draw(pDstSurface,x,y);

	if (m_transform_flag != 0)
	{
		pDstSurface->Save();
		REMatrix tempMatrix;
		getMatrix(x, y, tempMatrix);
		pDstSurface->Concat(tempMatrix);
	}
 
 	// groupview
	int screenx, screeny;
	GetScreenXY(screenx, screeny);
	KScreen* pScreen = GetScreen(); 
	RERect  rectScreen;
	if (!pScreen)
	{//screen
		rectScreen = RERect::MakeXYWH(-screenx, -screeny, m_rect.width(), m_rect.width());
	}
	else
	{
		rectScreen = RERect::MakeXYWH(-screenx, -screeny, pScreen->GetWidth(), pScreen->GetHeight());
	}

	// ViewPageView
	readLock lock(m_lst_view_mutex);

	KView_PTR pView;

	// groupview 
	if(m_b_clip)
	{
		pDstSurface->Save();
		pDstSurface->ClipRect(GetScreenRect(m_rect_clip) );
	}



	// debugsize vector
	int iArraySize = m_lst_view.size();
	for(int i = 0; i < iArraySize; i++)
	{
		pView = m_lst_view[i];
 
		// view
		if(pView->isShow() && RERect::Intersects(rectScreen, pView->getDrawRectBaseOnChild()))
		{
			//
			int i_ds_alpha = pView->getOpacity();
			int i_alpha =  i_ds_alpha * m_i_opacity  / 255; //(255*255)
			pView->setOpacity(i_alpha);

			pView->Draw(pDstSurface, m_rect.left()+x, m_rect.top()+y );//rect.left(), rect.top());

			pView->setOpacity(i_ds_alpha);
		}

	}

	if(m_b_clip)
	{
		pDstSurface->Restore();
	}


 
	lock.unlock();


	if (m_transform_flag != 0)
	{
		pDstSurface->Restore();
	}

}
 

// 
void KViewGroup::Draw(IRESurface* pDstSurface, LSTRECT& lst_rect, kn_int x, kn_int y)
{
	if (m_transform_flag != 0)
	{
		pDstSurface->Save();
		REMatrix tempMatrix;
		getMatrix(x, y, tempMatrix);
		pDstSurface->Concat(tempMatrix);
	}
	RERect  rect = m_rect;
	rect.offset(x,y);
	readLock lock(m_lst_view_mutex);
	for(LSTVIEW::iterator it = m_lst_view.begin(); it != m_lst_view.end(); it++)
	{
		if ( (*it)->isShow())
		{
			(*it)->Draw(pDstSurface, lst_rect,rect.left(), rect.top() );
		}

	}
	if (m_transform_flag != 0)
	{
		pDstSurface->Restore();
	}
	clearInvalidRect();
}

LSTRECT KViewGroup::GetInvalidRect()
{
	readLock lock(m_lst_view_mutex);
	for(LSTVIEW::iterator it = m_lst_view.begin(); it != m_lst_view.end(); it++)
	{
		KView_PTR pView = *it;
		LSTRECT lr = pView->GetInvalidRect( );
		m_lst_rect_invalid.insert(m_lst_rect_invalid.end(), lr.begin(),lr.end());
		//for(LSTRECT::iterator ite = lr.begin();ite!=lr.end();ite++)
		//{
		//	m_lst_rect_invalid.push_back((*ite));
		//}
	}

	return m_lst_rect_invalid;
}

kn_bool KViewGroup::DoMessage(KMessage* pMsg)
{
	kn_bool ret = false;
	kn_bool ret2 = false;
	kn_bool ret_focus = false;

	RERect rectBound = GetBoundRect();

// wince debug 
#ifndef _WIN32_WCE
 	if ((!m_b_do_msg) || (!m_b_show))
 	{
 		return false;
 	}

#endif

	ret = KView::DoMessage(pMsg);

	if (m_b_do_clip_msg  && pMsg->HasPos() && 
		!isPointInView(((KMessagePos*)pMsg)->m_pos_x,((KMessagePos*)pMsg)->m_pos_y))
	{//ViewgroupViewgroup   zhic 2014.12.29
		return false;
	}

	//
	if (pMsg->HasPos())
	{
		((KMessagePos*)pMsg)->m_pos_x -= rectBound.left();
		((KMessagePos*)pMsg)->m_pos_y -= rectBound.top();
	}

	//
	KView_PTR p_focus = GetScreen()->getTempFocusView();//,

	// 
	{
		LSTVIEW lst_view = m_lst_view; //
		for(LSTVIEW::reverse_iterator  it = lst_view.rbegin(); it != lst_view.rend(); it++)
		{
			if ( (*it) == p_focus )
			{	//, screen
				//,
				continue;
			}

			//ret2
			pMsg->setIdle(KMSG_RETURN_DEFAULT);
			ret2 = (*it)->DoMessage(pMsg);
			if(ret2 && pMsg->HasPos() && pMsg->getIdle() != KMSG_RETURN_CONTINUE)	//continue
			{//,
				// 1ViewmousemoveViewView?.
				break;
			}

			if(pMsg->getIdle() == KMSG_RETURN_DILE)
			{//,
				break;;
			}

		}
	}

	//
	if (pMsg->HasPos())
	{	
		((KMessagePos*)pMsg)->m_pos_x += rectBound.left();
		((KMessagePos*)pMsg)->m_pos_y += rectBound.top();
	}

	//view
	for(LSTVIEW::reverse_iterator  it = m_del_lst_view.rbegin(); it != m_del_lst_view.rend(); it++)
	{
		eraseView( *it);
	}


	if (m_del_lst_view.size() > 0)
	{
		InvalidateView();
		m_del_lst_view.clear();
	}

	return ret || ret2 ;

}

void KViewGroup::AddView(KView_PTR v)
{
	if (v)
	{
		v->SetParent( VIEW_PTR(KViewGroup)( shared_from_this() ) );
		writeLock lock(m_lst_view_mutex);
		m_lst_view.push_back(v);
	}
}

void KViewGroup::AddViewToDel(KView_PTR v)
{
	if (v)
	{
		eraseView(v);
		//m_del_lst_view.push_back(v);
	}
}

//view
kn_int KViewGroup::findViewIndex(KView_PTR v)
{
	readLock lock(m_lst_view_mutex);
	LSTVIEW::iterator it = find( m_lst_view.begin(), m_lst_view.end(), v );
	if (it == m_lst_view.end())
	{
		return -1;
	}
	return distance(m_lst_view.begin(),it);
}

KView_PTR KViewGroup::getViewByIndex(kn_int index)
{
	readLock lock(m_lst_view_mutex);
	if(index < m_lst_view.size())
	{
		return m_lst_view[index];
	}

	KView_PTR p;
	return p;

}

kn_int KViewGroup::getViewCount()
{
	readLock lock(m_lst_view_mutex);
	return m_lst_view.size();
}


void KViewGroup::swapViewLayer(KView_PTR v1, KView_PTR v2)
{
	readLock rlock(m_lst_view_mutex);
	LSTVIEW::iterator it1 = find( m_lst_view.begin(), m_lst_view.end(), v1 );
	LSTVIEW::iterator it2 = find( m_lst_view.begin(), m_lst_view.end(), v2 );
	if (it1 == m_lst_view.end() || it2 == m_lst_view.end() )
	{
		return ;
	}
	rlock.unlock();

	writeLock wlock(m_lst_view_mutex);
	KView_PTR tmp = (*it1);
	(*it1) = (*it2);
	(*it2) = tmp;
}

//
void KViewGroup::changeViewLayerTop(KView_PTR v)
{
	kn_int count = m_lst_view.size();
	if (count > 1 )
	{
		//swap(it1,m_lst_view.end()-1 );
		kn_int n = findViewIndex(v);
		if (n >= 0 && n < count-1)
		{
			writeLock lock(m_lst_view_mutex);
			KView_PTR tmp = m_lst_view[n];
			m_lst_view.erase( m_lst_view.begin()+n );
			m_lst_view.push_back(tmp);
		}
	}
}

void KViewGroup::changeViewLayerBottom(KView_PTR v)
{
	kn_int count = m_lst_view.size();
	if (count > 1 )
	{
		//swap(it1,m_lst_view.end()-1 );
		kn_int n = findViewIndex(v);
		//if (n >= 0 && n < count-1)
		if (n > 0 && n <= count-1)
		{
			writeLock lock(m_lst_view_mutex);
			KView_PTR tmp = m_lst_view[n];
			m_lst_view.erase( m_lst_view.begin()+n );
			m_lst_view.insert(m_lst_view.begin(), tmp);
		}
	}
}

//
void KViewGroup::changeViewLayerUp(KView_PTR v)
{
	kn_int count = m_lst_view.size();
	if (count > 1 )
	{
		//swap(it1,m_lst_view.end()-1 );
		kn_int n = findViewIndex(v);
		//if (n > 0 && n <= count-1)
		if (n >= 0 && n < count-1)
		{
			writeLock lock(m_lst_view_mutex);
			KView_PTR tmp = m_lst_view[n+1];
			m_lst_view[n+1] = m_lst_view[n];
			m_lst_view[n] = tmp;	
		}
	}
}

//
void KViewGroup::changeViewLayerDown(KView_PTR v)
{
	kn_int count = m_lst_view.size();
	if (count > 1 )
	{
		//swap(it1,m_lst_view.end()-1 );
		kn_int n = findViewIndex(v);
		if (n > 0 )
		{
			writeLock lock(m_lst_view_mutex);
			KView_PTR tmp = m_lst_view[n-1];
			m_lst_view[n-1] = m_lst_view[n];
			m_lst_view[n] = tmp;	
		}
	}
}

void KViewGroup::moveViewLayer( kn_int old_index, kn_int new_index )
{
	

}

void KViewGroup::eraseView(KView_PTR v)
{
	kn_int count = m_lst_view.size();
	if (count > 0 )
	{
		//swap(it1,m_lst_view.end()-1 );
		kn_int n = findViewIndex(v);
		if (n >= 0)
		{
			//MyTrace(_T("wait lock"));
			writeLock lock(m_lst_view_mutex);
			//KView_PTR tmp = m_lst_view[n];
			m_lst_view.erase( m_lst_view.begin()+n );
			//delete tmp;
			//MyTrace(_T("m_lst_view.erase"));
		}
	}
}

void KViewGroup::viewSizeChange()
{
	KView::viewSizeChange();

	if (m_b_change_child_size)
	{
		for (kn_int i = 0;i < m_lst_view.size();i ++)
		{
			m_lst_view[i]->viewSizeChange();
		}	
	}

}

void KViewGroup::SaveOriginalViewRect()
{
	KView::SaveOriginalViewRect();

	for (kn_int i = 0;i < m_lst_view.size();i ++)
	{
		m_lst_view[i]->SaveOriginalViewRect();
	}	

}

void KViewGroup::resize(RERect dst_rect)
{
	SaveOriginalViewRect();

	SetRect(dst_rect);

	for (kn_int i = 0;i < m_lst_view.size();i ++)
	{
		m_lst_view[i]->viewSizeChange();
	}	
}


void KViewGroup::createTextViewHelper( KTextView_PTR* view,const kn_string& imgPath,kn_int x ,kn_int y, kn_int w, kn_int h)
{
	IRESurface* imgSurface =  getSurfaceManager()->GetSurface(imgPath.c_str());

	//zhic 
	//if (!imgSurface)
	//{ 
	//	return;
	//}

	*view = KTextView_PTR(new KTextView);
	
	RERect rect = RERect::MakeXYWH(x, y, w, h);
	if (imgSurface)
	{
		rect = RERect::MakeXYWH(x,y ,imgSurface->GetWidth(), imgSurface->GetHeight());
		(*view)->Create(rect);

		if( imgPath.find(_T(".9.") ) == kn_string::npos )
		{//9
			KImageDrawable_PTR drawable = KImageDrawable_PTR(new KImageDrawable(imgSurface,true));
			(*view)->setBKDrawable(drawable);
		}
		else
		{
			K9PatchImageDrawable_PTR drawable = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(imgSurface,true));
			(*view)->setBKDrawable(drawable);

		}
	}
	else
	{
		(*view)->Create(rect);
	}

	AddView(*view);
}


void KViewGroup::createImgViewHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath
	,const kn_string& focusPath,kn_int x ,kn_int y )
{

	IRESurface* surNormal =  getSurfaceManager()->GetSurface(normalPath.c_str());
	IRESurface* surActive =  getSurfaceManager()->GetSurface(activePath.c_str());
	IRESurface* surFocus =  getSurfaceManager()->GetSurface(focusPath.c_str());
	if (!surNormal || !surActive || !surFocus)
	{
		return;
	}

	*view = KImgButtonView_PTR(new KImgButtonView);

    RERect rect = RERect::MakeXYWH(x,y ,surNormal->GetWidth(), surNormal->GetHeight());
    (*view)->Create(rect);

	KDrawable_PTR normal = KImageDrawable_PTR(new KImageDrawable(surNormal,true));
	KDrawable_PTR focus = KImageDrawable_PTR(new KImageDrawable(surFocus,true));
	KDrawable_PTR selected = KImageDrawable_PTR(new KImageDrawable(surActive,true));
	KDrawable_PTR disable = KImageDrawable_PTR(new KImageDrawable(surNormal,true));
	(*view)->setBKG(normal,focus,selected,disable);
	AddView(*view);
}

void KViewGroup::createImgView9PatchHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath,
	const kn_string& focusPath,kn_int x ,kn_int y , kn_int w ,kn_int h )
{

	IRESurface* surNormal =  getSurfaceManager()->GetSurface(normalPath.c_str());
	IRESurface* surActive =  getSurfaceManager()->GetSurface(activePath.c_str());
	IRESurface* surFocus =  getSurfaceManager()->GetSurface(focusPath.c_str());
	if (!surNormal || !surActive || !surFocus)
	{
		return;
	}

	*view = KImgButtonView_PTR(new KImgButtonView);

    RERect rect = RERect::MakeXYWH(x,y ,w, h);
    (*view)->Create(rect);

	K9PatchImageDrawable_PTR normal = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surNormal,true));		normal->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR focus = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surFocus,true));		focus->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR selected = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surActive,true));	selected->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR disable = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surNormal,true));	disable->setRect(0,0,w, h);
	(*view)->setBKG(normal,focus,selected,disable);
	AddView(*view);
}


void KViewGroup::createImgView9PatchIconHelper(KImgButtonView_PTR* view,const kn_string& normalPath,const kn_string& activePath, const kn_string& focusPath,const kn_string& iconPath, kn_int x,kn_int y, kn_int w, kn_int h, kn_int icon_x, kn_int icon_y)
{

	IRESurface* surNormal =  getSurfaceManager()->GetSurface(normalPath.c_str());
	IRESurface* surActive =  getSurfaceManager()->GetSurface(activePath.c_str());
	IRESurface* surFocus =  getSurfaceManager()->GetSurface(focusPath.c_str());
	if (!surNormal || !surActive || !surFocus)
	{
		return;
	}

	*view = KImgButtonView_PTR(new KImgButtonView);
    RERect rect = RERect::MakeXYWH(x,y ,w, h);
    (*view)->Create(rect);

	K9PatchImageDrawable_PTR normal = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surNormal,true));		normal->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR focus = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surFocus,true));		focus->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR selected = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surActive,true));	selected->setRect(0,0 ,w, h);
	K9PatchImageDrawable_PTR disable = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surNormal,true));	disable->setRect(0,0,w, h);
	(*view)->setIconImage(iconPath);
	;
	if (icon_x == ICON_SENTER)
	{
		(*view)->setIconCenter();
	}
	else
	{
		(*view)->setIconPos(icon_x,icon_y);
	}
	(*view)->setBKG(normal,focus,selected,disable);
	AddView(*view);
}

void KViewGroup::createImageHelper(KStaticView_PTR* view,const kn_string& normalPath, kn_int x,kn_int y)
{
	IRESurface* surNormal =  getSurfaceManager()->GetSurface(normalPath.c_str());
	if (!surNormal )
	{
		return;
	}

	*view = KStaticView_PTR(new KStaticView);

    RERect rect = RERect::MakeXYWH(x,y ,surNormal->GetWidth(), surNormal->GetHeight());
    (*view)->Create(rect);

	if( normalPath.find(_T(".9.") ) == kn_string::npos )
	{//9
		KImageDrawable_PTR drawable = KImageDrawable_PTR(new KImageDrawable(surNormal,true));
		(*view)->setBKDrawable(drawable);
	}
	else
	{
		K9PatchImageDrawable_PTR drawable = K9PatchImageDrawable_PTR(new K9PatchImageDrawable(surNormal,true));
		(*view)->setBKDrawable(drawable);

	}

	AddView(*view);
}

void KViewGroup::createTextHelper(KStaticView_PTR* view,const kn_string& txt, int fontsize, kn_int x,kn_int y, kn_int w, kn_int h)
{
	*view = KStaticView_PTR(new KStaticView);

    RERect rect = RERect::MakeXYWH(x,y ,w, h);
    (*view)->Create(rect);
	(*view)->SetText(txt);
	(*view)->SetTextColor(RE_ColorWHITE);
	(*view)->SetFontSize(fontsize);
	(*view)->enableMessage(false);
	AddView(*view);
}

void KViewGroup::createEditViewHelper(KEditView_PTR* view, int fontsize, kn_int x,kn_int y, kn_int w, kn_int h)
{
	*view = KEditView_PTR(new KEditView);
    RERect rect = RERect::MakeXYWH(x,y ,w, h);
    (*view)->Create(rect);
	(*view)->Init(10,7,RE_ColorYELLOW);
	(*view)->KStaticView::SetTextColor(RE_ColorWHITE);
	(*view)->SetFontSize(fontsize);
	AddView(*view);
}
void KViewGroup::EnableClipMessage(kn_bool b)
{
	m_b_do_clip_msg = b;
}

RERect KViewGroup::getDrawRectBaseOnChild()
{
	if (!isShow())
	{
		return RERect::MakeXYWH(0, 0, 0, 0);
	}
	RERect child_join_rect = RERect::MakeXYWH(0, 0, m_rect.width(), m_rect.height() );
    // m_lst_view add by weix 2015-12-2
    readLock rlock(m_lst_view_mutex);
	for (kn_int i = 0; i < m_lst_view.size(); ++i)
	{
		//{fLeft=-1.0737418e+008 fTop=-1.0737418e+008 fRight=-1.0737418e+008 ...}
		child_join_rect.join(m_lst_view[i]->getDrawRectBaseOnChild());	
	}
	rlock.unlock();
	// m_lst_drawable add by junz 2015-12-26
	readLock lock(m_lst_drawable_mutex);
	for(kn_int i = 0; i < m_lst_drawable.size(); ++i)
	{
		child_join_rect.join(m_lst_drawable[i]->GetRect());
	}
	lock.unlock();
	RERect draw_rect = RERect::MakeXYWH(child_join_rect.left() + m_rect.left(), child_join_rect.top() + m_rect.top(), child_join_rect.width(), child_join_rect.height());
	return draw_rect;
}
