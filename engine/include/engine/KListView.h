//  **************************************
//  File:        KLISTVIEW.h
//  ***************************************
#ifndef KLISTVIEW_DEFINED
#define KLISTVIEW_DEFINED

#include "KButtonView.h"
#include "KViewGroup.h"
#include "AnimationThread.h"
#include "KMoveableView.h"
#include "boost/thread/recursive_mutex.hpp"
#include "KShapeDrawable.h"

// 
struct TrackPoint
{
	kn_int y;	//	Y
	kn_dword ticks;	// 

	TrackPoint(int);
	TrackPoint();

};
 
class API KListView : public KViewGroup
{
public:

	enum
	{
		LS_NORMAL,
		LS_SCROLLING,	// 
		LS_ITEMCLICK 	// item

	};

	KListView() ;
	virtual ~KListView();
	virtual void shared_ptr_inited();
	// View
	void UI_addItemView(KView_PTR pItemView);

	// Item
	void UI_clearAllItems();

	// ItemView
	KView_PTR getItemView(kn_int index);

 
	// 
	kn_int getItemCount();

	//void setViewport(RERect rect);

	// 
	int adjustInViewport(int iPosY);

	void bindData(vector<kn_string>& vData);

	// 
	void scrollByOffsetAnimation(int y);

	// 
	void scrollByOffset(int y);
	void scrollByPos(int y);

	// ItemGroup
	kn_int calcScrollerPos(int iItemsTop);

	void  onKeydown(KMessageKey* pMsg);

	virtual void onDownDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onMoveDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onUpDirect(kn_int iScreenX, kn_int iScreenY, KMessageMouse* pMsg); 
	virtual void onWheelDirect(KMessageMouseWheel* pMsg); 

	virtual kn_bool Create(kn_int iX, kn_int iY, kn_int iWidth, kn_int iHeight);

	// FastScroll 
	void showFastScroller(kn_bool bShow);

	// 
	void setDivider(KDrawable_PTR pDrawable);
	 

	// 
	void setScroller();

	// .listview
	kn_bool isAnimationRunning();

	//  
	void UI_SetToBottom();

	// 
	void enableDrag(kn_bool b);
	 
protected:

	void createListView();

	KTextView_PTR createListItem(RERect& rect, kn_string& strItem);

	void dragLastPhyHandler();


	// 
	void setFastScroller();

	void  onFastScrollerDown(kn_int x, kn_int y, KMessageMouse* pMsg);
	void  onFastScrollerMove(kn_int x, kn_int y, KMessageMouse* pMsg);
	void  onFastScrollerUp(kn_int x, kn_int y,  KMessageMouse* pMsg);

	void onItemClick(KView_PTR pView);

	void updateFastScrollerPos(kn_float y);

	//   / item
	kn_int judgeScrollState();


	// item group 
	void resetItemGroup();

protected:

	
	vector<kn_string> m_vec_data;

	CAnimationThread m_ani_thread;

	// 
	REPoint m_last_press_point;
	REPoint m_first_press_point;

	// listviewtop
	kn_int m_i_press_top; 

	// listview, ,m_rect
	RERect m_rect_viewport;

	// , Y
	vector<TrackPoint> m_vec_touchpoints;

	// 
	KView_PTR m_p_scroller;

	//  drawable
	KShapeDrawable_PTR m_drawable_slider;

	// 
	KMoveableView_PTR m_p_fast_scroller;

	kn_bool m_b_show_scroller;

	// ,listview
	KViewGroup_PTR m_p_item_groupview;

	//   listview / Item  
	kn_int m_i_scroll_state; 

	// 
	KDrawable_PTR m_drawable_divider;

	// 
	kn_int m_i_divider_height;

	// item
	kn_int m_i_item_height;

	// 
	kn_int m_i_item_count;

	// 
	kn_bool m_b_enable_drag;

 

};

typedef boost::shared_ptr<KListView> KListView_PTR;


#endif // KLISTVIEW_DEFINED

