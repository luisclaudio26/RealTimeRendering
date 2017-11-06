#include "../../include/shaders/shader_data.h"
#include <iostream>

uniform_loader_func uniform_loaders[] = { load_blinnphong_uniforms };

//TODO: move this to .cpp
void load_blinnphong_uniforms(const ShaderData& data, const ShaderHandler& handler)
{
	//Load matrices
	glUniformMatrix4fv(handler.BlinnPhong.model, 1, GL_FALSE, &data.BlinnPhong.model[0][0]);
	glUniformMatrix4fv(handler.BlinnPhong.vp, 1, GL_FALSE, &data.BlinnPhong.vp[0][0]);

	//camera position	
	glUniform3f(handler.BlinnPhong.cam, data.BlinnPhong.cam[0], 
										data.BlinnPhong.cam[1], 
										data.BlinnPhong.cam[2]);
	
	//material settings
	glUniform1f(handler.BlinnPhong.material.k_d, data.BlinnPhong.material.k_d);
	glUniform1f(handler.BlinnPhong.material.k_a, data.BlinnPhong.material.k_a);

	
	glUniform3f(handler.BlinnPhong.material.d, data.BlinnPhong.material.d[0], 
												data.BlinnPhong.material.d[1],
												data.BlinnPhong.material.d[2]);

	glUniform3f(handler.BlinnPhong.material.a, data.BlinnPhong.material.a[0], 
												data.BlinnPhong.material.a[1],
												data.BlinnPhong.material.a[2]);
}