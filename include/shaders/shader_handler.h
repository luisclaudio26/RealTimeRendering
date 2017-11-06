#ifndef SHADER_HANDLE_H
#define SHADER_HANDLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef union
{
	struct {
		GLuint vp, model, cam;

		struct {
			GLuint a, k_a, d, k_d;
		} material;
	} BlinnPhong;

} ShaderHandler;

typedef void (*location_loader_func)(GLuint, ShaderHandler&);

void get_location_blinnphong(GLuint program, ShaderHandler& handlers);
extern location_loader_func location_loaders[1];

#endif