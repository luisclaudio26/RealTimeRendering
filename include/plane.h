#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
public:
	Plane(ShaderType t) : Object(t) {}
	void load_geometry() override;
};

#endif
