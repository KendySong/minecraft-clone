#include "Chunk.h"

Chunk::Chunk() 
{

}

Chunk::Chunk(glm::vec3 position, FastNoiseLite* fastNoise, bool* neighbor)
{
	north = neighbor[0];
	south = neighbor[1];
	east  = neighbor[2];
	west  = neighbor[3];

	cornerPosition = position;

	unsigned int chunkWidthMid = ChunkSize::WIDTH / 2;
	unsigned int chunkDepthMid = ChunkSize::DEPTH / 2;
	midPosition.x = position.x + chunkWidthMid;
	midPosition.z = position.z + chunkDepthMid;
	
	//Generate heightmap
	float heightMap[ChunkSize::WIDTH][ChunkSize::DEPTH];
	for (size_t x = 0; x < ChunkSize::WIDTH; x++)
	{
		for (size_t z = 0; z < ChunkSize::DEPTH; z++)
		{
			heightMap[x][z] = fastNoise->GetNoise((float)x + position.x, (float)z + position.z);
			heightMap[x][z] = std::abs(heightMap[x][z]) * 40;
			heightMap[x][z]++;
		}
	}

	//Create 3D array for face check
	bool chunkCoordinate[ChunkSize::WIDTH][ChunkSize::HEIGHT][ChunkSize::DEPTH] = {false}; //False => Empty
	for (size_t x = 0; x < ChunkSize::WIDTH; x++)
		for (size_t z = 0; z < ChunkSize::DEPTH; z++)
			for (size_t y = 0; y < heightMap[x][z]; y++)
				chunkCoordinate[x][y][z] = true;

	//Create chunk mesh
	for (size_t x = 0; x < ChunkSize::WIDTH; x++)
	{	
		for (size_t z = 0; z < ChunkSize::DEPTH; z++)
		{
			for (size_t y = 0; y < heightMap[x][z]; y++)
			{
				/*
				Texture grass("textures/grass.png", 0);
				Texture dirt ("textures/dirt.png",  1);
				Texture sand ("textures/sand.png",  2);
				Texture wood ("textures/wood.png",  3);

				*/

				float textureID = 1;
				bool faceToRender[6];

				//Set block texture
				if (!chunkCoordinate[x][y + 1][z])
					textureID = 0;

				if (y < 4)
					textureID = 2;					

				//Check face to render
				if (z == ChunkSize::DEPTH - 1)
					faceToRender[0] = true;
				else
					faceToRender[0] = !chunkCoordinate[x][y][z + 1];	

				if (z == 0)
					faceToRender[1] = true;
				else
					faceToRender[1] = !chunkCoordinate[x][y][z - 1];
					
				if (x == ChunkSize::WIDTH - 1)
					faceToRender[2] = true;
				else
					faceToRender[2] = !chunkCoordinate[x + 1][y][z];

				if (x == 0)
					faceToRender[3] = true;
				else
					faceToRender[3] = !chunkCoordinate[x - 1][y][z];
				
				if (y == heightMap[x][z] - 1)
					faceToRender[4] = true;
				else
					faceToRender[4] = !chunkCoordinate[x][y + 1][z];

				if (y == 0)
					faceToRender[5] = true;
				else
					faceToRender[5] = !chunkCoordinate[x][y - 1][z];			

				//Set texture			
				AddNewBlock(_vertex, glm::vec3(x + position.x, y, z + position.z), textureID, faceToRender);
			}
		}
	}

	
	//Generate a tree
	bool faceToRender[] = {true};
	for (size_t i = 25; i < 30; i++)
	{
		AddNewBlock(_vertex, glm::vec3(midPosition.x, i, midPosition.z), 3, faceToRender);
	}
	

	PrepareRender();
}

void Chunk::PrepareRender() 
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex.size(), &_vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 36, (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, false, 36, (const void*)(12));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, false, 36, (const void*)(20));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, false, 36, (const void*)(32));
	glEnableVertexAttribArray(3);

	verticesDraw = _vertex.size() / 3;
	_vertex.clear();
}

void Chunk::AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID, bool* faceToRender)
{
	//Front
	if (faceToRender[0])
	{
		float frontFace[]
		{
			position.x - 0.5, position.y - 0.5,  position.z + 0.5,		0.375, 0,		0.0, 0.0, 1.0,		textureID,
			position.x + 0.5, position.y - 0.5,  position.z + 0.5,		0.625, 0,		0.0, 0.0, 1.0,		textureID,
			position.x + 0.5, position.y + 0.5,  position.z + 0.5,		0.625, 1,		0.0, 0.0, 1.0,		textureID,

			position.x + 0.5, position.y + 0.5,  position.z + 0.5,		0.625, 1,		0.0, 0.0, 1.0,		textureID,
			position.x - 0.5, position.y + 0.5,  position.z + 0.5,		0.375, 1,		0.0, 0.0, 1.0,		textureID,
			position.x - 0.5, position.y - 0.5,  position.z + 0.5,		0.375, 0,		0.0, 0.0, 1.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &frontFace[0], &frontFace[std::size(frontFace)]);
	}	
	
	//Back
	if (faceToRender[1])
	{
		float backFace[]
		{
			position.x - 0.5, position.y - 0.5,	position.z - 0.5,		0.625, 0,		0.0, 0.0, -1.0,		textureID,
			position.x + 0.5, position.y + 0.5,	position.z - 0.5,		0.375, 1,		0.0, 0.0, -1.0,		textureID,
			position.x + 0.5, position.y - 0.5,	position.z - 0.5,		0.375, 0,		0.0, 0.0, -1.0,		textureID,

			position.x + 0.5, position.y + 0.5,	position.z - 0.5,		0.375, 1,		0.0, 0.0, -1.0,		textureID,
			position.x - 0.5, position.y - 0.5,	position.z - 0.5,		0.625, 0,		0.0, 0.0, -1.0,		textureID,
			position.x - 0.5, position.y + 0.5,	position.z - 0.5,		0.625, 1,		0.0, 0.0, -1.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &backFace[0], &backFace[std::size(backFace)]);
	}
	
	//Right
	if (faceToRender[2])
	{
		float rightFace[]
		{
			position.x + 0.5, position.y + 0.5, position.z + 0.5,		0.375, 1,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,		0.625, 0,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,		0.625, 1,		1.0, 0.0, 0.0,		textureID,

			position.x + 0.5, position.y - 0.5, position.z - 0.5,		0.625, 0,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5, position.y + 0.5, position.z + 0.5,		0.375, 1,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5, position.y - 0.5, position.z + 0.5,		0.375, 0,		1.0, 0.0, 0.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &rightFace[0], &rightFace[std::size(rightFace)]);
	}
	
	//Left
	if (faceToRender[3])
	{
		float leftFace[]
		{
			position.x - 0.5, position.y + 0.5, position.z + 0.5,		0.625, 1,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5, position.y + 0.5, position.z - 0.5,		0.375, 1,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,		0.375, 0,		-1.0, 0.0, 0.0,		textureID,

			position.x - 0.5, position.y - 0.5, position.z - 0.5,		0.375, 0,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5, position.y - 0.5, position.z + 0.5,		0.625, 0,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5, position.y + 0.5, position.z + 0.5,		0.625, 1,		-1.0, 0.0, 0.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &leftFace[0], &leftFace[std::size(leftFace)]);
	}
	
	//Top
	if (faceToRender[4])
	{
		float topFace[]
		{
			position.x - 0.5, position.y + 0.5, position.z - 0.5,		0.0625, 0,		0.0, 1.0, 0.0,		textureID,
			position.x + 0.5, position.y + 0.5, position.z + 0.5,		0.3125, 1,		0.0, 1.0, 0.0,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,		0.3125, 0,		0.0, 1.0, 0.0,		textureID,

			position.x + 0.5, position.y + 0.5, position.z + 0.5,		0.3125, 1,		0.0, 1.0, 0.0,		textureID,
			position.x - 0.5, position.y + 0.5, position.z - 0.5,		0.0625, 0,		0.0, 1.0, 0.0,		textureID,
			position.x - 0.5, position.y + 0.5, position.z + 0.5,		0.0625, 1,		0.0, 1.0, 0.0,		textureID			
		};
		chunkMesh.insert(chunkMesh.end(), &topFace[0], &topFace[std::size(topFace)]);
	}

	//Bot
	if (faceToRender[5])
	{
		float botFace[]
		{
			position.x - 0.5, position.y - 0.5, position.z - 0.5,		0.6875, 0,		0.0, -1.0, 0.0,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,		0.9375, 0,		0.0, -1.0, 0.0,		textureID,
			position.x + 0.5, position.y - 0.5, position.z + 0.5,		0.9375, 1,		0.0, -1.0, 0.0,		textureID,

			position.x + 0.5, position.y - 0.5, position.z + 0.5,		0.9375, 1,		0.0, -1.0, 0.0,		textureID,
			position.x - 0.5, position.y - 0.5, position.z + 0.5,		0.6875, 1,		0.0, -1.0, 0.0,		textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,		0.6875, 0,		0.0, -1.0, 0.0,		textureID	
		};
		chunkMesh.insert(chunkMesh.end(), &botFace[0], &botFace[std::size(botFace)]);
	}
}

unsigned int Chunk::GetVao()
{
	return _vao;
}