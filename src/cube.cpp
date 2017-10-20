#include "../include/cube.h"
#include <iostream>

void Cube::load_geometry()
{
	typedef struct {
		glm::vec3 p, n;
	} vertex;

	//24 vertices, because we need 3 of each vertices
	//so to define correct normals
	vertex cube_v[24];
	cube_v[0] = (vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f) };
	cube_v[1] = (vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f) };
	cube_v[2] = (vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) };

	cube_v[3] = (vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f) };
	cube_v[4] = (vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, -1.0f, 0.0f) };
	cube_v[5] = (vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f) };

	cube_v[6] = (vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f) };
	cube_v[7] = (vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, +1.0f, 0.0f) };
	cube_v[8] = (vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) };

	cube_v[9] = (vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f) };
	cube_v[10] = (vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, +1.0f, 0.0f) };
	cube_v[11] = (vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f) };

	cube_v[12] = (vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f) };
	cube_v[13] = (vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f) };
	cube_v[14] = (vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) };

	cube_v[15] = (vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f) };
	cube_v[16] = (vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, -1.0f, 0.0f) };
	cube_v[17] = (vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f) };

	cube_v[18] = (vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f) };
	cube_v[19] = (vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, +1.0f, 0.0f) };
	cube_v[20] = (vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) };

	cube_v[21] = (vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f) };
	cube_v[22] = (vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, +1.0f, 0.0f) };
	cube_v[23] = (vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f) };

	unsigned int cube_e[] = { 20, 14, 2, //Backface
								8, 20, 2,
								
								5, 11, 23, //Frontface
								5, 23, 17,
								
								19, 22, 10,
								19, 10, 7, //Top
								
								4, 16, 14, 
								1, 4, 13, //Bottom
								
								15, 12, 18,
								15, 18, 21, //Right
								
								3, 0, 6, //Left
								3, 6, 9 };
	this->n_indices = 36;

	//create buffers
	glGenBuffers(1, &this->h_data);
	glGenBuffers(1, &this->h_indices);

	//download data into buffers -> TODO: CHECK THIS!!!
	glBindVertexArray(this->h_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->h_data);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_v), cube_v, GL_STATIC_DRAW);

	GLuint id_pos = glGetAttribLocation(this->h_program, "pos");
	glEnableVertexAttribArray(id_pos);
	glVertexAttribPointer(id_pos, 3, GL_FLOAT, GL_FALSE, 3, (GLvoid*)0);

	GLuint id_normal = glGetAttribLocation(this->h_program, "normal");
	glEnableVertexAttribArray(id_normal);
	glVertexAttribPointer(id_normal, 3, GL_FLOAT, GL_FALSE, 3, (GLvoid*)3);

	//build vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->h_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_e), cube_e, GL_STATIC_DRAW);

	//unbind VAO
	glBindVertexArray(0);
}

