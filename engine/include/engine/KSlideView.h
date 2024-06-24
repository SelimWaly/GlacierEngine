//  **************************************
//  File:        KSlideView.h
//  ***************************************
#ifndef K_SLIDE_VIEW_DEFINED
#define K_SLIDE_VIEW_DEFINED

#include "KButtonView.h"
#include "KViewGroup.h"
#include "KTextView.h"
#include "KProcessView.h"

class API KSlideView : public KTextView
{
public:
	KSlideView() ;
	virtual ~KSlideView();

	void init(PROCESS_DIR e = PROCESS_Horizontal, int spacing1 = 0, int spacing2 = 0);
	void setMaxMin( int max, int min);
	virtual void onDownDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onMoveDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onUpDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 

	void setValue(float iPos, kn_bool b_call_back = FALSE); 


	void setSlideBarSize(int iPos, kn_bool b_call_back = FALSE);    
	int getValue();
	int getValueArea();

	sigslot::signal1<int> m_silder_value_change_sign;

public:
	kn_int m_value;           //0~100
	kn_int m_max; 
	kn_int m_min; 
	PROCESS_DIR m_e_dir;

	kn_bool m_drag_flag;
	int m_spacing1;
	int m_spacing2;

	REPoint m_down_point;
	int m_old_pos;
};

typedef boost::shared_ptr<KSlideView> KSlideView_PTR;

#endif // KPROCESS_VIEW_DEFINED

