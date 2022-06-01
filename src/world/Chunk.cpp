#include "Chunk.h"

Chunk::Chunk(glm::vec2 position)
{
	_position = position;
	for (int x = position.x; x < position.x + 16; x++)
	{
		for (int z = position.y; z < position.y + 16; z++)
		{
			blocks.push_back(Block(glm::vec3(x, 0, z)));
		}
	}
}