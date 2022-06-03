///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain 16x16x16 block's data

#include <iostream>
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
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	

public :
	std::vector<float> vertex;
	std::vector<glm::vec3> blocks;

	Chunk(glm::vec2 position);
	void AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position);
	unsigned int GetVao();
};