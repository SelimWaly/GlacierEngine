//  **************************************
//  File:        KSurfaceManager.h
//  ***************************************
#ifndef K_SURFACE_MANAGER_H
#define K_SURFACE_MANAGER_H

#include "boost/unordered_map.hpp"
#include "renderingengine.h"
#define  mapSurfaceMap boost::unordered_map<kn_string, IRESurface*>
using namespace skia_surface;
class API KSurfaceManager
{
private:

	mapSurfaceMap m_SurfaceManagerMap;
public:
	KSurfaceManager();
	~KSurfaceManager();
	IRESurface* GetSurface(kn_string surfacepath);
};
typedef mapSurfaceMap::iterator MAPSurfaceIter;

API KSurfaceManager*  getSurfaceManager();
API void ReleaseSurfaceManager();
#endif
