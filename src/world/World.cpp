#include "World.h"

World::World() 
{
	renderDistance = 250;
	srand(time(nullptr));
	_fastNoise = new FastNoiseLite(rand());
}

void World::Load() 
{
	for (size_t z = 0; z < 16 * 4; z += ChunkSize::Depth)
	{
		for (size_t x = 0; x < 16 * 4; x += ChunkSize::Width)
		{
			displayChunks.push_back(Chunk(glm::vec3(x, 0, z), _fastNoise));
		}
	}
}

void World::ManageChunk(const glm::vec3& playerPosition)
{
	//Check too far chunks
	for (size_t i = 0; i < displayChunks.size(); i++)
	{	
		if (GetDistanceChunkPlayer(playerPosition, displayChunks[i].midPosition) > renderDistance)
		{
			hiddenChunks.push_back(displayChunks[i]);
			displayChunks.erase(displayChunks.begin() + i);		
		}
	}

	//Check hidden chunks
	for (size_t i = 0; i < hiddenChunks.size(); i++)
	{
		if (GetDistanceChunkPlayer(playerPosition, hiddenChunks[i].midPosition) < renderDistance)
		{
			displayChunks.push_back(hiddenChunks[i]);
			hiddenChunks.erase(hiddenChunks.begin() + i);
		}
	}

	//Create new chunks
	/*
	for (size_t i = 0; i < displayChunks.size(); i++)
	{
		
	}
	*/
}

float World::GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition)
{
	//Approximated distance for heigher performance
	float distX = std::abs(playerPosition.x - chunkPosition.x);
	float distY = std::abs(playerPosition.z - chunkPosition.z);

	return distX + distY;
}