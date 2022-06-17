///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain blocks position and create terrain

#include <iostream>
#include <chrono>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <FastNoiseLite/FastNoiseLite.h>

#pragma once
namespace ChunkSize
{
	const unsigned int WIDTH = 16;
	const unsigned int HEIGHT = 90;
	const unsigned int DEPTH = 16;
}

class Chunk 
{
	//Attributes and properties
private :
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	std::vector<float> _vertex;

	void PrepareRender();

public :
	bool north;
	bool south;
	bool east;
	bool west;

	glm::vec3 cornerPosition;
	glm::vec3 midPosition;
	unsigned int verticesDraw;
	std::vector<glm::vec3> blocks;

	Chunk();

	Chunk(glm::vec3 position, FastNoiseLite* fastNoise, bool* neighbor);

	void AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID, bool* faceToRender);

	unsigned int GetVao();
};