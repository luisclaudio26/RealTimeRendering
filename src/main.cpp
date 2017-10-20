#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cstring>

#include "../include/shader_loader.h"
#include "../include/cube.h"

GLFWwindow* setup();

int main(int argc, char** args)
{
	GLFWwindow* window = setup();
	glGetError(); //clean glewInit() error

	Scene scene;
	scene.cam = glm::vec3(0.0f, 0.0f, -5.0f);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.01f, 20.0f);
	glm::mat4 view = glm::lookAt(scene.cam, //Position 
								glm::vec3(0.0f, 0.0f, 0.0f), 	//Look at
								glm::vec3(0.0f, 1.0f, 0.0f) );	//Up

	glm::mat4 PV = proj*view;



	/*
	Cube cube;
	cube.set_view_projection(PV);
	cube.set_shader_program("../shaders/flat");
	cube.request_handlers();
	cube.load_geometry();
	*/
	
	GLenum err;

	GLuint programID = ShaderLoader::load("../shaders/flat");

	float cube_v[] = { 0.0f, 1.0f, 0.0f, 
		               -1.0f, 0.0f, 0.0f,
						1.0f, 0.0f, 0.0f};

	unsigned int cube_e[] = { 0, 1, 2 };

	//Load data into buffers
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint vertexData, indices;
	glGenBuffers(1, &vertexData);
	glBindBuffer(GL_ARRAY_BUFFER, vertexData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_v), cube_v, GL_STATIC_DRAW);

	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_e), cube_e, GL_STATIC_DRAW);	

	GLuint id_pos = glGetAttribLocation(programID, "pos");
	glEnableVertexAttribArray(id_pos);
	
	err = glGetError();
	std::cout<<"ERROR1 "<<err<<std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, VAO);

	err = glGetError();
	std::cout<<"ERROR2 "<<err<<std::endl;

	glVertexAttribPointer(id_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //vec3 is made of 3 floats

	err = glGetError();
	std::cout<<"ERROR3 "<<err<<std::endl;

	//Set model shader as current program
	glUseProgram(programID);

	do
	{
		//Clear screen -> this function also clears stencil and depth buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//we list and define the pointers to each
		//attribute (localized by the layout() directive
		//in the shader).		

		//bind indices and draw elements. Element indices are taken in groups
		//of 3, to take the triangle; each integer index is used to access
		//the Attribute Arrays and then build a vertex which will be processed
		//in vertex shader.
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)0);

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