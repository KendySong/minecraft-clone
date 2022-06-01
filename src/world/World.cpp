#include "World.h"

World::World() 
{
	for (size_t y = 0; y < 3 * 16; y+=16)
	{
		for (size_t x = 0; x < 3 * 16; x+=16)
		{
			displayChunks.push_back(Chunk(glm::vec2(x, y)));
		}
	}
}

void World::ManageChunks() 
{

}