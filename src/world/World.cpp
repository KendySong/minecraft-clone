#include "World.h"

World::World() 
{
	renderDistance = 250;
	srand(time(nullptr));
	_fastNoise = new FastNoiseLite(rand());
	_fastNoise->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S);
	_fastNoise->SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

	_fastNoise->SetFractalLacunarity(2);
	_fastNoise->SetFrequency(0.01);
	_fastNoise->SetFractalOctaves(5);
}

void World::Load() 
{	
	for (size_t z = 0; z < ChunkSize::Depth * 20; z += ChunkSize::Depth)
		for (size_t x = 0; x < ChunkSize::Width * 20; x += ChunkSize::Width)
			displayChunks.push_back(Chunk(glm::vec3(x, 0, z), _fastNoise));
}

void World::ManageChunk(const glm::vec3& playerPosition)
{
	//Check too far chunks
	for (size_t i = 0; i < displayChunks.size(); i++)
	{	
		if (GetDistanceChunkPlayer(playerPosition, displayChunks[i].midPosition) > renderDistance)
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

	//Create new chunks
	/*
	for (size_t i = 0; i < displayChunks.size(); i++)
	{
		
	}
	*/
}

float World::GetDistanceChunkPlayer(glm::vec3 playerPosition, glm::vec3 chunkPosition)
{
	//Approximated distance for heigher performance
	return std::abs(playerPosition.x - chunkPosition.x) + std::abs(playerPosition.z - chunkPosition.z);
}