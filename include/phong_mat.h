#ifndef PHONG_MAT_H
#define PHONG_MAT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class PhongMaterial
{
public:
	typedef struct {
		float k_a; glm::mat3 a;
		float k_d; glm::mat3 d;
	} param;

	typedef struct {
		GLint k_a, k_d, a, d;
	} handler;

	PhongMaterial();

	void request_handlers(GLuint program);
	void download_as_uniform();
};

#endif