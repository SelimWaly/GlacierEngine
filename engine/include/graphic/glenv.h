//  **************************************
//  File:        glenv.h
//  ***************************************
#ifndef GLENV_H
#define GLENV_H

#include <GL/gl.h>
#include <GL/glu.h>

class API CGLEvn
{
public:
	CGLEvn();
	~CGLEvn();
	//
	void glenvRelease();
	//
	bool glenvInit(HDC hdc, int x,  int y,  int t, int b, bool b_mem = FALSE);
	//
	bool glenvActive();
	//
	void SwapBuffers();

	HGLRC m_hrc;
	HDC m_hdc;

	RECT m_rectClient;

	kn_bool  m_b_init;
};

#endif //GLENV_H
