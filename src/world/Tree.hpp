#include <vector>

#include <glm/glm.hpp>

#include "Block.hpp"

#pragma once
class Tree
{
private :
	std::vector<Block> _treeStruct;

public :
	Tree(const glm::vec3& position);
	std::vector<Block>& getTreeStruct();
};