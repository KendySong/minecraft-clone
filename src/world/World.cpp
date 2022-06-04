#include "World.h"

World::World() 
{
	
}

void World::Load() 
{
	for (size_t y = 0; y < 16 * 3; y+=16)
	{
		for (size_t x = 0; x < 16 * 3; x+=16)
		{
			displayChunks.push_back(Chunk(glm::vec2(x, y)));
		}
	}
}