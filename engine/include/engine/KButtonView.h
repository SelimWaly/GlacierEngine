//  **************************************
//  File:        KButtonView.h
//  ***************************************
#ifndef KButtonView_DEFINED
#define KButtonView_DEFINED

#include "KTextView.h"
#include "KTextDrawable.h"
#include "KImageDrawable.h"
#include "KColorDrawable.h"
#include "sigslot.h"


class API KImgButtonView : public KTextView
{
public:
	KImgButtonView();
	virtual ~KImgButtonView();

	void setBKGImage(const kn_string& normalResPath, 
					const kn_string& focusResPath, 
					const kn_string& selectedResPath, 
					const kn_string& disabledResPath);
	void setBKG( KDrawable_PTR normal,  KDrawable_PTR focus, KDrawable_PTR selected, KDrawable_PTR disabled);
//	void SizeBKGToImage();
//	void SetPressed(bool value);
	virtual void setState( ViewState state ,kn_bool bRefresh=TRUE);

private:
//	void NotifyPaint();

	KDrawable_PTR m_focus_bk_drawable;
	KDrawable_PTR m_selected_bk_drawable;
	KDrawable_PTR m_disable_bk_drawable;
	//alpha
	kn_bool m_b_check_alpha;
};
typedef boost::shared_ptr<KImgButtonView> KImgButtonView_PTR;

#endif

