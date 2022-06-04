///Author : kndysong@gmail.com
///Date : 31.05.2022
///Summary : Manage chunk display, and generate new chunks

#include <vector>

#include "Chunk.h"

#pragma once
class World
{
	//Attributes and properties
public :
	std::vector<Chunk> displayChunks;

	/// <summary>
	/// Constructor
	/// </summary>
	World();

	/// <summary>
	/// Load the map
	/// </summary>
	void Load();
};