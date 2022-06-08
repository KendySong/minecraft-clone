///Author : kndysong@gmail.com
///Date : 07.06.2022
///Summary : Contain vertex data

#include <glm/glm.hpp>

#pragma once
struct VertexBuffer
{
	glm::vec3 position;
	glm::vec2 texUV;
	float texID;
};