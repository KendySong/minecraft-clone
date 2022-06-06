///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Contain 16x16x16 block's data

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

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
	unsigned int verticesDraw;
	std::vector<float> vertex;
	std::vector<glm::vec3> blocks;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="position">Position fo the chunk</param>
	Chunk(glm::vec2 position);

	/// <summary>
	/// Add new block into chunk mesh
	/// </summary>
	/// <param name="chunkMesh">Mesh of the chunk to add the block</param>
	/// <param name="position">Position into the mesh</param>
	void AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position);

	/// <summary>
	/// Getter of vao for draw call
	/// </summary>
	/// <returns>Vao of the current chunk</returns>
	unsigned int GetVao();
};