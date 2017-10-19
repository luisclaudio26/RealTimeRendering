#version 150

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;
};

//------------------------------------------

uniform _model model;
uniform mat4 viewProj;
uniform vec3 cam;

in vec3 pos;
in vec3 normal;
in vec3 tex;

flat out vec3 vcolor;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	gl_Position = viewProj * model.transform * vec4(pos, 1.0);
	vcolor = model.kA * model.a;
}