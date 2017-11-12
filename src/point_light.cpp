#include "../include/point_light.h"

PointLight::PointLight()
{
	pos = glm::vec4(5.0f, 5.0f, 0.0f, 1.0f);
	color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	k = 1.0f;
}