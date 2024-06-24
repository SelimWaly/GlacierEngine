//  **************************************
//  File:        KSvgAnalyzing.h
//  ***************************************
#ifndef _KSVGANALYZING_H__
#define _KSVGANALYZING_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "tinyxml.h"

#include "KShapeDrawable.h"
using namespace std;

struct ArcData
{
	RERect rect;
	float startAngle;
	float sweepAngle;
};

class API KSvgAnalyzing
{
public:
	KSvgAnalyzing();
	~KSvgAnalyzing(void);
	//load
	void LoadSvgFile(kn_string& filePath,vector<KShape* >& pShapeList, RERect& rect,bool bScaleFlag);
private:
	//
	KShape* GetRectInfo(TiXmlElement* nodeElement);
	//
	KShape* GetCircleInfo(TiXmlElement* nodeElement);
	//
	KShape* GetEllipseInfo(TiXmlElement* nodeElement);
	//
	KShape* GetLineInfo(TiXmlElement* nodeElement);
	//
	KShape* GetPolylineInfo(TiXmlElement* nodeElement);
	//
	KShape* GetPolygonInfo(TiXmlElement* nodeElement);
	//
	KShape* GetPathInfo(TiXmlElement* nodeElement);
	//
	void GetPathsData(char* pPoints, REPath& path);
	//
	void AnalyzingPath(vector<string>& sectionList,REPath& path);
	//skiapath
	void SvgToSkiaData(vector<PathData>& pathDataList, REPath& path);
	//polygon
	void GetPointsData(char* pPoints,vector<REPoint>& pointList);
	//svg Arc skia
	ArcData ComputeArc(float x0, float y0,float rx, float ry,float angle,bool largeArcFlag,bool sweepFlag,float x, float y);
	//
	void SetShapePublicAttr(KShape* pShape,char* pName, char* pAttr);
	float m_scale; //
	bool m_bScale; //
};
#endif //  _KSVGANALYZING_H__

