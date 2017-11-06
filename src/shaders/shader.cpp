#include "../../include/shaders/shader.h"
#include <iostream>

//--------------------------------------------------------
//------------------ FROM SHADER.H -----------------------
//--------------------------------------------------------
const GLchar* Shader::load_file(const std::string& path)
{
	std::fstream file;
	file.open(path, std::ios_base::in);

	if(!file.is_open()) {
		std::cout<<"No such shader file!"<<std::endl;
		exit(0);
	}

	std::stringstream ss;
	
	while(!file.eof())
	{
		std::string buffer;
		getline(file, buffer);
		ss<<buffer<<std::endl;
	}

	file.close();

	//Copy to temporary place, which must be
	//deleted after (is it possible to change the
	//ownership of the char vector underlying ss, so 
	//we don't have to copy?)
	std::string code = ss.str();
	GLchar* temp = new GLchar[code.length() + 1];
	strcpy(temp, code.c_str());
	
	return temp;
}

GLuint Shader::compile_file(const std::string& file, GLenum shaderType)
{
	const GLchar* code = load_file(file);

	//Load code and compile
	GLuint id = glCreateShader(shaderType);
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	//display any warning messages
	char buffer[1000];
	glGetShaderInfoLog(id, 1000, NULL, buffer);
	std::cout<<"Shader compilation log: "<<buffer<<std::endl;

	delete[] code;

	return id;
}

GLuint Shader::get_shader_program(const std::string& path)
{
	std::string v_path(path); 
	v_path.append(".vs");
	GLuint v_shader_id = compile_file(v_path, GL_VERTEX_SHADER);

	std::string f_path(path); 
	f_path.append(".fs");
	GLuint f_shader_id = compile_file(f_path, GL_FRAGMENT_SHADER);

	//Create program, attach and link compiled shaders
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, v_shader_id);
	glAttachShader(program_id, f_shader_id);
	glLinkProgram(program_id);

	return program_id;
}

Shader::Shader()
{
	this->n_indices = -1;
	this->h_program = this->h_data = 0;

	glGenVertexArrays(1, &this->h_VAO); OGL_OK
}

void Shader::select_shader(ShaderType t)
{
	switch(t)
	{
	case BLINNPHONG:
		this->t = t;
		this->h_program = get_shader_program("../shaders/flat");
		break;
	}

	//get handlers for this shader
	location_loaders[this->t]( this->h_program, this->handlers );
}

void Shader::upload_data(const Vertex* vertices, int n_vertices, 
							const unsigned int* edges, int n_edges)
{
	//TODO: if h_data/h_indices are already in use,
	//drop handlers before generating these

	//create buffers
	glGenBuffers(1, &this->h_data); OGL_OK
	glGenBuffers(1, &this->h_indices); OGL_OK

	//download data into buffers
	glBindVertexArray(this->h_VAO); OGL_OK
	glBindBuffer(GL_ARRAY_BUFFER, this->h_data); OGL_OK
	
	glBufferData(GL_ARRAY_BUFFER, n_vertices, vertices, GL_STATIC_DRAW); OGL_OK

	//define location for each vertex attribute
	GLuint id_pos = glGetAttribLocation(this->h_program, "pos"); OGL_OK
	glEnableVertexAttribArray(id_pos); OGL_OK
	glVertexAttribPointer(id_pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); OGL_OK

	GLuint id_normal = glGetAttribLocation(this->h_program, "normal"); OGL_OK
	glEnableVertexAttribArray(id_normal); OGL_OK
	glVertexAttribPointer(id_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3)); OGL_OK

	GLuint id_uv = glGetAttribLocation(this->h_program, "uv"); OGL_OK
	glEnableVertexAttribArray(id_uv); OGL_OK
	glVertexAttribPointer(id_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2*sizeof(glm::vec3))); OGL_OK

	//build vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->h_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_edges, edges, GL_STATIC_DRAW);

	//unbind VAO
	glBindVertexArray(0);

	this->n_indices = n_edges;
}

void Shader::draw(const ShaderData& uniform_data, GLuint framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, 800, 600); //TODO: allow general viewports

	glUseProgram(this->h_program);

	//depending on the shader type, we need to load different
	//uniform variables
	uniform_loaders[this->t]( uniform_data, this->handlers );

	//bind VAO and draw elements. Element indices are taken in groups
	//of 3, to take the triangle; each integer index is used to access
	//the Attribute Arrays and then build a vertex which will be processed
	//in vertex shader.
	glBindVertexArray(this->h_VAO);
	glDrawElements(GL_TRIANGLES, this->n_indices, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);

	glUseProgram(0);
}