#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstring>

#include "../include/cube.h"

GLFWwindow* setup();

int main(int argc, char** args)
{
	GLFWwindow* window = setup();

	Scene scene;
	scene.cam = glm::vec3(0.0f, 0.0f, -5.0f);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.01f, 20.0f);
	glm::mat4 view = glm::lookAt(scene.cam, //Position 
								glm::vec3(0.0f, 0.0f, 0.0f), 	//Look direction
								glm::vec3(0.0f, 1.0f, 0.0f) );	//Up

	glm::mat4 PV = proj*view;

	Cube cube;
	cube.set_view_projection(PV);
	cube.set_shader_program("../shaders/flat");
	cube.load_geometry();

	do
	{
		//Clear screen -> this function also clears stencil and depth buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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
	glewExperimental = true; //Where the fuck is this coming from?
	glewInit();

	//Get keyboard input
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Enable z-buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return window;
}