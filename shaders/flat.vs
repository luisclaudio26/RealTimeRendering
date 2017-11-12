#version 330

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;

	//texture unit
	sampler2D tex;
};

struct _pointLight {
	vec3 o, d;
};

//------------------------------------------
in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec4 texelColor;
out vec4 vertexColor;

uniform _model model;
uniform mat4 viewProj;
uniform vec3 cam;

void main() 
{
	//Apply Model-View-Projection matrix to vertice
	vec4 final_pos = viewProj * model.model2world * vec4(pos, 1.0);
	vec4 final_normal = viewProj * model.model2world * vec4(normal, 0.0);
	gl_Position = final_pos;

	//compute color using directional light
	vec3 light_d = vec3(0.0f, 0.0f, 1.0f);
	float d = dot(light_d, normalize(normal));

	//output color/texel
	texelColor = texture(model.tex, uv);
	vertexColor = vec4(model.kA*model.a + d*model.kD*model.d, 1.0f);
}