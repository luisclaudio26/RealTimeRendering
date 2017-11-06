#version 330

in vec2 uv_frag;
in vec3 normal_frag;
uniform sampler2D myTextureSampler;

void main() 
{
	vec3 texcolor = texture(myTextureSampler, uv_frag).xyz;
	gl_FragColor = vec4(texcolor, 1.0f) + vec4(0.2f);
}