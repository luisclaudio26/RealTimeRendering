#include "../../include/shaders/shader_data.h"
#include <iostream>

uniform_loader_func uniform_loaders[] = { load_blinnphong_uniforms, 
											load_texturerenderer_uniforms };

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

	//put the desired texture in slot 0,
	//then upload slot zero into shader uniform	
	glActiveTexture(GL_TEXTURE0); //activate slot zero
	glBindTexture(GL_TEXTURE_2D, data.BlinnPhong.material.tex); //bind texture to previously activated slot
	glUniform1i(handler.BlinnPhong.material.tex, 0); //upload Zero to TEX uniform
}

void load_texturerenderer_uniforms(const ShaderData& data, const ShaderHandler& handler)
{
	glUniformMatrix4fv(handler.TextureRenderer.vp, 1, GL_FALSE, &data.TextureRenderer.vp[0][0]);
	glUniformMatrix4fv(handler.TextureRenderer.model, 1, GL_FALSE, &data.TextureRenderer.model[0][0]);

	glUniform3f(handler.TextureRenderer.cam, data.TextureRenderer.cam[0], 
										data.TextureRenderer.cam[1], 
										data.TextureRenderer.cam[2]);

	//put the desired texture in slot 0,
	//then upload slot zero into shader uniform
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data.TextureRenderer.tex);
	glUniform1i(handler.TextureRenderer.tex, 0);
}