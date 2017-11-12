#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct PointLight
{
	glm::vec4 pos; 
	glm::vec4 color;
	float k;

	PointLight();
};

#endif