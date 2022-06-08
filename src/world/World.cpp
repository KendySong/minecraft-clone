#include "World.h"

World::World() 
{
	renderDistance = 250;
}

void World::Load() 
{
	for (size_t y = 0; y < 16 * 3; y += ChunkSize::Depth)
	{
		for (size_t x = 0; x < 16 * 3; x += ChunkSize::Width)
		{
			displayChunks.push_back(Chunk(glm::vec2(x, y)));
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

}

float World::GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec2 chunkPosition)
{
	//Approximated distance for heigher performance
	float distX = std::abs(playerPosition.x - chunkPosition.x);
	float distY = std::abs(playerPosition.z - chunkPosition.y);

	return distX + distY;
}