#include "../include/directional_light.h"

DirectionalLight::DirectionalLight()
{
	dir = glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f));
	color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	k = 1.0f;
}