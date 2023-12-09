#include <algorithm>
#include <vector>

#include <glm/glm.hpp>
#include <FastNoiseLite/FastNoiseLite.h>
#include "Perlin.hpp"

#include "Chunk.hpp"
#include "../application/Random.hpp"

#pragma once
class World
{
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
	Perlin* getFastNoise() noexcept;

private :
	Perlin* p_fastNoise;
};