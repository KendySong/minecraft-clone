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
	FastNoiseLite* p_fastNoise;

public :
	Chunk* nearestChunk;
	float renderDistance;
	std::vector<glm::vec3> chunksPositions;
	std::vector<Chunk> borderMapChunk;
	std::vector<Chunk> displayChunks;
	std::vector<Chunk> hiddenChunks;

	World();

	void load();
	void manageChunks(const glm::vec3& playerPosition);
	float getDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition);
};