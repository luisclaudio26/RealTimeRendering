#version 330

struct _model {
	mat4 model2world;

	//Intensity and color for diffuse, 
	//ambient and specular components
	float kD; vec3 d;
	float kA; vec3 a;
};

struct _pointLight {
	vec3 o, d;
};

//------------------------------------------
in vec3 pos;
in vec3 normal;

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
	vec4 light_d = vec4(0, 0, 1, 0);
	float d = dot(light_d, normalize(final_normal));

	//output color
	vertexColor = vec4(model.kA * model.a
						+ d * model.kD * model.d, 1.0f);
}