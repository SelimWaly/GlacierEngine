//  **************************************
//  File:        DataSync.h
//  ***************************************

#ifndef __DATA_SYNC_H
#define __DATA_SYNC_H
#include "KObject.h"
#include "renderingengine.h"
#include "KEasingCurve.h"
#include <boost/thread/thread.hpp>
#include "KView.h"

class API CPropertyBase: public KObject 
{
public:
	CPropertyBase(void);
	~CPropertyBase(void);
	enum PropertyTYPE
	{
		ATTR_NONE,
		ATTR_POS,
		ATTR_OPACITY,
		ATTR_BOUNDRECT,
		ATTR_ENUM_SIZE
	};
	virtual void DoChange()=0;
	CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, int iEasingCurveType);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve)=0;
	virtual CPropertyBase* copyProperty(KView_PTR p)=0;
	virtual CPropertyBase* copyProperty()=0;
	KView_PTR getView();
	void setView(KView_PTR p);
	virtual kn_bool isChange() ;
private:
	KView_PTR m_p_view;

};

typedef  vector<CPropertyBase*> PropertyBaseVector;

class API CPropertyPos: public CPropertyBase
{
public:
	CPropertyPos(KView_PTR p, kn_int x, kn_int y);
	~CPropertyPos(void);

	void getProperty( kn_int &x, kn_int &y);
	void setProperty(KView_PTR p, kn_int x, kn_int y);
	void DoChange();
	virtual kn_bool isChange();
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
private:
	REPoint m_point;
};

class API CPropertyOpacity: public CPropertyBase
{
public:
	CPropertyOpacity(KView_PTR p, kn_int opacity);
	~CPropertyOpacity(void);

	void getProperty(kn_int &opacity);
	void setProperty(KView_PTR p, kn_int opacity);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();
private:
	int m_i_opacity;
};

class API CPropertyPara: public CPropertyBase
{
public:
	CPropertyPara(KView_PTR p, kn_int para_id, double v);
	~CPropertyPara(void);

	void getProperty(kn_double &opacity);
	void setProperty(KView_PTR p, kn_double opacity);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();
private:
	double m_value;

	kn_int m_para_id;
};

class API CPropertyRect: public CPropertyBase
{
public:
	CPropertyRect(KView_PTR p, RERect rect);
	~CPropertyRect(void);

	void getProperty(RERect& rect);
	void setProperty(KView_PTR p, RERect rect);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();
private:
	RERect m_rect;
};

class API CPropertyAngle: public CPropertyBase
{
public:
	CPropertyAngle(KView_PTR p, REScalar degree, REScalar px, REScalar py);
	~CPropertyAngle(void);
	void getProperty(REScalar &a, REScalar &x, REScalar &y);
	void setProperty(KView_PTR p, REScalar degree, REScalar px, REScalar py);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();
private:
	REScalar m_degree;
	REScalar m_px;
	REScalar m_py;
};

class API CPropertyClip: public CPropertyBase
{
public:
	CPropertyClip(KView_PTR p, RERect rect);
	~CPropertyClip(void);

	void getProperty(RERect& rect);
	void setProperty(KView_PTR p, RERect rect);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();
private:
	RERect m_rect;
};


class API CPropertyText: public CPropertyBase
{
public:
	CPropertyText(KView_PTR p, RERect rectBound, RERect rectClip);
	~CPropertyText(void);

	void getProperty(RERect& rectBound, RERect& rectClip);
	void setProperty(KView_PTR p, RERect rectBound, RERect rectClip);
	virtual CPropertyBase* getCurrent(CPropertyBase* target, kn_double& dv, KEasingCurve* curve);
	virtual CPropertyBase* copyProperty(KView_PTR p);
	virtual CPropertyBase* copyProperty();
	virtual kn_bool isChange();
	void DoChange();

private:

	RERect m_rect;

	RERect m_rect_clip;
};


class API CPropertyList: public KObject
{
	PropertyBaseVector m_lst_data;
public:
	CPropertyList(){};
	~CPropertyList();
	void addProperty(CPropertyBase* p);
	void DoChange();
};

class API CDataSync: public KObject
{
public:
	CDataSync(void);
	~CDataSync(void);

	CPropertyList* getDataList();
	//id
	kn_int getNewID();
	//ID
	kn_bool checkID(kn_int&);
	//ID
	void addID(kn_int&);

	void addProperty(CPropertyBase* p);
	void release();

private:

	//
	CPropertyList* m_p_lst_data;

	//ID
	boost::shared_mutex m_id_mutex;
	vector<kn_int>	m_id_lst;

	//ID
	//ID: id
	//idid
	//
	kn_int	m_current_id;
	boost::mutex m_data_mutex;
};


#endif // __DATA_SYNC_H