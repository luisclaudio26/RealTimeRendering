#include "../include/cube.h"
#include <iostream>

void Cube::load_geometry()
{
	//hardcoded data for a cube centered on the origin
	
	/*
	glm::vec3 cube_v[8];
	cube_v[0] = glm::vec3(-0.5f, -0.5f, -0.5f);
	cube_v[1] = glm::vec3(-0.5f, -0.5f, +0.5f);
	cube_v[2] = glm::vec3(-0.5f, +0.5f, -0.5f);
	cube_v[3] = glm::vec3(-0.5f, +0.5f, +0.5f);
	cube_v[4] = glm::vec3(+0.5f, -0.5f, -0.5f);
	cube_v[5] = glm::vec3(+0.5f, -0.5f, +0.5f);
	cube_v[6] = glm::vec3(+0.5f, +0.5f, -0.5f);
	cube_v[7] = glm::vec3(+0.5f, +0.5f, +0.5f);

	unsigned int cube_e[36] = { 6, 4, 0,
								0, 2, 6, //Backface
								1, 5, 7,
								1, 7, 3, //Frontface
								3, 7, 6,
								3, 6, 2, //Top
								1, 5, 4, 
								1, 4, 0, //Bottom
								5, 4, 6,
								5, 6, 7, //Right
								0, 1, 3, //Left
								1, 3, 2 };

	this->n_indices = 36;

	//Load data into buffers
	glGenBuffers(1, &this->h_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, this->h_vertex_array);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(glm::vec3), cube_v, GL_STATIC_DRAW);

	glGenBuffers(1, &this->h_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->h_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(int), cube_e, GL_STATIC_DRAW);

	//unbind stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/

	float cube_v[] = { 0.0f, 1.0f, 0.0f, 
		               -1.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f};

	unsigned int cube_e[3] = { 0, 1, 2 };

	this->n_indices = 3;

	//create buffers
	glGenBuffers(1, &this->h_data);
	glGenBuffers(1, &this->h_indices);

	//download data into buffers
	glBindVertexArray(this->h_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->h_data);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_v), cube_v, GL_STATIC_DRAW);

	GLuint id_pos = glGetAttribLocation(this->h_program, "pos");
	glEnableVertexAttribArray(id_pos);
	glVertexAttribPointer(id_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	//build vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->h_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_e), cube_e, GL_STATIC_DRAW);

	//unbind VAO
	glBindVertexArray(0);
}

