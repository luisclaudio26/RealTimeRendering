#version 330

in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec2 uv_frag;

uniform mat4 model2world;
uniform mat4 viewProj;
uniform vec3 cam;

void main() 
{	
	//Vertex position in clip space
	gl_Position = viewProj * model2world * vec4(pos, 1.0);

	//pass uv texture coordinates
	uv_frag = uv;
}