#version 330

in vec4 texelColor;
in vec4 vertexColor;

void main() 
{
	//if the user wants to use TEXTURE only,
	//set material so that vertex color will
	//be zero, and vice-versa
	gl_FragColor = vertexColor + texelColor;
}