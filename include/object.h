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

class Object
{
protected:
	PhongMaterial material;

	glm::mat4 model; GLint h_model;

	//although this is redundant (every object will
	//have the same view-projection matrix stored),
	//it will be useful when doing render-to-texture
	//operations after.
	glm::mat4 viewProj; GLint h_vp;

	//Handler to the shader program used to render this
	GLuint h_program;

	//Handler to the array storing
	//the vertex data of this object
	GLuint h_vertex_array;

	//handler to array of indices which we'll
	//use to store the edges 
	GLuint h_indices; int n_indices;

	//request OpenGL the IDs (handlers)
	//for matrices, shader, etc.
	void request_handlers();

public:
	Object();
	
	void draw(const Scene& scene);
	void set_view_projection(const glm::mat4& vp);
	void set_shader_program(const std::string& path);
	virtual void load_geometry() = 0;
};

#endif