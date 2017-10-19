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
	this->h_program = this->h_vertex_array = 0;
	this->h_model = this->h_vp = 0;
	this->model = this->viewProj = glm::mat4(1.0f);
}

void Object::set_view_projection(const glm::mat4& vp)
{
	this->viewProj = vp;
}

void Object::set_shader_program(const std::string& path)
{
	this->h_program = ShaderLoader::load(path);
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
	glUniformMatrix4fv(this->h_vp, 1, GL_FALSE, &this->viewProj[0][0]);

	//material settings
	this->material.download_as_uniform();

	//camera position
	GLint h_cam = glGetUniformLocation(this->h_program, "cam");
	glUniform3f(h_cam, 0.0f, 0.0f, 0.0f);

	//Load data for each model
	glBindVertexArray(this->h_vertex_array);
	glDrawArrays(GL_TRIANGLES, 0, this->out_vertices.size());
	
	//unload stuff
	glBindVertexArray(0);
	glUseProgram(0);
}