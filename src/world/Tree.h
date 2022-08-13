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
	std::vector<Block> _treeStruct;

public :
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="position">Position of tree (wood block at the bottom)</param>
	Tree(const glm::vec3& position);

	/// <summary>
	/// Allow chunk mesh add the block structure of the tree
	/// </summary>
	/// <returns>Block's data to add into chunk mesh</returns>
	std::vector<Block>& GetTreeStruct();
};