#include "Tree.hpp"

Tree::Tree(const glm::vec3& position)
{
	/*
		Texture grass("textures/grass.png", 0);
		Texture dirt ("textures/dirt.png",  1);
		Texture sand ("textures/sand.png",  2);
		Texture wood ("textures/wood.png",  3);
		Texture leaf ("textures/leaf.png",  4);
	*/

	std::uint32_t woodHeight = 5 + 1;
	std::uint32_t leafHeight = 4;
	std::uint32_t leafSize = 5;

	//Wood
	_treeStruct.reserve(woodHeight + (leafSize * leafSize * leafHeight) - 16);
	for (size_t i = 1; i < woodHeight; i++)	
		_treeStruct.emplace_back(Block(glm::vec3(position.x, position.y + i, position.z), 3));
	

	for (size_t x = 0; x < leafSize; x++)
	{
		for (size_t z = 0; z < leafSize; z++)
		{
			for (size_t y = 0; y < leafHeight; y++)
			{
				if (!(y == leafHeight - 1 && (x == 0 || x == leafSize - 1 || z == 0 || z == leafSize - 1)))
				{
					_treeStruct.emplace_back(Block(glm::vec3(position.x + x - leafSize / 2, position.y + woodHeight + y, position.z + z - leafSize / 2), 4));
				}
			}	
		}
	}
}

std::vector<Block>& Tree::getTreeStruct()
{
	return _treeStruct;
}