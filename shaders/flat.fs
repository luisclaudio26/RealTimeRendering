#version 330

//uniform stuff
uniform sampler2D tex;

uniform float kD; uniform vec3 d;
uniform float kA; uniform vec3 a;

uniform vec3 light_pos;
uniform vec3 light_color;

//fragment data
in vec2 frag_uv;
in vec3 world_pos;
in vec3 world_normal;

void main() 
{
	//lookup texture
	vec4 texel = texture2D(tex, frag_uv);
	
	//compute illumination
	vec3 point2light = normalize(light_pos - world_pos);
	float f = max(dot(point2light, world_normal), 0.0f);

	vec4 pixel = vec4(kA*a + f*kD*d, 1.0f);

	//if the user wants to use TEXTURE only,
	//set material so that vertex color will
	//be zero, and vice-versa
	gl_FragColor = pixel + texel;
}