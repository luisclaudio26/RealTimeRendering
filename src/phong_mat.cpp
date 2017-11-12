#include "../include/phong_mat.h"

//---------------------------------------------------------------------------
//--------------------------- FROM PHONGMATERIAL ----------------------------
//---------------------------------------------------------------------------
PhongMaterial::PhongMaterial()
{
	this->a = this->d = glm::vec3(0.0f, 1.0f, 0.0f);
	this->k_a = 0.3f;
	this->k_d = 1.0f;
	
	//load a blank texture as defaut. This is such
	//that it won't affect computation if we define
	//no texture
	glGenTextures(1, &this->tex);
	glBindTexture(GL_TEXTURE_2D, this->tex);

	GLubyte data[] = {0, 0, 0, 0};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}