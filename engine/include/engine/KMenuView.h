//  **************************************
//  File:        KMenuView.h
//  ***************************************
#ifndef KMenuView_DEFINED
#define KMenuView_DEFINED

#include "KViewGroup.h"
#include "KTextDrawable.h"
#include "KImageDrawable.h"
#include "KColorDrawable.h"
#include "sigslot.h"

#define NO_HIDE_MENU 400

class API KMenuBase : public KViewGroup
{
public:
	KMenuBase();
	virtual ~KMenuBase();

	virtual void init();
	kn_bool isAutoHide();
	void setAutoHide(kn_bool b);
	sigslot::signal1<int> m_sign_menu_click;
	void  setBKDrawable( KDrawable_PTR p );
protected:
	//触发menu的view
	KView_PTR	m_active_view;
	KDrawable_PTR	m_bk_drawable;

	//自动隐藏，只要菜单收到点击消息就隐藏
	kn_bool m_b_auto_hide;

};
//Menu 类使用智能指针管理
typedef boost::shared_ptr<KMenuBase> KMenuBase_PTR;


//标准菜单
class API KMenuList : public KMenuBase
{
public:
	KMenuList();
	virtual ~KMenuList();

	virtual void init();
	void addItem();
private:

};
typedef boost::shared_ptr<KMenuList> KMenuList_PTR;

#endif

