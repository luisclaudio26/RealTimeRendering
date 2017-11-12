#include "../include/phong_mat.h"
#include "../3rdparty/bmpread.h"

#include <iostream>
#include <cstdlib>

#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

//---------------------------------------------------------------------------
//--------------------------- FROM PHONGMATERIAL ----------------------------
//---------------------------------------------------------------------------
PhongMaterial::PhongMaterial()
{
	//TODO: change this after to something other than Black
	this->a = this->d = glm::vec3(1.0f, 1.0f, 1.0f);
	this->k_a = 0.2f;
	this->k_d = 0.0f;
	
	//load a blank texture as defaut. This is such
	//that it won't affect computation if we define
	//no texture
	glGenTextures(1, &this->tex);
	glBindTexture(GL_TEXTURE_2D, this->tex);

	GLubyte data[] = {255, 0, 0};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void PhongMaterial::load_ppm_texture(const char* path)
{
	bmpread_t bmp;

	//if there's any error, return and load nothing
	if(!bmpread(path, 0, &bmp))
	{
		std::cout<<"Error while reading .BMP texture!\n";
		return;
	}

	//load into OpenGL
	glBindTexture(GL_TEXTURE_2D, this->tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); OGL_OK

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.width, bmp.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.rgb_data);

	bmpread_free(&bmp);
}