#include "../include/object.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>

void Object::prepare_blinnphong(const Scene& scene, ShaderData& data)
{
	data.BlinnPhong.vp = scene.viewProj;
	data.BlinnPhong.cam = scene.cam;
	data.BlinnPhong.model = this->model;
	data.BlinnPhong.model_it = glm::transpose(glm::inverse(this->model));

	data.BlinnPhong.light.color = glm::vec3(scene.lights[0].color[0], 
											scene.lights[0].color[1],
											scene.lights[0].color[2]);
	
	data.BlinnPhong.light.dir = glm::vec3(scene.lights[0].dir[0], 
											scene.lights[0].dir[1], 
											scene.lights[0].dir[2]);
	
	data.BlinnPhong.material.a = this->m.a;
	data.BlinnPhong.material.d = this->m.d;
	data.BlinnPhong.material.k_a = this->m.k_a;
	data.BlinnPhong.material.k_d = this->m.k_d;
	data.BlinnPhong.material.tex = this->m.tex;
}

void Object::prepare_shadowmapper(const Scene& scene, ShaderData& data)
{

	glm::mat4 proj = glm::ortho<float>(-10, 10, -10, 10, -10, 20);

	glm::vec3 lDir = glm::vec3(scene.lights[0].dir[0], 
								scene.lights[0].dir[1], 
								scene.lights[0].dir[2]);
	glm::mat4 view = glm::lookAt(lDir, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	data.ShadowMapper.vp = proj * view;
	data.ShadowMapper.model = this->model;
}

//--------------------------------------------------------
//-------------------- FROM OBJECT.H ---------------------
//--------------------------------------------------------
Object::Object(ShaderType t)
{
	this->model = glm::mat4(1.0f);
	this->s.select_shader(t);

	prepare_funcs[0] = &Object::prepare_blinnphong;
	prepare_funcs[1] = &Object::prepare_shadowmapper;
}

void Object::prepare()
{
	load_geometry();
	s.upload_data(vertices, n_vertices, edges, n_edges);
}

void Object::draw(const Scene& scene, GLuint framebuffer)
{
	//TODO: we'll have multiple lights, so this function
	//is responsible for deferred light rendering, i.e.
	//baking geometry data into textures (normal, pos)
	//then calling Phong computation shaders so to
	//"paint" the result of one light and then summing
	//the result up.
	ShaderData data;
	(this->*prepare_funcs[this->s.t])(scene, data);
	s.draw(data, framebuffer);
}