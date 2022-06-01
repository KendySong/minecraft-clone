///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain 16x16 block's data

#include <vector>
#include <glm/glm.hpp>
#include "Block.h"

#pragma once
class Chunk 
{
	//Attributes and properties
private :
	glm::vec2 _position;

public :
	std::vector<Block> blocks;
	Chunk(glm::vec2 position);
};