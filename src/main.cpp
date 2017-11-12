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
#include "../include/render_target.h"

GLFWwindow* setup();

int main(int argc, char** args)
{
	GLFWwindow* window = setup();
	glGetError(); //clean glewInit() error

	//scene setup
	Scene scene;
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.01f, 20.0f);
	scene.cam = glm::vec3(3.0f, 3.0f, 5.0f);

	//render target
	RenderTarget target;

	//geometry setup	
	Plane plane(BLINNPHONG); plane.prepare();
	plane.model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
	plane.m.load_ppm_texture("../data/bricks.bmp");
	plane.m.k_a = 0.0f;

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