#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ShaderLoader
{
	const GLchar* load_code(const std::string& path);
	GLuint load_shader(const std::string& file, GLenum shaderType);
	GLuint load(const std::string& path);
};

#endif