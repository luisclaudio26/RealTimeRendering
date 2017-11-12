#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "point_light.h"

class Scene
{
public:
	std::vector<PointLight> lights;
	glm::vec3 cam;
	glm::mat4 viewProj;
};

#endif