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

	/// <summary>
	/// Check chunk to display, remove or add
	/// </summary>
	/// <param name="playerPosition">Manage chunk depending player position</param>
	void ManageChunk(const glm::vec3& playerPosition);

	/// <summary>
	/// Calculate the approximative distance between the player and the chunk
	/// </summary>
	/// <param name="playerPosition">Position of the player</param>
	/// <param name="chunkPosition">Position of the chunk</param>
	/// <returns>Approximative distance</returns>
	float GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec2 chunkPosition);
};