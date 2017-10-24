#version 330

in vec2 uv_frag;
uniform sampler2D myTextureSampler;

void main() 
{
	gl_FragColor = vec4(uv_frag.x, 0.0f, uv_frag.y, 1.0f);
}