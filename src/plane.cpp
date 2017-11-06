#include "../include/plane.h"
#include <iostream>

void Plane::load_geometry()
{
	this->vertices = new Vertex[4];
	
	vertices[0] = (Vertex){ glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[1] = (Vertex){ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) };
	vertices[2] = (Vertex){ glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
	vertices[3] = (Vertex){ glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) };

	this->n_vertices = 4;

	//--

	this->edges = new unsigned int[6];

	edges[0] = 0; edges[1] = 1; edges[2] = 2;
	edges[3] = 0; edges[4] = 2; edges[5] = 3;

	this->n_edges = 6;
}