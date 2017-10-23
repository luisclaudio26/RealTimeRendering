#include "../include/object.h"
#include "../include/shader_loader.h"

#include <cstdlib>

//---------------------------------------------------
//-------------------- INTERNAL ---------------------
//---------------------------------------------------
static void load_vec3_uniform(GLuint handler, const glm::vec3& v) {
	glUniform3f(handler, v[0], v[1], v[2]);
}

//--------------------------------------------------------
//-------------------- FROM OBJECT.H ---------------------
//--------------------------------------------------------
Object::Object()
{
	this->h_program = this->h_data = 0;
	this->h_model = this->h_vp = 0;
	this->model = this->viewProj = glm::mat4(1.0f);

	glGenVertexArrays(1, &this->h_VAO);
}

void Object::set_view_projection(const glm::mat4& vp)
{
	this->viewProj = vp;
}

void Object::set_shader_program(const std::string& path)
{
	this->h_program = ShaderLoader::load(path);

	//request handlers for this shader
	this->request_handlers();
}

void Object::request_handlers()
{
	//TODO: We probably need also a way to store the handler
	//of the camera position: we store the handler, receive
	//the actual camera vector in the DRAW() function, then
	//we download it on the card using glUniform___.
	this->h_model = glGetUniformLocation(this->h_program, "model.model2world");	
	this->h_vp = glGetUniformLocation(this->h_program, "viewProj");
	this->material.request_handlers(this->h_program);
}

void Object::draw(const Scene& scene)
{	
	//Set model shader as current program
	glUseProgram(this->h_program);

	//Load matrices
	glUniformMatrix4fv(this->h_model, 1, GL_FALSE, &this->model[0][0]);
	glUniformMatrix4fv(this->h_vp, 1, GL_FALSE, &scene.viewProj[0][0]);

	//material settings
	this->material.download_as_uniform();

	//camera position
	GLint h_cam = glGetUniformLocation(this->h_program, "cam");
	glUniform3f(h_cam, scene.cam[0], scene.cam[1], scene.cam[2]);

	//bind VAO and draw elements. Element indices are taken in groups
	//of 3, to take the triangle; each integer index is used to access
	//the Attribute Arrays and then build a vertex which will be processed
	//in vertex shader.
	glBindVertexArray(this->h_VAO);
	glDrawElements(GL_TRIANGLES, this->n_indices, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);

	//unload stuff
	glUseProgram(0);
}