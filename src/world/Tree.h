///Author : Kendy Song
///Date : 18.06.2022
///Summary : Generate tree block's position to be added in chunk mesh

#include <vector>

#include <glm/glm.hpp>

#include "Block.h"

#pragma once
class Tree
{
	//Attributes and properties
private :
	std::vector<Block> treeStruct;

public :
	Tree(glm::vec3 position);
	std::vector<Block>& GetTreeStruct();
};