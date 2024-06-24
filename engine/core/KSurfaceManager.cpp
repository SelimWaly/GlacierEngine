//  **************************************
//  File:        KSurfaceManager.cpp
//  ***************************************
#include "KSurfaceManager.h"
#include "renderingengine.h"

KSurfaceManager* g_m = NULL;
KSurfaceManager* getSurfaceManager()
{
	if (g_m == NULL)
	{
		g_m = new KSurfaceManager();
	}
	return g_m;
}

void ReleaseSurfaceManager()
{
	SAFE_DELETE(g_m);
}

KSurfaceManager::KSurfaceManager()
{
}


KSurfaceManager::~KSurfaceManager()
{
	MAPSurfaceIter it;
	for ( it = m_SurfaceManagerMap.begin(); it != m_SurfaceManagerMap.end(); it++ )
	{
		 delete it->second;
	}

	m_SurfaceManagerMap.clear();
}

IRESurface* KSurfaceManager::GetSurface(kn_string surfacepath)
{
	MAPSurfaceIter mapitersurface = m_SurfaceManagerMap.find(surfacepath);
	if (mapitersurface != m_SurfaceManagerMap.end())
	{
		return mapitersurface->second;
	}
	//
	IRESurface* Surface = RESurfaceFactory::CreateRESurface(surfacepath);
	m_SurfaceManagerMap[surfacepath] = Surface;
	return Surface;
}
