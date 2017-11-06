#include "../include/object.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>

//--------------------------------------------------------
//-------------------- FROM OBJECT.H ---------------------
//--------------------------------------------------------
Object::Object(ShaderType t)
{
	this->model = glm::mat4(1.0f);
	this->s.select_shader(t);
}

void Object::prepare()
{
	load_geometry();
	s.upload_data(vertices, n_vertices, edges, n_edges);
}

void Object::draw(const Scene& scene, GLuint framebuffer)
{
	ShaderData data;

	//prepare uniform data
	if(this->s.t == BLINNPHONG)
	{
		data.BlinnPhong.vp = scene.viewProj;
		data.BlinnPhong.cam = scene.cam;
		data.BlinnPhong.model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));

		data.BlinnPhong.material.a = this->m.a;
		data.BlinnPhong.material.d = this->m.d;
		data.BlinnPhong.material.k_a = this->m.k_a;
		data.BlinnPhong.material.k_d = this->m.k_d;
	}

	s.draw(data, framebuffer);
}