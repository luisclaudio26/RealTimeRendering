#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef struct
{
	//Position, Normal
	glm::vec3 p, n;

	//Texture coordinate
	glm::vec2 t;
} Vertex;

#endif