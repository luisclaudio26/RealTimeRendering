#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
public:
	GLuint tex;
	void load_geometry() override;
	void load_uniforms() override;
};

#endif
