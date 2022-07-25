///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain blocks position and create terrain

#include <chrono>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <FastNoiseLite/FastNoiseLite.h>

#include "../application/Random.h"
#include "Tree.h"

#pragma once
namespace ChunkGen
{
	const unsigned int WIDTH = 16;
	const unsigned int HEIGHT = 40;
	const unsigned int DEPTH = 16;

	const unsigned int SAND_HEIGHT = 5;
	const unsigned int WATER_HEIGHT = 4;
}

class Chunk 
{
	//Attributes and properties
private :
	unsigned int _vao = 0;
	unsigned int _vbo = 0;
	std::vector<float> _vertex;
	FastNoiseLite* _fastNoise;

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

	/// <summary>
	/// Constructor
	/// </summary>
	Chunk();

	/// <summary>
	/// Return texture id depending the height of the block
	/// </summary>
	/// <param name="upBlock">If there is a block on the top</param>
	/// <param name="height">Height of the current block</param>
	/// <returns>Texture ID</returns>
	float GetTextureHeight(bool upBlock, size_t height);

	/// <summary>
	/// Get the height of the map at the position
	/// </summary>
	/// <param name="x">Horizontal position</param>
	/// <param name="z">Depth position</param>
	/// <returns>Height</returns>
	float GetHeight(float x, float z);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="position">Position of the chunk (block in the corner)</param>
	/// <param name="fastNoise">Map generator</param>
	/// <param name="neighbor">Array of bool that contain existance of neighbor</param>
	Chunk(const glm::vec3& position, FastNoiseLite* fastNoise, bool* neighbor);

	/// <summary>
	/// Generate tree in the current chunk
	/// </summary>
	void GenerateTree();

	/// <summary>
	/// Add a block in the chunk mesh
	/// </summary>
	/// <param name="chunkMesh">Chunk vertices</param>
	/// <param name="position">Posiion of block</param>
	/// <param name="textureID">Texture of block for render</param>
	/// <param name="faceToRender">Direction of faces to render</param>
	void AddNewBlock(std::vector<float>& chunkMesh, const glm::vec3& position, float textureID, bool* faceToRender);

	/// <summary>
	/// Getter of vao for bind and draw
	/// </summary>
	/// <returns>Vao of the chunk</returns>
	unsigned int GetVao();
};