#include "World.h"

World::World() 
{
	renderDistance = 50;
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
	float distancePlayerChunk = 0;
	float distX = 0;
	float distY = 0;


	for (size_t i = 0; i < displayChunks.size(); i++)
	{
		distX = std::abs(playerPosition.x - displayChunks[i].midPosition.x);
		distY = std::abs(playerPosition.z - displayChunks[i].midPosition.y);

		distX = std::pow(distX, 2);
		distY = std::pow(distY, 2);

		distancePlayerChunk = std::sqrt(distX + distY);

		
		if (distancePlayerChunk > renderDistance)
		{
			hiddenChunks.push_back(displayChunks[i]);
			displayChunks.erase(displayChunks.begin() + i);		
		}
	}

	//Check hidden chunks
	for (size_t i = 0; i < hiddenChunks.size(); i++)
	{
		distX = std::abs(playerPosition.x - hiddenChunks[i].midPosition.x);
		distY = std::abs(playerPosition.z - hiddenChunks[i].midPosition.y);

		distX = std::pow(distX, 2);
		distY = std::pow(distY, 2);

		distancePlayerChunk = std::sqrt(distX + distY);

		if (distancePlayerChunk < renderDistance)
		{
			displayChunks.push_back(hiddenChunks[i]);
			hiddenChunks.erase(hiddenChunks.begin() + i);
		}
	}
}