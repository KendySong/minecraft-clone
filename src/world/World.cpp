#include <chrono>

#include "World.hpp"

World::World() 
{
	renderDistance = 500;
	Random::instance()->setSeed(time(nullptr));
	p_fastNoise = new Perlin();
	/*p_fastNoise = new FastNoiseLite(Random::instance()->fastRand());
	p_fastNoise->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S);
	p_fastNoise->SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
	p_fastNoise->SetFractalLacunarity(2);
	p_fastNoise->SetFrequency(0.008);
	p_fastNoise->SetFractalOctaves(4);*/
}

void World::load() 
{	
	bool firstChunkNeighbor[4] = { false };
	Chunk firstChunk(glm::vec3(0, 0, 0), p_fastNoise, firstChunkNeighbor);
	displayChunks.emplace_back(firstChunk);
	borderMapChunk.emplace_back(firstChunk);
	chunksPositions.emplace_back(firstChunk.cornerPosition);
}

void World::manageChunks(const glm::vec3& playerPosition)
{
	//Check too far chunks
	nearestChunk = &displayChunks[0];
	for (size_t i = 0; i < displayChunks.size(); i++)
	{	
		//Get nearest chunk for create new chunks
		float distance = getDistanceChunkPlayer(playerPosition, displayChunks[i].midPosition);
		if (distance < getDistanceChunkPlayer(playerPosition, nearestChunk->midPosition))
			nearestChunk = &displayChunks[i];

		if (distance > renderDistance)
		{
			hiddenChunks.emplace_back(displayChunks[i]);
			displayChunks.erase(displayChunks.begin() + i);
		}
	}

	//Check hidden chunks
	for (size_t i = 0; i < hiddenChunks.size(); i++)
	{
		if (getDistanceChunkPlayer(playerPosition, hiddenChunks[i].midPosition) < renderDistance)
		{
			displayChunks.emplace_back(hiddenChunks[i]);
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
			northChunkPosition.z -= ChunkGen::DEPTH;
			if (getDistanceChunkPlayer(playerPosition, northChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), northChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, true, false, false };
				Chunk northChunk(northChunkPosition, p_fastNoise, neighbor);

				displayChunks.emplace_back(northChunk);
				borderMapChunk.emplace_back(northChunk);
				chunksPositions.emplace_back(northChunk.cornerPosition);
				borderMapChunk[i].north = true;
			}
		}
		
		if (!borderMapChunk[i].south)
		{
			glm::vec3 southChunkPosition = borderMapChunk[i].cornerPosition;
			southChunkPosition.z += ChunkGen::DEPTH;
			if (getDistanceChunkPlayer(playerPosition, southChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), southChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { true, false, false, false };
				Chunk southChunk(southChunkPosition, p_fastNoise, neighbor);

				displayChunks.emplace_back(southChunk);
				borderMapChunk.emplace_back(southChunk);
				chunksPositions.emplace_back(southChunk.cornerPosition);
				borderMapChunk[i].south = true;
			}
		}
		
		if (!borderMapChunk[i].east)
		{
			glm::vec3 eastChunkPosition = borderMapChunk[i].cornerPosition;
			eastChunkPosition.x += ChunkGen::WIDTH;
			if (getDistanceChunkPlayer(playerPosition, eastChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), eastChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, false, false, true };
				Chunk eastChunk(eastChunkPosition, p_fastNoise, neighbor);

				displayChunks.emplace_back(eastChunk);
				borderMapChunk.emplace_back(eastChunk);
				chunksPositions.emplace_back(eastChunk.cornerPosition);
				borderMapChunk[i].east = true;
			}
		}

		if (!borderMapChunk[i].west)
		{
			glm::vec3 westChunkPosition = borderMapChunk[i].cornerPosition;
			westChunkPosition.x -= ChunkGen::WIDTH;
			if (getDistanceChunkPlayer(playerPosition, westChunkPosition) < renderDistance && std::find(chunksPositions.begin(), chunksPositions.end(), westChunkPosition) == chunksPositions.end())
			{
				bool neighbor[] = { false, false, true, false };
				Chunk westChunk(westChunkPosition, p_fastNoise, neighbor);

				displayChunks.emplace_back(westChunk);
				borderMapChunk.emplace_back(westChunk);
				chunksPositions.emplace_back(westChunk.cornerPosition);
				borderMapChunk[i].west = true;
			}
		}					
	}
}

float World::getDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition)
{
	//Approximated distance for heigher performance
	return std::abs(playerPosition.x - chunkPosition.x) + std::abs(playerPosition.z - chunkPosition.z);
}

Perlin* World::getFastNoise() noexcept
{
	return p_fastNoise;
}