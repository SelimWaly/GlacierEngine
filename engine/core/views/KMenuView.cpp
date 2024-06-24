//  **************************************
//  File:        KMenuView.cpp
//  ***************************************
#include "KMenuView.h"
#include "DataSync.h"
#include "KShapeDrawable.h"

/////////////////// KImgButtonView //////////////////////////
KMenuBase::KMenuBase()
{
	m_e_viewtype = KVIEW_MENU;
	m_b_auto_hide = TRUE;
	m_bk_drawable = KColorDrawable_PTR(new KColorDrawable(RE_ColorBLACK) );
	addDrawable(m_bk_drawable);
}

KMenuBase::~KMenuBase()
{
}

void KMenuBase::init( )
{

}

kn_bool KMenuBase::isAutoHide()
{
	return m_b_auto_hide;
}

void KMenuBase::setAutoHide(kn_bool b)
{
	m_b_auto_hide = b;
}

void  KMenuBase::setBKDrawable( KDrawable_PTR p )
{
	writeLock lock(m_lst_drawable_mutex);
	m_bk_drawable = p;
	m_lst_drawable[0] = p;

	m_bk_drawable->SetShow(TRUE);

	m_bk_drawable->SetViewChangeType(KVIEW_LRMethod_Parent_Left, KVIEW_LRMethod_Parent_Right, KVIEW_BTMethod_Parent_Top, KVIEW_BTMethod_Parent_Bottom);
}
