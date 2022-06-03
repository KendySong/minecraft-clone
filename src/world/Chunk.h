///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain 16x16x16 block's data

#include <vector>

#include <glm/glm.hpp>

#include "Block.h"
#include "../render/Shader.h"

#pragma once
namespace ChunkSize
{
	const unsigned int Width = 16;
	const unsigned int Height = 16;
	const unsigned int Depth = 16;
}

class Chunk 
{
	//Attributes and properties
private :
	unsigned int _vao;
	unsigned int _vbo;
	std::vector<float> _vertex;

public :
	std::vector<glm::vec3> blocks;

	Chunk(glm::vec2 position);

	unsigned int GetVao();
};