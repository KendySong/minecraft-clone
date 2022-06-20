#include "Tree.h"

Tree::Tree(glm::vec3 position)
{
	/*
		Texture grass("textures/grass.png", 0);
		Texture dirt ("textures/dirt.png",  1);
		Texture sand ("textures/sand.png",  2);
		Texture wood ("textures/wood.png",  3);
		Texture leaf ("textures/leaf.png",  4);
	*/

	_height = 6 ;
	for (size_t i = 1; i < _height + 1; i++)
	{
		treeStruct.push_back(Block(glm::vec3(position.x, position.y + i, position.z), 3));
	}
}

std::vector<Block>& Tree::GetTreeStruct()
{
	return treeStruct;
}