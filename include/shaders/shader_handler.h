#ifndef SHADER_HANDLE_H
#define SHADER_HANDLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef union
{
	struct {
		GLuint vp, model, model_it, cam;

		struct {
			GLuint a, k_a;
			GLuint d, k_d;
			GLuint tex;
		} material;

		struct {
			GLuint dir, color;
		} light;
	} BlinnPhong;

	struct {
		GLuint vp, model;
	} ShadowMapper;

} ShaderHandler;

typedef void (*location_loader_func)(GLuint, ShaderHandler&);

void get_location_blinnphong(GLuint program, ShaderHandler& handlers);
void get_location_shadowmapper(GLuint program, ShaderHandler& handlers);
extern location_loader_func location_loaders[2];

#endif