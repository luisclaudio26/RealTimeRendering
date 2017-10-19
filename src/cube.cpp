#include "../include/cube.h"

void Cube::load_geometry()
{
	//Build and bring new vertex array to context
	glGenVertexArrays(1, &this->h_vertex_array);
	glBindVertexArray(this->h_vertex_array);

	//hardcoded data for a cube centered on the origin
	glm::vec3 cube[8];
	cube[0] = glm::vec3(-0.5f, -0.5f, -0.5f);
	cube[1] = glm::vec3(-0.5f, -0.5f, +0.5f);
	cube[2] = glm::vec3(-0.5f, +0.5f, -0.5f);
	cube[3] = glm::vec3(-0.5f, +0.5f, +0.5f);
	cube[4] = glm::vec3(+0.5f, -0.5f, -0.5f);
	cube[5] = glm::vec3(+0.5f, -0.5f, +0.5f);
	cube[6] = glm::vec3(+0.5f, +0.5f, -0.5f);
	cube[7] = glm::vec3(+0.5f, +0.5f, +0.5f);

	//Load data into buffer
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	glBufferData(GL_ARRAY_BUFFER,
				8 * sizeof(glm::vec3),
				cube,
				GL_STATIC_DRAW);

	//with the current vertex array and data buffer loaded, 
	//load the parameters expected by the shader
	this->load_glsl_parameters();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	
}

