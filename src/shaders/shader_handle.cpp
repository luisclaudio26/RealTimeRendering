#include "../../include/shaders/shader_handler.h"

location_loader_func location_loaders[] = { get_location_blinnphong };

void get_location_blinnphong(GLuint program, ShaderHandler& handlers)
{
	handlers.BlinnPhong.model = glGetUniformLocation(program, "model.model2world");
	handlers.BlinnPhong.vp = glGetUniformLocation(program, "viewProj");
	handlers.BlinnPhong.cam = glGetUniformLocation(program, "cam");

	handlers.BlinnPhong.material.a = glGetUniformLocation(program, "model.a");
	handlers.BlinnPhong.material.k_a = glGetUniformLocation(program, "model.kA");
	handlers.BlinnPhong.material.d = glGetUniformLocation(program, "model.d");
	handlers.BlinnPhong.material.k_d = glGetUniformLocation(program, "model.kD");
}