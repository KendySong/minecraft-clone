#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <FastNoiseLite/FastNoiseLite.h>

#include "Tree.hpp"

#pragma once
namespace ChunkGen
{
	const std::uint32_t WIDTH = 16;
	const std::uint32_t HEIGHT = 40;
	const std::uint32_t DEPTH = 16;

	const std::uint32_t SAND_HEIGHT = 5;
	const std::uint32_t WATER_HEIGHT = 4;
}

class Chunk 
{
public :
	bool north;
	bool south;
	bool east;
	bool west;

	glm::vec3 cornerPosition;
	glm::vec3 midPosition;
	std::uint32_t verticesDraw;
	std::vector<glm::vec3> blocks;

	Chunk() = default;
	Chunk(glm::vec3 position, FastNoiseLite* fastNoise, bool* neighbor);
	float getTextureHeight(bool upBlock, size_t height);
	float getHeight(float x, float z);
	
	void generateTree();
	void addNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID, bool* faceToRender);
	std::uint32_t getVao() const noexcept;

private :
	std::uint32_t _vao = 0;
	std::uint32_t _vbo = 0;
	std::vector<float> _vertex;
	FastNoiseLite* _fastNoise;
	void PrepareRender();
};