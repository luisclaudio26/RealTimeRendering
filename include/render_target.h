#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct RenderTarget
{
	GLuint h_framebuffer;
	GLuint h_renderedTexture;
	GLuint h_depthBuffer;

	RenderTarget();
} RenderTarget;

#endif