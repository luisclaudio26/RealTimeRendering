#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
public:
	Cube(ShaderType t) : Object(t) {}
	void load_geometry() override;
};

#endif