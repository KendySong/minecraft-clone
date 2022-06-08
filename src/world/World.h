///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Manage chunk display, and generate new chunks

#include <vector>
#include <glm/glm.hpp>

#include "Chunk.h"

#pragma once
class World
{
	//Attributes and properties
public :
	float renderDistance;
	std::vector<Chunk> displayChunks;
	std::vector<Chunk> hiddenChunks;

	/// <summary>
	/// Constructor
	/// </summary>
	World();

	/// <summary>
	/// Load the map
	/// </summary>
	void Load();

	void ManageChunk(const glm::vec3& playerPosition);
};