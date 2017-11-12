#version 330

//------------------------------------------
//uniform model data
uniform mat4 model2world;
uniform mat4 model2world_it; //inverse transpose of model2world

//uniform scene data
uniform mat4 viewProj;
uniform vec3 cam;

//vertex data
in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec2 frag_uv;
out vec3 world_normal;
out vec3 world_pos;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	gl_Position = viewProj * model2world * vec4(pos, 1.0f);
	world_normal = normalize(model2world_it * vec4(normal, 0.0f)).xyz;
	world_pos = (model2world * vec4(pos, 1.0f)).xyz;

	//output color/texel
	frag_uv = uv;
}