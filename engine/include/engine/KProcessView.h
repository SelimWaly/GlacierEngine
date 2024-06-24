//  **************************************
//  File:        KProcessView.h
//  ***************************************

#ifndef KPROCESS_VIEW_DEFINED
#define KPROCESS_VIEW_DEFINED

#include "KButtonView.h"
#include "KViewGroup.h"
#include "AnimationThread.h"
#include "KShapeDrawable.h"
//
enum PROCESS_DIR
{
	PROCESS_Horizontal, //
	PROCESS_Vertical, //
};

class API KProcessView : public KStaticView
{
public:
	KProcessView() ;
	virtual ~KProcessView();
	virtual void init(PROCESS_DIR e = PROCESS_Horizontal);

	virtual void setValue(int iPos);    //
	int getValue();
	void enableProcessClip(kn_bool );
	void setIconDrawableRect(int l, int r, int w, int h);
protected:
	kn_int m_value;           // 0~100
	PROCESS_DIR m_e_dir; // 
	kn_bool m_b_auto_center_text; //
	kn_bool m_b_process_clip; //
};
typedef boost::shared_ptr<KProcessView> KProcessView_PTR;

class API KProcessCirleView : public KProcessView
{
public:
	KProcessCirleView() ;
	virtual ~KProcessCirleView();
	void init(REColor);
	virtual void setValue(int iPos);    //
protected:
	KShapeDrawable_PTR m_arc_drawable;

};
typedef boost::shared_ptr<KProcessCirleView> KProcessCirleView_PTR;


// 
class API KLoadingView : public KView
{
public:
	KLoadingView();
	virtual ~KLoadingView();

	// 
	void setCycleImage(const kn_string& strResPath);

	void setCycleDrawable(KDrawable_PTR drawable);

	// , iCycleTime : ms
	void startAnimation(int iCycleTime = 500,kn_int frame_time = 500);

	void endAnimation();

protected:
	 
	// 
	KDrawable_PTR m_drawable_cycle;

	CAnimationThread m_ani_thread;


};


typedef boost::shared_ptr<KLoadingView> KLoadingView_PTR;

#endif // KPROCESS_VIEW_DEFINED

