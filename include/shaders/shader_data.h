#ifndef SHADER_DATA_H
#define SHADER_DATA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#include "shader_handler.h"

typedef union ShaderData
{
	struct {
		glm::mat4 vp, model, model_it;
		glm::vec3 cam;

		struct {
			glm::vec3 a, d;
			float k_a, k_d;
			GLuint tex;
		} material;

		struct {
			glm::vec3 pos, color;
		} light;
	} BlinnPhong;

	struct {
		glm::mat4 vp, model;
		glm::vec3 cam;
		GLuint tex;
	} TextureRenderer;	

	ShaderData() {}
} ShaderData;

typedef void (*uniform_loader_func)(const ShaderData&, const ShaderHandler&);

void load_blinnphong_uniforms(const ShaderData& data, const ShaderHandler& handler);
void load_texturerenderer_uniforms(const ShaderData& data, const ShaderHandler& handler);
extern uniform_loader_func uniform_loaders[2];

#endif