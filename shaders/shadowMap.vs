#version 330

//------------------------------------------
//uniform model data
uniform mat4 model2world;

//uniform scene data
uniform mat4 viewProj;

in vec3 pos;

void main() 
{
	gl_Position = viewProj * model2world * vec4(pos, 1.0f);
}