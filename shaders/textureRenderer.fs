#version 330

in vec2 uv_frag;
uniform sampler2D texture_sampler;

void main() 
{
	vec3 texcolor = texture(texture_sampler, uv_frag).xyz;
	gl_FragColor = vec4(texcolor, 1.0f) + vec4(0.2f);
}