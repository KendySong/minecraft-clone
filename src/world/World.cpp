#include "World.h"

World::World() 
{
	renderDistance = 100;
	srand(time(nullptr));
	_fastNoise = new FastNoiseLite(rand());
	_fastNoise->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S);
	_fastNoise->SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

	_fastNoise->SetFractalLacunarity(2);
	_fastNoise->SetFrequency(0.008);
	_fastNoise->SetFractalOctaves(4);
}

void World::Load() 
{	
	bool firstChunkNeighbor[] = {false, false, false, false};

	Chunk firstChunk(glm::vec3(0, 0, 0), _fastNoise, firstChunkNeighbor);
	displayChunks.push_back(firstChunk);
	borderMapChunk.push_back(firstChunk);
	chunksPositions.push_back(firstChunk.cornerPosition);
}

void World::ManageChunks(const glm::vec3& playerPosition)
{
	//Check too far chunks
	nearestChunk = &displayChunks[0];
	for (size_t i = 0; i < displayChunks.size(); i++)
	{	
		//Get nearest chunk for create new chunks
		float distance = GetDistanceChunkPlayer(playerPosition, displayChunks[i].midPosition);
		if (distance < GetDistanceChunkPlayer(playerPosition, nearestChunk->midPosition))
			nearestChunk = &displayChunks[i];

		if (distance > renderDistance)
		{
			hiddenChunks.push_back(displayChunks[i]);
			displayChunks.erase(displayChunks.begin() + i);
		}
	}

	//Check hidden chunks
	for (size_t i = 0; i < hiddenChunks.size(); i++)
	{
		if (GetDistanceChunkPlayer(playerPosition, hiddenChunks[i].midPosition) < renderDistance)
		{
			displayChunks.push_back(hiddenChunks[i]);
			hiddenChunks.erase(hiddenChunks.begin() + i);
		}
	}
	
	//Create new chunks (north => 0 | south => 1 | east => 2 | west => 3) 
	//false => empty neighbor | true => neighbor exist
	for (size_t i = 0; i < borderMapChunk.size(); i++)
	{
		if (borderMapChunk[i].north && borderMapChunk[i].south && borderMapChunk[i].east && borderMapChunk[i].west)
		{
			borderMapChunk.erase(borderMapChunk.begin() + i);
			chunksPositions.erase(chunksPositions.begin() + i);
			break;
		}
			
		if (!borderMapChunk[i].north)
		{
			glm::vec3 northChunkPosition = borderMapChunk[i].cornerPosition;
			northChunkPosition.z -= ChunkSize::DEPTH;
			if (GetDistanceChunkPlayer(playerPosition, northChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), northChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, true, false, false };
				Chunk northChunk(northChunkPosition, _fastNoise, neighbor);

				displayChunks.push_back(northChunk);
				borderMapChunk.push_back(northChunk);
				chunksPositions.push_back(northChunk.cornerPosition);
				borderMapChunk[i].north = true;
			}
		}
		
		if (!borderMapChunk[i].south)
		{
			glm::vec3 southChunkPosition = borderMapChunk[i].cornerPosition;
			southChunkPosition.z += ChunkSize::DEPTH;
			if (GetDistanceChunkPlayer(playerPosition, southChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), southChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { true, false, false, false };
				Chunk southChunk(southChunkPosition, _fastNoise, neighbor);

				displayChunks.push_back(southChunk);
				borderMapChunk.push_back(southChunk);
				chunksPositions.push_back(southChunk.cornerPosition);
				borderMapChunk[i].south = true;
			}
		}
		
		if (!borderMapChunk[i].east)
		{
			glm::vec3 eastChunkPosition = borderMapChunk[i].cornerPosition;
			eastChunkPosition.x += ChunkSize::WIDTH;
			if (GetDistanceChunkPlayer(playerPosition, eastChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), eastChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, false, false, true };
				Chunk eastChunk(eastChunkPosition, _fastNoise, neighbor);

				displayChunks.push_back(eastChunk);
				borderMapChunk.push_back(eastChunk);
				chunksPositions.push_back(eastChunk.cornerPosition);
				borderMapChunk[i].east = true;
			}
		}

		if (!borderMapChunk[i].west)
		{
			glm::vec3 westChunkPosition = borderMapChunk[i].cornerPosition;
			westChunkPosition.x -= ChunkSize::WIDTH;
			if (GetDistanceChunkPlayer(playerPosition, westChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), westChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, false, true, false };
				Chunk westChunk(westChunkPosition, _fastNoise, neighbor);

				displayChunks.push_back(westChunk);
				borderMapChunk.push_back(westChunk);
				chunksPositions.push_back(westChunk.cornerPosition);
				borderMapChunk[i].west = true;
			}
		}					
	}
}

float World::GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition)
{
	//Approximated distance for heigher performance
	return std::abs(playerPosition.x - chunkPosition.x) + std::abs(playerPosition.z - chunkPosition.z);
}