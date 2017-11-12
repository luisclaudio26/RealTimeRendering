#ifndef PHONG_MAT_H
#define PHONG_MAT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class PhongMaterial
{
public:
	GLuint tex;

	float k_a; glm::vec3 a;
	float k_d; glm::vec3 d;

	PhongMaterial();
};

#endif