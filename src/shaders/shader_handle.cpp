#include "../../include/shaders/shader_handler.h"
#include <iostream>

#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

location_loader_func location_loaders[] = { get_location_blinnphong };

void get_location_blinnphong(GLuint program, ShaderHandler& handlers)
{
	handlers.BlinnPhong.model = glGetUniformLocation(program, "model.model2world"); OGL_OK
	handlers.BlinnPhong.vp = glGetUniformLocation(program, "viewProj"); OGL_OK
	handlers.BlinnPhong.cam = glGetUniformLocation(program, "cam"); OGL_OK

	handlers.BlinnPhong.material.a = glGetUniformLocation(program, "model.a"); OGL_OK
	handlers.BlinnPhong.material.k_a = glGetUniformLocation(program, "model.kA"); OGL_OK
	handlers.BlinnPhong.material.d = glGetUniformLocation(program, "model.d"); OGL_OK
	handlers.BlinnPhong.material.k_d = glGetUniformLocation(program, "model.kD"); OGL_OK
}