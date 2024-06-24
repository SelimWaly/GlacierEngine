﻿//  **************************************
//  File:        KGALLERY.h
//  ***************************************
#ifndef KGALLERY_DEFINED
#define KGALLERY_DEFINED

#include "KViewGroup.h"
#include "KTextView.h"
#include "AnimationThread.h" 



class API KGalleryItemView : public KTextView
{
public:
	KGalleryItemView();
	virtual ~KGalleryItemView();

	void SetFileName(kn_string&  str);

	kn_string GetFileName();

public:

	kn_string m_strFileName;




};
typedef boost::shared_ptr<KGalleryItemView> KGalleryItemView_PTR;

class API KGalleryView : public KViewGroup
{
public:
  
	KGalleryView() ;
	virtual ~KGalleryView();

	// 设置网格的大小和间距
	void setGridStyle(kn_int w, kn_int h, kn_int hi, kn_int vi);

	// 设置drawable列表
	//void bindDrawables(vector<KDrawable_PTR>& vDrawables);

	// 设置图片文件列表
	kn_bool bindFilelist (vector<kn_string>& vFlieList);

protected:

	// 单项点击事件
	void onItemClick(KView_PTR pView);

protected:

	// 缩略图的式样
	kn_int m_i_thum_width;
	kn_int m_i_thum_height;

	kn_int m_i_horizontal_interval;
	kn_int m_i_vertical_interval;

	// 缩略图的集合, 当前页
	KViewGroup_PTR m_p_thum_groupview;


	// 动画线程
	CAnimationThread m_ani_thread;


};

typedef boost::shared_ptr<KGalleryView> KGalleryView_PTR;


#endif // KGALLERY_DEFINED

