#ifndef DRAW_H
#define DRAW_H

#include "box2d/b2_types.h"

struct Camera
{
	Camera();

	// @TODO uint32 vs int32
	int32 m_width;
	int32 m_height;
};

// @TODO draw.cpp���� �����ϰ� ������� extern
extern Camera g_camera;


#endif // DRAW_H
