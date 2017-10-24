#version 330

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;
};

struct _pointLight {
	vec3 o, d;
};

//------------------------------------------
in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec2 uv_frag;
out vec3 normal_frag;

uniform _model model;
uniform mat4 viewProj;
uniform vec3 cam;

void main() 
{	
	//Vertex position in clip space
	gl_Position = viewProj * model.model2world * vec4(pos, 1.0);

	//works only if model2world does not scale!
	vec3 normal_worldspace = (viewProj * model.model2world * vec4(normal, 0.0f)).xyz;
	normal_frag = normal;

	//pass uv texture coordinates
	uv_frag = uv;
}