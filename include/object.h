#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "phong_mat.h"
#include "scene.h"
#include "shaders/shader.h"

class Object
{
protected:
	Shader s;
	PhongMaterial m;

	glm::mat4 model;

	Vertex* vertices; int n_vertices;
	unsigned int* edges; int n_edges;

	virtual void load_geometry() = 0;
public:
	GLuint myTex;

	Object(ShaderType t);

	void draw(const Scene& scene, GLuint framebuffer = 0);
	void prepare();	
};

#endif