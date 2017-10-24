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
	//handler for model to world matrix
	GLint h_model;

	//although this is redundant (every object will
	//have the same view-projection matrix stored),
	//it will be useful when doing render-to-texture
	//operations after.
	GLint h_vp;

	//Handler to the shader program used to render this
	GLuint h_program;

	//Handler to the geometry data
	GLuint h_data;

	//Handler to the vertex array object
	GLuint h_VAO;

	//handler to array of indices which we'll
	//use to store the edges 
	GLuint h_indices; int n_indices;

	virtual void load_uniforms();

public:
	PhongMaterial material;

	Object();
	
	//request OpenGL the IDs (handlers)
	//for matrices, shader, etc.
	void request_handlers();

	void draw(const Scene& scene);
	void drawToTex(const Scene& scene, GLuint framebuffer);
	void set_shader_program(const std::string& path);
	virtual void load_geometry() = 0;

	glm::mat4 model;
};

#endif