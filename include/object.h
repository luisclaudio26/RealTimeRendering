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
private:
	typedef void (Object::*Prepare_func)(const Scene&, ShaderData&);

	void prepare_blinnphong(const Scene& scene, ShaderData& data);
	void prepare_texturerenderer(const Scene& scene, ShaderData& data);

	Prepare_func prepare_funcs[2];

protected:
	Shader s;
	
	Vertex* vertices; int n_vertices;
	unsigned int* edges; int n_edges;

	virtual void load_geometry() = 0;

public:
	glm::mat4 model;
	PhongMaterial m;

	Object(ShaderType t);

	void draw(const Scene& scene, GLuint framebuffer = 0);
	void prepare();	
};

#endif