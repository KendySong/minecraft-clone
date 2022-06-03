#include "World.h"

World::World() 
{
	
}

void World::Load() 
{
	displayChunks.push_back(Chunk(glm::vec2(0, 0)));
	//displayChunks.push_back(Chunk(glm::vec2(20, 20)));
}