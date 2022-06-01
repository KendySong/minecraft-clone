#include "Chunk.h"

Chunk::Chunk(glm::vec2 position)
{
	int height = 2;
	_position = position;
	for (int x = position.x; x < position.x + 16; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int z = position.y; z < position.y + 16; z++)
			{				
				Block block(glm::vec3(x, y, z));
				
				if (y == height - 1)				
					block.indexOffset.push_back(24);
				
				if (x == 0)				
					block.indexOffset.push_back(18);				

				if (x == position.x + 15)				
					block.indexOffset.push_back(12);				

				if (z == 0)				
					block.indexOffset.push_back(6);								

				if (z == position.y + 15)				
					block.indexOffset.push_back(0);		
	
				blocks.push_back(block);
			}
		}
	
	}

	//0		FRONT
	//6		BACK
	//12	RIGHT	
	//18	LEFT	
	//24	TOP		OK
	//30	BOT		OK
}