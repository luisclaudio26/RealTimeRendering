#include "../include/phong_mat.h"

static inline void load_vec3_uniform(GLuint handler, const glm::vec3& v) {
	glUniform3f(handler, v[0], v[1], v[2]);
}

//---------------------------------------------------------------------------
//--------------------------- FROM PHONGMATERIAL ----------------------------
//---------------------------------------------------------------------------

PhongMaterial::PhongMaterial()
{
	this->param.a = this->param.d = glm::vec3(1.0f, 1.0f, 1.0f);
	this->param.k_a = this->param.k_d = 1.0f;
	this->handler.k_a = this->handler.k_d = this->handler.a = this->handler.d = 0;
}

void PhongMaterial::request_handlers(GLuint program)
{
	//Handles to uniform parameters (i.e., which are global to the model)
	this->handler.a = glGetUniformLocation(program, "model.d");
	this->handler.k_a = glGetUniformLocation(program, "model.kD");

	this->handler.d = glGetUniformLocation(program, "model.a");
	this->handler.k_d = glGetUniformLocation(program, "model.kA");
}

void PhongMaterial::download_as_uniform()
{
	glUniform1f(this->handler.k_d, this->param.k_d);
	glUniform1f(this->handler.k_a, this->param.k_a);

	load_vec3_uniform(this->handler.d, this->param.d);
	load_vec3_uniform(this->handler.a, this->param.a);
}