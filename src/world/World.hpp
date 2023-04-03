///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Manage chunk display, and generate new chunks

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>
#include <FastNoiseLite/FastNoiseLite.h>

#include "Chunk.hpp"
#include "../application/Random.hpp"

#pragma once
class World
{
private :
	FastNoiseLite* _fastNoise;

	//Attributes and properties
public :
	Chunk* nearestChunk;
	float renderDistance;
	std::vector<glm::vec3> chunksPositions;
	std::vector<Chunk> borderMapChunk;
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
	void ManageChunks(const glm::vec3& playerPosition);

	/// <summary>
	/// Calculate the approximative distance between the player and the chunk
	/// </summary>
	/// <param name="playerPosition">Position of the player</param>
	/// <param name="chunkPosition">Position of the chunk</param>
	/// <returns>Approximative distance</returns>
	float GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition);
};