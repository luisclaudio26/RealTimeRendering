#include "../include/cube.h"
#include <iostream>

void Cube::load_geometry()
{
	//24 vertices, because we need 3 of each vertices
	//so to define correct normals
	//TODO: fix texture coordinates
	this->vertices = new Vertex[24];

	vertices[0] = (Vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[1] = (Vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[2] = (Vertex){ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[3] = (Vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[4] = (Vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[5] = (Vertex){ glm::vec3(-0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[6] = (Vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[7] = (Vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, +1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[8] = (Vertex){ glm::vec3(-0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[9] = (Vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[10] = (Vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, +1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[11] = (Vertex){ glm::vec3(-0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[12] = (Vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[13] = (Vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[14] = (Vertex){ glm::vec3(+0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[15] = (Vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[16] = (Vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[17] = (Vertex){ glm::vec3(+0.5f, -0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[18] = (Vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[19] = (Vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, +1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[20] = (Vertex){ glm::vec3(+0.5f, +0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) };

	vertices[21] = (Vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(+1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[22] = (Vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, +1.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
	vertices[23] = (Vertex){ glm::vec3(+0.5f, +0.5f, +0.5f), glm::vec3(0.0f, 0.0f, +1.0f), glm::vec2(0.0f, 0.0f) };

	this->n_vertices = 24;

	//---

	this->edges = new unsigned int[36];

	edges[0] = 20; edges[1] = 14; edges[2] = 2;
	edges[3] = 8; edges[4] = 20; edges[5] = 2;

	edges[6] = 5; edges[7] = 11; edges[8] = 23;
	edges[9] = 5; edges[10] = 23; edges[11] = 17;

	edges[12] = 19; edges[13] = 22; edges[14] = 10;
	edges[15] = 19; edges[16] = 10; edges[17] = 7;

	edges[18] = 4; edges[19] = 16; edges[20] = 14;
	edges[21] = 1; edges[22] = 4; edges[23] = 13;

	edges[24] = 15; edges[25] = 12; edges[26] = 18;
	edges[27] = 15; edges[28] = 18; edges[29] = 21;

	edges[30] = 3; edges[31] = 0; edges[32] = 6;
	edges[33] = 3; edges[34] = 6; edges[35] = 9;

	this->n_edges = 36;
}