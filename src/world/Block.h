///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Contain block vertices for render

#include <vector>
#include <glm/glm.hpp>
#include "Direction.h"

#pragma once
class Block
{
	//Attributes and properties
public :
	glm::vec3 position;
	std::vector<int> indexOffset;
	Block(glm::vec3 iPosition);
};