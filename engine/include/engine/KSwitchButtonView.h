//  **************************************
//  File:        KSwitchButtonView.h
//  ***************************************
#ifndef KSwitchButtonView_DEFINED
#define KSwitchButtonView_DEFINED

#include "KTextView.h"
#include "KTextDrawable.h"
#include "KImageDrawable.h"
#include "KColorDrawable.h"
#include "KButtonView.h"
#include "sigslot.h"

class API KSwitchButtonView : public KImgButtonView
{
public:
	KSwitchButtonView();
	virtual ~KSwitchButtonView();
	virtual void shared_ptr_inited();
	/**OFFON :
	trueONfalseOFF
	ONOFFON->OFF
	OFFONOFF->ON
	*/
	void setResourse(IRESurface* on, IRESurface* off, kn_bool bON = TRUE);
	void setResourse(const kn_string& strOnResPath, const kn_string& strOffResPath, kn_bool bON = TRUE);
	void setResourseDrawable( KDrawable_PTR onDrawable, KDrawable_PTR offDrawable, kn_bool bON = TRUE);
	void showSwitchStatus();
	void onClick(kn_int x, kn_int y, KMessageMouse* pMsg);
	void setStatus(kn_bool b, kn_bool callback=FALSE); //callback 
	BOOL getStatus();
	sigslot::signal1<kn_bool> m_sign_state_changed;

protected:
	KDrawable_PTR m_off_drawable;
	KDrawable_PTR m_on_drawable;
	kn_bool m_b_on;
};

typedef boost::shared_ptr<KSwitchButtonView> KSwitchButtonView_PTR;
#endif

