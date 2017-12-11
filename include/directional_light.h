#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "render_target.h"

class Object;

struct DirectionalLight
{
	glm::vec4 dir; 
	glm::vec4 color;
	float k;

	RenderTarget shadowMap;

	void compute_shadow_map( const std::vector<Object*>& pool );

	DirectionalLight();
};

#endif