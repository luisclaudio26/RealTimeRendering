#version 330

//------------------------------------------
//uniform model data
uniform mat4 model2world;
uniform float kD; uniform vec3 d;
uniform float kA; uniform vec3 a;

//uniform scene data
uniform mat4 viewProj;
uniform vec3 cam;

//vertex data
in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec2 frag_uv;
out vec4 vertexColor;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	vec4 final_pos = viewProj * model2world * vec4(pos, 1.0);
	vec4 final_normal = viewProj * model2world * vec4(normal, 0.0);
	gl_Position = final_pos;

	//compute color using directional light
	vec3 light_d = vec3(0.0f, 0.0f, 1.0f);
	float f = dot(light_d, normalize(normal));

	//output color/texel
	vertexColor = vec4(kA*a + f*kD*d, 1.0f);
	frag_uv = uv;
}