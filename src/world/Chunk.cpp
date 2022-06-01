#include "Chunk.h"

Chunk::Chunk(glm::vec2 position)
{
	_position = position;
	for (int x = position.x; x < position.x + 16; x++)
	{
		for (int z = position.y; z < position.y + 16; z++)
		{
			//Check z
			Block block(glm::vec3(x, 0, z));
			block.indexOffset.push_back(30);


			blocks.push_back(block);
		}
	}

	//0		FRONT
	//6		BACK
	//12	RIGHT
	//18	LEFT
	//26	TOP
	//30	BOT
}