///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain 16x16 block's data

#include <glm/glm.hpp>
#include <vector>

#pragma once
class Chunk 
{
	//Attributes and properties
private :
	glm::vec2 _position;
	unsigned int _width;
	unsigned int _height;

public :
	std::vector<glm::vec3> blocks;
	Chunk(glm::vec2 position);
};