#ifndef _VERTEX_H_
#define _VERTEX_H_
#pragma once

//GLM
#include <glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

#endif /* _VERTEX_H_ */