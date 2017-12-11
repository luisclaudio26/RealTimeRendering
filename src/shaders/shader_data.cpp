#include "../../include/shaders/shader_data.h"
#include <iostream>

#define uniform3(h, v3) glUniform3f(h, v3[0], v3[1], v3[2])

uniform_loader_func uniform_loaders[] = { load_blinnphong_uniforms, 
											load_shadowmapper_uniforms };

void load_blinnphong_uniforms(const ShaderData& data, const ShaderHandler& handler)
{
	//Load matrices
	glUniformMatrix4fv(handler.BlinnPhong.model, 1, GL_FALSE, &data.BlinnPhong.model[0][0]);
	glUniformMatrix4fv(handler.BlinnPhong.model_it, 1, GL_FALSE, &data.BlinnPhong.model_it[0][0]);
	glUniformMatrix4fv(handler.BlinnPhong.vp, 1, GL_FALSE, &data.BlinnPhong.vp[0][0]);

	//camera position
	uniform3(handler.BlinnPhong.cam, data.BlinnPhong.cam);
		
	//material settings
	glUniform1f(handler.BlinnPhong.material.k_d, data.BlinnPhong.material.k_d);
	glUniform1f(handler.BlinnPhong.material.k_a, data.BlinnPhong.material.k_a);

	uniform3(handler.BlinnPhong.material.d, data.BlinnPhong.material.d);
	uniform3(handler.BlinnPhong.material.a, data.BlinnPhong.material.a);

	//light settings
	uniform3(handler.BlinnPhong.light.dir, data.BlinnPhong.light.dir);
	uniform3(handler.BlinnPhong.light.color, data.BlinnPhong.light.color);

	//put the desired texture in slot 0,
	//then upload slot zero into shader uniform	
	glActiveTexture(GL_TEXTURE0); //activate slot zero
	glBindTexture(GL_TEXTURE_2D, data.BlinnPhong.material.tex); //bind texture to previously activated slot
	glUniform1i(handler.BlinnPhong.material.tex, 0); //upload Zero to TEX uniform
}

void load_shadowmapper_uniforms(const ShaderData& data, const ShaderHandler& handler)
{
	glUniformMatrix4fv(handler.ShadowMapper.vp, 1, GL_FALSE, &data.ShadowMapper.vp[0][0]);
	glUniformMatrix4fv(handler.ShadowMapper.model, 1, GL_FALSE, &data.ShadowMapper.model[0][0]);
}