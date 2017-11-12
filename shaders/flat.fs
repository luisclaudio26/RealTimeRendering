#version 330

//uniform stuff
uniform sampler2D tex;
uniform float kD; uniform vec3 d;
uniform float kA; uniform vec3 a;

uniform vec3 light_dir;
uniform vec3 light_color;

//fragment data
in vec2 frag_uv;
in vec3 world_pos;
in vec3 world_normal;

void main() 
{
	vec4 texel = texture2D(tex, frag_uv);

	//color for object depends on the base colors
	//defined and the texture. Correctly adjusting
	//these values in the material settings lend
	//to different blendings which can be used for
	//various effects.	
	vec4 color_d = (texel + vec4(d, 1.0f)) * vec4(light_color, 1.0f);
	vec4 color_a = (texel + vec4(a, 1.0f)) * vec4(light_color, 1.0f);
	
	//diffuse component
	float f = max(dot(-light_dir, world_normal), 0.0f);

	gl_FragColor = kA*color_a + f*kD*color_d;
}