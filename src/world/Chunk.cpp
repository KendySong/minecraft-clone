#include "Chunk.h"

Chunk::Chunk(glm::vec3 position)
{
	cornerPosition = position;

	unsigned int chunkWidthMid = ChunkSize::Width / 2;
	unsigned int chunkDepthMid = ChunkSize::Depth / 2;
	midPosition.x = position.x + chunkWidthMid;
	midPosition.z = position.z + chunkDepthMid;

	//Init height map
	int heightMap[ChunkSize::Width][ChunkSize::Depth];
	for (size_t x = 0; x < ChunkSize::Width; x++)
		for (size_t z = 0; z < ChunkSize::Depth; z++)
			heightMap[x][z] = rand() % 5 + 1;

	//Create 3D array for face check
	bool chunkCoordinate[ChunkSize::Width][ChunkSize::Height][ChunkSize::Depth] = {false}; //False if empty  //True if block
	for (size_t x = 0; x < ChunkSize::Width; x++)
		for (size_t z = 0; z < ChunkSize::Depth; z++)
			for (size_t y = 0; y < heightMap[x][z]; y++)
				chunkCoordinate[x][y][z] = true;

	//Create chunk mesh
	for (size_t x = 0; x < ChunkSize::Width; x++)
	{	
		for (size_t z = 0; z < ChunkSize::Depth; z++)
		{
			for (size_t y = 0; y < heightMap[x][z]; y++)
			{		
				/*
				front	0
				back	1
				right	2
				left	3
				top		4
				bot		5
				*/

				bool faceToRender[6];
		
				if (z == ChunkSize::Depth - 1)
					faceToRender[0] = true;
				else
					faceToRender[0] = !chunkCoordinate[x][y][z + 1];

				if (z == 0)
					faceToRender[1] = true;
				else
					faceToRender[1] = !chunkCoordinate[x][y][z - 1];
					
				if (x == ChunkSize::Width - 1)
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
				
				AddNewBlock(vertex, glm::vec3(x + position.x, y, z + position.z), 0, faceToRender);									
			}
		}
	}

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, false, 24, (const void*)(12));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, false, 24, (const void*)(20));
	glEnableVertexAttribArray(2);

	verticesDraw = vertex.size() / 3;
}

void Chunk::AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID, bool* faceToRender)
{
	//Front
	if (faceToRender[0])
	{
		float frontFace[]
		{
			position.x - 0.5, position.y - 0.5,  position.z + 0.5,  0.25, 0.3333333333,		textureID,
			position.x + 0.5, position.y - 0.5,  position.z + 0.5,  0.5,  0.3333333333,		textureID,
			position.x + 0.5, position.y + 0.5,  position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x + 0.5, position.y + 0.5,  position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x - 0.5, position.y + 0.5,  position.z + 0.5,  0.25, 0.6666666666,		textureID,
			position.x - 0.5, position.y - 0.5,  position.z + 0.5,  0.25, 0.3333333333,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &frontFace[0], &frontFace[std::size(frontFace)]);
	}

	//Back
	if (faceToRender[1])
	{
		float backFace[]
		{
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.3333333333,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,	1.0,  0.6666666666,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,	1.0,  0.3333333333,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,	1.0,  0.6666666666,		textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.3333333333,		textureID,
			position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.75, 0.6666666666,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &backFace[0], &backFace[std::size(backFace)]);
	}

	//Right
	if (faceToRender[2])
	{
		float rightFace[]
		{
			position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.3333333333,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,	0.75, 0.6666666666,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.3333333333,		textureID,
			position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.5,  0.3333333333,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &rightFace[0], &rightFace[std::size(rightFace)]);
	}

	//Left
	if (faceToRender[3])
	{
		float leftFace[]
		{
			position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.6666666666,		textureID,
			position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.0,  0.6666666666,		textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.0,  0.3333333333,		textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.0,  0.3333333333,		textureID,
			position.x - 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.3333333333,		textureID,
			position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.6666666666,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &leftFace[0], &leftFace[std::size(leftFace)]);
	}

	//Top
	if (faceToRender[4])
	{
		float topFace[]
		{			
			position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.25, 1.0,				textureID,
			position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x + 0.5, position.y + 0.5, position.z - 0.5,	0.5,  1.0,				textureID,
			position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.6666666666,		textureID,
			position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.25, 1.0,				textureID,
			position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.6666666666,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &topFace[0], &topFace[std::size(topFace)]);
	}

	//Bot
	if (faceToRender[5])
	{
		float botFace[]
		{
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.5,  0.3333333333,		textureID,
			position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.25, 0.3333333333,		textureID,
			position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.0,				textureID,
			position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.0,				textureID,
			position.x - 0.5, position.y - 0.5, position.z + 0.5,	0.5,  0.0,				textureID,
			position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.5,  0.3333333333,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &botFace[0], &botFace[std::size(botFace)]);
	}
}

unsigned int Chunk::GetVao()
{
	return _vao;
}