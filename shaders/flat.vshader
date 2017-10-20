#version 330

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;
};

//------------------------------------------
in vec3 pos;

//uniform _model model;
//uniform mat4 viewProj;
//uniform vec3 cam;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	//gl_Position = viewProj * model.model2world * vec4(pos, 1.0);
	gl_Position = vec4(pos, 1.0f);
}