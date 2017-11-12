#version 330

//uniform stuff
uniform sampler2D tex;

//fragment data
in vec2 frag_uv;
in vec4 vertexColor;

void main() 
{
	//if the user wants to use TEXTURE only,
	//set material so that vertex color will
	//be zero, and vice-versa
	vec4 texel = texture2D(tex, frag_uv);
	gl_FragColor = vertexColor + texel;
}