#include "../include/plane.h"
#include <iostream>

#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

void Plane::load_geometry()
{
	typedef struct {
		glm::vec3 p, n;
		glm::vec2 uv;
	} vertex;

	vertex p_v[4];
	p_v[0] = (vertex){ glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	p_v[1] = (vertex){ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) };
	p_v[2] = (vertex){ glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
	p_v[3] = (vertex){ glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	unsigned int p_e[] = { 0, 1, 2,
							0, 2, 3};
	this->n_indices = 6;

	//create buffers
	glGenBuffers(1, &this->h_data); OGL_OK
	glGenBuffers(1, &this->h_indices); OGL_OK

	//download data into buffers
	glBindVertexArray(this->h_VAO); OGL_OK

	glBindBuffer(GL_ARRAY_BUFFER, this->h_data); OGL_OK
	glBufferData(GL_ARRAY_BUFFER, sizeof(p_v), p_v, GL_STATIC_DRAW); OGL_OK

	
	GLuint id_pos = glGetAttribLocation(this->h_program, "pos"); OGL_OK
	glEnableVertexAttribArray(id_pos); OGL_OK
	glVertexAttribPointer(id_pos, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0); OGL_OK

	GLuint id_uv = glGetAttribLocation(this->h_program, "uv"); OGL_OK
	glEnableVertexAttribArray(id_uv); OGL_OK
	glVertexAttribPointer(id_uv, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(2*sizeof(glm::vec3))); OGL_OK

	GLuint id_normal = glGetAttribLocation(this->h_program, "normal"); OGL_OK
	glEnableVertexAttribArray(id_normal); OGL_OK
	glVertexAttribPointer(id_normal, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(glm::vec3)); OGL_OK


	//build vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->h_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(p_e), p_e, GL_STATIC_DRAW);

	//unbind VAO
	glBindVertexArray(0);
}

void Plane::load_uniforms()
{
	GLuint texID = glGetUniformLocation(this->h_program, "myTextureSampler");

	//bind texture with rendered image to unit 0
	//and load it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->tex);

	//apparently, loading the value 0 into a
	//texture uniform will make it load data
	//from Texture Unit 0. What!?
	glUniform1i(texID, 0);
}