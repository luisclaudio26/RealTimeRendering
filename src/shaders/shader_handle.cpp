#include "../../include/shaders/shader_handler.h"
#include <iostream>

#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

location_loader_func location_loaders[] = { get_location_blinnphong, 
											get_location_shadowmapper };

void get_location_blinnphong(GLuint program, ShaderHandler& handlers)
{
	handlers.BlinnPhong.model = glGetUniformLocation(program, "model2world"); OGL_OK
	handlers.BlinnPhong.model_it = glGetUniformLocation(program, "model2world_it"); OGL_OK
	handlers.BlinnPhong.vp = glGetUniformLocation(program, "viewProj"); OGL_OK
	handlers.BlinnPhong.cam = glGetUniformLocation(program, "cam"); OGL_OK

	handlers.BlinnPhong.material.a = glGetUniformLocation(program, "a"); OGL_OK
	handlers.BlinnPhong.material.k_a = glGetUniformLocation(program, "kA"); OGL_OK
	handlers.BlinnPhong.material.d = glGetUniformLocation(program, "d"); OGL_OK
	handlers.BlinnPhong.material.k_d = glGetUniformLocation(program, "kD"); OGL_OK
	handlers.BlinnPhong.material.tex = glGetUniformLocation(program, "tex"); OGL_OK

	handlers.BlinnPhong.light.dir = glGetUniformLocation(program, "light_dir"); OGL_OK
	handlers.BlinnPhong.light.color = glGetUniformLocation(program, "light_color"); OGL_OK
}

void get_location_shadowmapper(GLuint program, ShaderHandler& handlers)
{
	handlers.ShadowMapper.vp = glGetUniformLocation(program, "viewProj"); OGL_OK
	handlers.ShadowMapper.model = glGetUniformLocation(program, "model2world"); OGL_OK
}