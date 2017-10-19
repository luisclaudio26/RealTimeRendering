#ifndef CUBE_H
#define CUBE_H

#include "object.h"

class Cube : public Object
{
public:
	void load_geometry() override;
};

#endif


/*

//Position
	GLuint id_pos = glGetAttribLocation(this->shader_id, "pos");
	glEnableVertexAttribArray(id_pos);
	glVertexAttribPointer(id_pos,			//Attribute we're setting
							3,				//how many elements this attribute is composed
							GL_FLOAT,		//type of the element
							GL_FALSE,		//element is not normalized
							sizeof(Vertex), //offset to next attribute in array. MAYBE THIS WILL CAUSE PROBLEMS
							0);				//offset to the first attribute

	//Normal
	GLuint id_normal = glGetAttribLocation(this->shader_id, "normal");
	glEnableVertexAttribArray(id_normal);
	glVertexAttribPointer(id_normal,			
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(GLvoid*) (3*sizeof(GL_FLOAT)) );

	//Texture coordinates
	GLuint id_tex = glGetAttribLocation(this->shader_id, "tex");
	glEnableVertexAttribArray(id_tex);
	glVertexAttribPointer(id_tex,			
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(GLvoid*) (6*sizeof(GL_FLOAT)) ) ;

							*/