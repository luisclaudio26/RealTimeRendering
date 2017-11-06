#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstring>

#define PI 3.14159265359
#define OGL_OK { \
					GLenum err; \
					if((err = glGetError()) != GL_NO_ERROR) \
						std::cout<<"Error at "<<__FILE__<<", line "<<__LINE__<<": "<<err<<std::endl; \
				}

#include "../include/cube.h"
#include "../include/plane.h"

GLFWwindow* setup();

int main(int argc, char** args)
{
	GLFWwindow* window = setup();
	glGetError(); //clean glewInit() error

	//scene setup
	Scene scene;
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.01f, 20.0f);
	scene.cam = glm::vec3(3.0f, 3.0f, 5.0f);

	//geometry setup
	//Cube cube(BLINNPHONG); cube.prepare();
	Plane plane(BLINNPHONG); plane.prepare();

	//------ Render to texture -------
	//Create a framebuffer. A framebuffer holds
	//textures and a depth buffers
	GLuint h_framebuffer = 0;
	glGenFramebuffers(1, &h_framebuffer); OGL_OK
	glBindFramebuffer(GL_FRAMEBUFFER, h_framebuffer); OGL_OK

	//bind a TEXTURE to the the current bound
	//framebuffer
	GLuint h_renderTarget;
	glGenTextures(1, &h_renderTarget); OGL_OK
	glBindTexture(GL_TEXTURE_2D, h_renderTarget); OGL_OK

	glTexImage2D(GL_TEXTURE_2D,  //Target texture
					0, 			//Mip-map level
					GL_RGB, 	//Number of color components
					800, 600, 	//dimension
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
	GLuint h_depthBuffer;
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
							h_renderTarget,
							0); OGL_OK

	GLenum bufs[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, bufs); OGL_OK

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout<<"Error while creating framebuffer!!!\n";

	//--------------------------------

	//floor.tex = h_renderTarget;

	do
	{
		//manage keyboard input
		if( glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS )
			scene.cam.x -= 0.15f;
		if( glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS )
			scene.cam.x += 0.15f;

		//set scene properties
		glm::mat4 view = glm::lookAt(scene.cam, //Position 
								glm::vec3(0.0f, 0.0f, 0.0f), 	//Look at
								glm::vec3(0.0f, 1.0f, 0.0f) );	//Up
		scene.viewProj = proj * view;

		//Clear screen -> this function also clears stencil and depth buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//draw objects
		plane.draw(scene);	

		//Swap buffer and query events
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
			!glfwWindowShouldClose(window));

	//Drop GLFW device
	glfwTerminate();

	return 0;
}

GLFWwindow* setup()
{
	//This will setup a new window and OpenGL context.
	//GLFW or GLUT may be used for this kind of stuff.
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 1); //Supersampling, 4 samples/pixel
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Make sure OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //version is 3.0

	//Something about which kind of OpenGL will run here
	//This says to glfw that we're using only OpenGL core functions, not
	//vendor-specific
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and set it as the context
	GLFWwindow *window = glfwCreateWindow(800, 600, "Physics", NULL, NULL);
	glfwMakeContextCurrent(window);

	//Initialize GLEW.
	glewExperimental = GL_TRUE; //Where the fuck is this coming from?
	glewInit(); //this launches an error!

	//Get keyboard input
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Enable z-buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return window;
}