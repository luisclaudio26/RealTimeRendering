#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
public:
	void load_geometry() override;
};

#endif


/*
	GLuint id_pos = glGetAttribLocation(this->shader_id, "pos");
*/