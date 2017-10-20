#version 330

flat in vec3 vcolor;

out vec4 fragColor;

void main() 
{
	//fragColor = vec4(vcolor, 1.0);
	fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}