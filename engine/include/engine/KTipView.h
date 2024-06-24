#ifndef KTipView_DEFINED
#define KTipView_DEFINED

#include "KViewGroup.h"
#include "KTextDrawable.h"
#include "KImageDrawable.h"
#include "KColorDrawable.h"
#include "KTextMultiLineDrawable.h"
#include "sigslot.h"

#define NO_HIDE_MENU 400

class KTipBase : public KViewGroup
{
public:
	KTipBase();
	virtual ~KTipBase();

	virtual void init(KScreen*, RERect rect, kn_string str=_T("") ); //tipviewscreen
	kn_bool isAutoHide();
	void setAutoHide(kn_bool b);
//	sigslot::signal1<int> m_sign_menu_click;
	void  setBKDrawable( KDrawable_PTR p );
	void  setTipText(kn_string );
	//
	void setShowTime(int);
	int	 getTipID();
protected:
	//menuview
	KTextMultiLineDrawable_PTR	m_txt_drawable;
	KDrawable_PTR	m_bk_drawable;

	//
	int	m_show_time;
	int m_max_w; //
	kn_bool m_b_auto_hide;

	static int m_s_id;
	int m_tip_id;
};
//Menu 
typedef boost::shared_ptr<KTipBase> KTipBase_PTR;

#endif

