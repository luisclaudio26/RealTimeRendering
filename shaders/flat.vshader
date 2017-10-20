#version 330

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;
};

//------------------------------------------
layout(location = 0) in vec3 pos;

flat out vec3 vcolor;

uniform _model model;
uniform mat4 viewProj;
uniform vec3 cam;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	gl_Position = viewProj * model.model2world * vec4(pos, 1.0);
	vcolor = model.kA * model.a;
}