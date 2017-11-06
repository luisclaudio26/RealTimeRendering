#include "../include/render_target.h"
#include <iostream>

#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

RenderTarget::RenderTarget()
{
	//Create a framebuffer. A framebuffer holds
	//textures and a depth buffer
	glGenFramebuffers(1, &h_framebuffer); OGL_OK
	glBindFramebuffer(GL_FRAMEBUFFER, h_framebuffer); OGL_OK

	//bind a TEXTURE to the the current bound
	//framebuffer
	glGenTextures(1, &h_renderedTexture); OGL_OK
	glBindTexture(GL_TEXTURE_2D, h_renderedTexture); OGL_OK

	glTexImage2D(GL_TEXTURE_2D,  //Target texture
					0, 			//Mip-map level
					GL_RGB, 	//Number of color components
					800, 600, 	//dimension TODO: make this generic
					0, 			//this must be zero (lol)
					GL_RGB, 	//Pixel data format
					GL_UNSIGNED_BYTE, //Store things using 1 unsigned byte per channel
					0);			//This is an empty texture
	OGL_OK

	//Set some filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); OGL_OK
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); OGL_OK

	//bind a DEPTH BUFFER to the framebuffer
	//currently bound
	glGenRenderbuffers(1, &h_depthBuffer); OGL_OK
	glBindRenderbuffer(GL_RENDERBUFFER, h_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600); //allocates storage for renderbuffer

	//attach renderbuffer object to a framebuffer object
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,			//Must be GL_FRAMEBUFFER
								GL_DEPTH_ATTACHMENT,	//it will be used as DEPTH buffer
								GL_RENDERBUFFER,		//Must be GL_RENDERBUFFER
								h_depthBuffer);			//the actual target
	OGL_OK

	//attach texture to framebuffer object
	glFramebufferTexture(GL_FRAMEBUFFER,
							GL_COLOR_ATTACHMENT0,
							h_renderedTexture,
							0); OGL_OK

	GLenum bufs[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, bufs); OGL_OK

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout<<"Error while creating framebuffer\n";	
}