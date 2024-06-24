﻿//  **************************************
//  File:        KTextView.cpp
//  ***************************************
#include "KTextView.h"
#include "DataSync.h"
#include "mainforwindows.h"
#include "KFontManager.h"

KStaticView::KStaticView()
{
	m_e_viewtype = KVIEW_STATIC;
	//drawable
	m_text_drawable = KTextDrawable_PTR (new KTextDrawable(_T(""), RE_ColorBLACK, 16, REPaint::kLeft_Align) );
	//m_text_drawable->setFontName("Microsoft YaHei");
	m_text_drawable->setFont(GetFontManagerSingleton()->GetFontFromName("Microsoft YaHei"));
	
	m_text_drawable->SetRect(RERect::MakeXYWH(5, 5, 100, 100) );
	m_bk_drawable = KColorDrawable_PTR(new KColorDrawable(RE_ColorBLACK) );
	m_icon_drawable = KImageDrawable_PTR(new KImageDrawable);
	//Static 
	m_b_do_msg = FALSE;

	m_b_check_alpha = FALSE;

	//
	addDrawable(m_bk_drawable);
	addDrawable(m_icon_drawable);
	addDrawable(m_text_drawable);
	//
	for(VEC_DRAWABLE::iterator ite = m_lst_drawable.begin();ite!=m_lst_drawable.end();ite++)
	{
		KDrawable_PTR p = (*ite);
		p->SetShow(FALSE);
	}
}

KStaticView::~KStaticView()
{
}

kn_bool KStaticView::Create(kn_int iX, kn_int iY, kn_int iWidth, kn_int iHeight)
{
	KView::Create(iX, iY, iWidth, iHeight);

	m_text_drawable->SetRect(RERect::MakeXYWH(0, 0, iWidth, iHeight) );
	m_bk_drawable->SetRect(RERect::MakeXYWH(0, 0, iWidth, iHeight) );
	return true;
}

kn_bool KStaticView::Create(const RERect& rect)
{
	return Create(rect.left(), rect.top(), rect.width(), rect.height());
}

void KStaticView::setIconPos(kn_int x, kn_int y)
{
	RERect rect;
	kn_bool ret = m_icon_drawable->GetImageBound(rect);
	if (ret)
	{
		//drawable(drawable drawable),
		writeLock lock(m_lst_drawable_mutex);
		m_icon_drawable->SetRect(RERect::MakeXYWH(x, y, rect.width(), rect.height()) );
	}
}

void KStaticView::setIconCenter()
{
	RERect rect;
	kn_bool ret = m_icon_drawable->GetImageBound(rect);
	if (ret)
	{
		//drawable(drawable drawable),
		writeLock lock(m_lst_drawable_mutex);
		kn_int iX = SkScalarHalf(m_rect.width() - rect.width());
		kn_int iY = SkScalarHalf(m_rect.height() - rect.height());
		m_icon_drawable->SetRect(RERect::MakeXYWH(iX, iY, rect.width(), rect.height()) );
	}
}

KDrawable_PTR KStaticView::getBKDrawable()
{
	return m_bk_drawable;
}
KDrawable_PTR KStaticView::getIconDrawable()
{
	return m_icon_drawable;
}

KDrawable_PTR KStaticView::getTextDrawable()
{
	return m_text_drawable;
}

void KStaticView::setOutBoundDot()
{
	m_text_drawable->setOutBoundDot();
}

void KStaticView::setTextMargin(kn_int w, kn_int h)
{
	//drawable(drawable drawable)
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetRect(RERect::MakeXYWH(w, w, 100-h, 100-h) );
}

void KStaticView::showBK(kn_bool b)
{
	//drawable
	writeLock lock(m_lst_drawable_mutex);
	m_bk_drawable->SetShow(b);
}

void KStaticView::showIcon(kn_bool b)
{
	//drawable
	writeLock lock(m_lst_drawable_mutex);
	m_icon_drawable->SetShow(b);
}
void KStaticView::showText(kn_bool b)
{
	//drawable,
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetShow(b);
}

void KStaticView::SetText( kn_string text )
{
	// 
	showText(TRUE);
	writeLock lock(m_lst_drawable_mutex);
//	m_text_drawable->setFontName((""));
	m_text_drawable->SetText(text.c_str());
}

void KStaticView::SetRect(const RERect& rect)
{
	KView::SetRect(rect);
	//
	m_bk_drawable->SetRect(RERect::MakeXYWH( 0,0,rect.width(), rect.height() ) );
}

kn_string KStaticView::getText()
{

	return m_text_drawable->GetText();
}

SkTypeface* KStaticView::GetFont()
{
	return m_text_drawable->GetFont();
}

void KStaticView::SetFont( SkTypeface* pTypeFace )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setFont(pTypeFace);
}

void KStaticView::SetTextColor( REColor color )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setColor(color);
}

void KStaticView::SetFontSize( kn_int iFontSize )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetFontSize(iFontSize);
}

void KStaticView::SetFontBold(kn_bool bBold)
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setBold(bBold);
}
void KStaticView::setTextAlign( REPaint::Align align )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setTextAlign(align);

	if (align == REPaint::kLeft_Align)
	{
		m_text_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Left, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Top);
	}
	else if (align == REPaint::kCenter_Align)
	{
		m_text_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Right, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Top);
	}
	else if (align == REPaint::kRight_Align)
	{
		m_text_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Right, KVIEW_LRMethod_Parent_Right, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Top);
	}

}

void KStaticView::viewSizeChange()
{
	KView::viewSizeChange();
    RERect rectParent = m_p_parent.lock()->GetRect();
    RERect rectOrigin = m_p_parent.lock()->getRectOrigin();
    sizeChange(rectParent, rectOrigin);

	if (m_text_drawable->isShow())
	{
		m_text_drawable->sizeChange(m_rect, m_rect_origin);
	}
	//for(VEC_DRAWABLE::iterator ite = m_lst_drawable.begin();ite != m_lst_drawable.end(); ++ite)
	//{
	//	(*ite)->sizeChange(m_rect, m_rect_origin);
	//}
}

void KStaticView::SetTextBound(RERect rect)
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetRect(rect);
}

void KStaticView::SetTextBold(kn_bool bBold)
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->setBold(bBold);
}

// View
void KStaticView::SetTextClip(RERect rect)
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetClip(rect);
}

kn_bool  KStaticView::isPointInView(int x, int y)
{
	if (!m_b_check_alpha)
	{
		return  KView::isPointInView(x,y);
	}

	if(  KView::isPointInView(x+1, y+1) )
	{
		//
		if ( m_check_alpha_da.get() == NULL)
		{
			m_check_alpha_da = m_lst_drawable[0];
		}
		return m_check_alpha_da->checkPoint(x - m_rect.left(), y - m_rect.top() );
	}

	return FALSE;
}

void KStaticView::setCheckAlphaDrawable( KImageDrawable_PTR b)
{
	m_check_alpha_da = b;
}


void KStaticView::checkAlpha( kn_bool b)
{
	m_b_check_alpha = b;
}


//void KStaticView::SetTextClipByView(RERect rect)
//{
//	writeLock lock(m_lst_drawable_mutex);
//	kn_int x, y;
//	GetScreenXY(x, y);
//
//	rect.offset(x, y);
//	m_text_drawable->SetClip(rect);
//}
//
//RERect KStaticView::GetTextClipByView()
//{
//	RERect rect = m_text_drawable->GetClip();
//
//	kn_int x, y;
//	GetScreenXY(x, y);
//
//	rect.offset(-x, -y);
//
//	return rect;
// 
//}



RERect KStaticView::GetTextBound()
{
	return m_text_drawable->GetRect();
}

RERect KStaticView::GetTextClip()
{
	return m_text_drawable->GetClip();
}


void KStaticView::StartTextAnimation()
{
	if(m_ani_thread_txt.isPlaying())
	{
		return;
	}

	CGLACIERAnimation* pGLACIERAnimation = new CGLACIERAnimation (2000, 0, 0);	

	RERect rectTextTarget = GetTextBound();
	SetTextClip(rectTextTarget);

	RERect rectTextsrc = rectTextTarget;
	rectTextsrc.offset(0, rectTextsrc.height());
	SetTextBound(rectTextsrc);
	 

	CPropertyText* pText = new CPropertyText(shared_from_this(), rectTextTarget, rectTextTarget);
	CPropertyAnimationData* pAnimationData = new CPropertyAnimationData(pText, KEasingCurve::OutCirc);
	pGLACIERAnimation->addAnimationData(pAnimationData);
	pGLACIERAnimation->setLoopType(CGLACIERAnimation::LOOP_TIME);
	pGLACIERAnimation->setLoopTimes(1000);

	m_ani_thread_txt.clearAnimation();
	m_ani_thread_txt.addAnimation(pGLACIERAnimation);
	m_ani_thread_txt.Start();


}

void KStaticView::setBKGColor( REColor color )
{
	writeLock lock(m_lst_drawable_mutex);
	if (m_bk_drawable->getType() == KDrawable::KDRAWABLE_COLOR)
	{
		(boost::dynamic_pointer_cast<KColorDrawable>(m_bk_drawable) )->setColor(color);
	}
	else
	{//
		m_bk_drawable = KColorDrawable_PTR(new KColorDrawable(RE_ColorBLACK));
		m_lst_drawable[0] = m_bk_drawable;
		
		m_bk_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Right, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Bottom);
	}
	m_bk_drawable->SetShow(TRUE);

}

void KStaticView::setBKGImage(const kn_string& path)
{
	
	writeLock lock(m_lst_drawable_mutex);
	if (m_bk_drawable->getType() == KDrawable::KDRAWABLE_IMAGE)
	{
		(boost::dynamic_pointer_cast<KImageDrawable>(m_bk_drawable))->CreateFromFile(path);
		
	}
	else
	{//
		m_bk_drawable = KImageDrawable_PTR(new KImageDrawable(path));
		m_lst_drawable[0] = m_bk_drawable;

 
	}
	m_bk_drawable->SetShow(TRUE);
}

void KStaticView::setIconImage( const kn_string& resPath )
{
	if(resPath.empty())
	{
		return;
	}
	writeLock lock(m_lst_drawable_mutex);
	m_icon_drawable->CreateFromFile(resPath);
	m_icon_drawable->SizeToImage();
	m_icon_drawable->SetShow(TRUE);
}

void KStaticView::sizeBKGToImage()
{
	writeLock lock(m_lst_drawable_mutex);
	if (m_bk_drawable->getType() == KDrawable::KDRAWABLE_IMAGE)
	{
		(boost::dynamic_pointer_cast<KImageDrawable>(m_bk_drawable))->SizeToImage();
		RERect rct;
		kn_bool ret = (boost::dynamic_pointer_cast<KImageDrawable>(m_bk_drawable))->GetImageBound(rct);
		SetRect(RERect::MakeXYWH(m_rect.left(), m_rect.top(), rct.width(), rct.height()));
	}
}

void  KStaticView::setBKDrawable( KDrawable_PTR p )
{
	writeLock lock(m_lst_drawable_mutex);
		m_bk_drawable = p;
		m_lst_drawable[0] = p;

	m_bk_drawable->SetShow(TRUE);

	m_bk_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Right, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Bottom);
}

void  KStaticView::setIconDrawable( KDrawable_PTR p )
{
 
	writeLock lock(m_lst_drawable_mutex);
	m_icon_drawable = boost::dynamic_pointer_cast<KImageDrawable>(p);
	m_lst_drawable[1] = p;
	m_icon_drawable->SetShow(TRUE);
	m_icon_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Left, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Top);
}

void  KStaticView::setTextDrawable( KTextDrawable_PTR p )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable = p;
	m_lst_drawable[2] = p;

	m_text_drawable->SetShow(TRUE);
}

////////////////////////////////////
KTextView::KTextView()
{
	m_e_viewtype = KVIEW_TEXT;
	m_b_do_msg = TRUE;
	m_b_enable_cursor_change = false;
	m_b_enable_state_change = false;
	m_text_normal_color = RE_ColorBLACK;
	m_text_focus_color = RE_ColorBLACK;
	m_text_pressed_color = RE_ColorBLACK;
	m_text_disable_color = RE_ColorBLACK;


}

KTextView::~KTextView()
{
}

void KTextView::shared_ptr_inited()
{
	KStaticView::shared_ptr_inited();
	m_sign_active.connect(this, &KTextView::onActive);
	m_sign_unactive.connect(this, &KTextView::onUnActive);
	m_sign_focus.connect(this,&KTextView::onFocus);
}

void  KTextView::setCursorChangeEnable(bool b)
{
	m_b_enable_cursor_change = b;
}
void  KTextView::setStateChangeEnable(bool b)
{
	m_b_enable_state_change = b;
}

void KTextView::setState( ViewState state, kn_bool bRefresh )
{//setstate
	if (m_state != state)
	{
		m_state = state;

		if (m_b_enable_state_change)
		{
			switch(state)
			{
			case BS_ACTIVE:
				KStaticView::SetTextColor(m_text_focus_color);
				if(m_b_enable_cursor_change)
				{
					SetMouseCursorStyle(CURSOR_HAND);
				}

				break;
			case BS_NORMAL:
				KStaticView::SetTextColor(m_text_normal_color);
				if(m_b_enable_cursor_change)
				{
					SetMouseCursorStyle(CURSOR_ARROW);
				}

				break;
			case BS_PRESSED:
				KStaticView::SetTextColor(m_text_pressed_color);
				break;
			case BS_DISABLED:
				KStaticView::SetTextColor(m_text_disable_color);
				break;
			default:
				break;
			}
			if (bRefresh)
			{
				InvalidateView();
			}
		}
	}
}

KTextView::ViewState KTextView::getState()
{
	return m_state;
}


//
//void KTextView::onMoveDirect( kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg )
//{
//	if (getState() == BS_PRESSED)
//	{//
//		if (m_b_mouse_in_view && !isPointInView(iScreenX, iScreenY))   // 
//		{
//			m_b_mouse_in_view = false;   //
//			//			m_mouse_leave_signal.emit();
//		}
//		return;
//	}
//
//	
//
//	if(!m_b_mouse_in_view && isPointInView(iScreenX, iScreenY))    //
//	{
//		m_b_mouse_in_view = true;    //
//		setViewActive();
//		m_mouse_enter_signal.emit();
//
//		pMsg->setIdle(KMSG_RETURN_DILE);
//
//	}
//	else if (m_b_mouse_in_view )   
//	{
//		if(isPointInView(iScreenX, iScreenY) )
//		{//
//			pMsg->setIdle(KMSG_RETURN_DILE);
//		}
//		else
//		{// 
//			m_b_mouse_in_view = false;   //
//			unSetViewActive();
//			m_mouse_leave_signal.emit();
//		}
//
//	}
//}

void KTextView::onDownDirect( kn_int iScreenX, kn_int iScreenY , KMessageMouse* pMsg)
{
	if (isPointInView(iScreenX, iScreenY))
	{
		setState( BS_PRESSED);
		//
		setViewFocus();
	}
}

void KTextView::onUpDirect( kn_int iScreenX, kn_int iScreenY , KMessageMouse* pMsg)
{
	//kn_bool b_in = isPointInView(iScreenX, iScreenY) ;
	if (getState() == BS_PRESSED || getState() == BS_FOCUS)
	{
		setState(BS_ACTIVE);
		unSetViewFocus(); //zhic 
		//if (b_in)
		//{
		//	m_clicked_pos_signal.emit(iScreenX, iScreenY, pMsg);
		//	m_clicked_signal.emit(shared_from_this());
		//}
	}
	else
	{//downup
		pMsg->setIdle(KMSG_RETURN_CONTINUE);
	}
}

void KTextView::SetTextColor(REColor color)
{
	KStaticView::SetTextColor(color);
}
 
void KTextView::SetTextColor(REColor n_color, REColor f_color, REColor p_color, REColor d_color)
{
	m_text_normal_color = n_color;
	m_text_focus_color = f_color;
	m_text_pressed_color = p_color;
	m_text_disable_color = d_color;

	KStaticView::SetTextColor(m_text_normal_color);
}

void KTextView::SetTextClipEnable( kn_bool bStatus )
{
	writeLock lock(m_lst_drawable_mutex);
	m_text_drawable->SetClipEnable(bStatus);
}

void KTextView::onActive()
{
//	MyTrace(_T("onActive %s"), m_text_drawable->GetText().c_str()) ;
	setState(BS_ACTIVE);        //
}

void KTextView::onUnActive()
{

//	MyTrace(_T("onUnActive %s"), m_text_drawable->GetText().c_str()) ;
	setState(BS_NORMAL);        //
}
void KTextView::onFocus()
{
//	MyTrace(_T("onFocus %s"), m_text_drawable->GetText().c_str()) ;
	setState(BS_FOCUS);        //
}
//
kn_int KTextView::GetTextWidth()
{
	return  m_text_drawable->getTextWidth();
}
//
kn_int KTextView::GetFontSize()
{
	return m_text_drawable->GetPaint()->getTextSize();
}

REPaint* KTextView::GetTextPaint()
{
	return m_text_drawable->GetPaint();
}
