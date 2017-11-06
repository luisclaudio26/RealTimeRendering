#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../vertex.h"
#include "shader_data.h"
#include "shader_handler.h"

enum ShaderType
{
	BLINNPHONG = 0,
	TEXTURERENDERER = 1,
};

class Shader
{
private:
	const GLchar* load_file(const std::string& path);
	GLuint compile_file(const std::string& file, GLenum shaderType);
	GLuint get_shader_program(const std::string& path);

	GLuint h_VAO, h_program, h_data, h_indices;
	int n_indices;

	
	ShaderHandler handlers;

public:
	ShaderType t;
	
	Shader();

	void select_shader(ShaderType t);

	void upload_data(const Vertex* vertices, int n_vertices, 
						const unsigned int* edges, int n_edges);

	//uniform_data will be cast to the uniform data pack
	//we need, so one must take care of passing a valid
	//pointer, otherwise things can crash or glitches will
	//appear
	void draw(const ShaderData& uniform_data, GLuint framebuffer = 0);
};

#endif