#include "Chunk.hpp"
#include "../application/Random.hpp"

float Chunk::getTextureHeight(bool upBlock, size_t height)
{
	/*
		Texture grass("textures/grass.png", 0);
		Texture dirt ("textures/dirt.png",  1);
		Texture sand ("textures/sand.png",  2);
		Texture wood ("textures/wood.png",  3);
		Texture leaf ("textures/leaf.png",  4);
		Texture water("textures/water.png", 5);
	*/
	
	float texID = 1;
	if (!upBlock)
		texID = 0;

	if (height < ChunkGen::SAND_HEIGHT)
		texID = 2;

	return texID;	
}

float Chunk::getHeight(float x, float z)
{
	float height = _fastNoise->noise2D(Vec2(x, z));
	height = std::abs(height) * 25;
	height++;
	return height;
}

Chunk::Chunk(glm::vec3 position, Perlin* fastNoise, bool* neighbor)
{
	north = neighbor[0];
	south = neighbor[1];
	east  = neighbor[2];
	west  = neighbor[3];

	cornerPosition = position;
	_fastNoise = fastNoise;

	std::uint32_t chunkWidthMid = ChunkGen::WIDTH / 2;
	std::uint32_t chunkDepthMid = ChunkGen::DEPTH / 2;
	midPosition.x = position.x + chunkWidthMid;
	midPosition.z = position.z + chunkDepthMid;
	
	//Generate heightmap
	float heightMap[ChunkGen::WIDTH][ChunkGen::DEPTH];
	for (size_t x = 0; x < ChunkGen::WIDTH; x++)
		for (size_t z = 0; z < ChunkGen::DEPTH; z++)
			heightMap[x][z] = getHeight(x + position.x, z + position.z);

	//Create 3D array for face check
	bool chunkCoordinate[ChunkGen::WIDTH][ChunkGen::HEIGHT][ChunkGen::DEPTH] = {false}; //False => Empty
	for (size_t x = 0; x < ChunkGen::WIDTH; x++)
	{
		for (size_t z = 0; z < ChunkGen::DEPTH; z++)
		{
			for (size_t y = 0; y < heightMap[x][z]; y++)
			{
				chunkCoordinate[x][y][z] = true;
			}
		}
	}

	//Create chunk mesh
	for (size_t x = 0; x < ChunkGen::WIDTH; x++)
	{
		for (size_t z = 0; z < ChunkGen::DEPTH; z++)
		{
			for (size_t y = 0; y < heightMap[x][z]; y++)
			{		
				bool faceToRender[6];

				if (z == ChunkGen::DEPTH - 1)
				{
					if (y > getHeight(x + position.x, z + position.z + 1))
					{
						faceToRender[0] = true;
					}
					else 
					{
						faceToRender[0] = false;
					}
				}
				else
				{
					faceToRender[0] = !chunkCoordinate[x][y][z + 1];	
				}

				if (z == 0)
				{
					if (y > getHeight(x + position.x, z + position.z - 1))
					{
						faceToRender[1] = true;
					}
					else 
					{
						faceToRender[1] = false;
					}
				}
				else
				{
					faceToRender[1] = !chunkCoordinate[x][y][z - 1];
				}
				
				if (x == ChunkGen::WIDTH - 1)
				{
					if (y > getHeight(x + position.x + 1, z + position.z))
					{
						faceToRender[2] = true;
					}
					else 
					{
						faceToRender[2] = false;
					}
				}
				else 
				{
					faceToRender[2] = !chunkCoordinate[x + 1][y][z];
				}

				if (x == 0)
				{			
					if (y > getHeight(x + position.x - 1, z + position.z))
					{
						faceToRender[3] = true;
					}
					else 
					{
						faceToRender[3] = false;
					}
				}
				else
				{
					faceToRender[3] = !chunkCoordinate[x - 1][y][z];
				}		

				if (y == heightMap[x][z] - 1)
				{
					faceToRender[4] = true;
				}
				else
				{
					faceToRender[4] = !chunkCoordinate[x][y + 1][z];
				}

				if (y == 0)
				{
					faceToRender[5] = true;
				}
				else
				{
					faceToRender[5] = !chunkCoordinate[x][y - 1][z];
				}

				//Set texture			
				addNewBlock
				(
					_vertex, 
					glm::vec3(x + position.x, y, z + position.z), 
					getTextureHeight(chunkCoordinate[x][y + 1][z], y),
					faceToRender
				);
				
				//Add water
				if (heightMap[x][z] < ChunkGen::WATER_HEIGHT)
				{
					faceToRender[5] = false;

					for (size_t i = heightMap[x][z]; i < ChunkGen::WATER_HEIGHT; i++)
					{
						if (i == ChunkGen::WATER_HEIGHT - 1)
							faceToRender[4] = true;
						else
							faceToRender[4] = false;

						addNewBlock
						(
							_vertex,
							glm::vec3(x + position.x, i, z + position.z),
							5,
							faceToRender
						);
					}
				}
			}
		}
	}

	generateTree();
	PrepareRender();
}

void Chunk::generateTree()
{
	//Tree position
	int xPos = Random::instance()->fastRand() % ChunkGen::WIDTH;
	int zPos = Random::instance()->fastRand() % ChunkGen::DEPTH;
	xPos += cornerPosition.x;
	zPos += cornerPosition.z;

	int positionHeight = (int)getHeight(xPos, zPos);
	if (positionHeight > ChunkGen::SAND_HEIGHT)
	{
		//Generate a tree
		Tree tree(glm::vec3(xPos, (int)getHeight(xPos, zPos), zPos));
		std::vector<Block> treeBlock = tree.getTreeStruct();
		bool treeFace[] = { true };

		for (size_t i = 0; i < treeBlock.size(); i++)
		{
			addNewBlock(_vertex, treeBlock[i].getPosition(), treeBlock[i].getTextureID(), treeFace);
		}
	}
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

void Chunk::addNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID, bool* faceToRender) 
{
	//Front
	if (faceToRender[0])
	{
		float frontFace[]
		{
			position.x - 0.5f, position.y - 0.5f,  position.z + 0.5f,		0.375, 0,		0.0, 0.0, 1.0,		textureID,
			position.x + 0.5f, position.y - 0.5f,  position.z + 0.5f,		0.625, 0,		0.0, 0.0, 1.0,		textureID,
			position.x + 0.5f, position.y + 0.5f,  position.z + 0.5f,		0.625, 1,		0.0, 0.0, 1.0,		textureID,

			position.x + 0.5f, position.y + 0.5f,  position.z + 0.5f,		0.625, 1,		0.0, 0.0, 1.0,		textureID,
			position.x - 0.5f, position.y + 0.5f,  position.z + 0.5f,		0.375, 1,		0.0, 0.0, 1.0,		textureID,
			position.x - 0.5f, position.y - 0.5f,  position.z + 0.5f,		0.375, 0,		0.0, 0.0, 1.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &frontFace[0], &frontFace[sizeof(frontFace) / sizeof(float)]);
	}	
	
	//Back
	if (faceToRender[1])
	{
		float backFace[]
		{
			position.x - 0.5f, position.y - 0.5f,	position.z - 0.5f,		0.625, 0,		0.0, 0.0, -1.0,		textureID,
			position.x + 0.5f, position.y + 0.5f,	position.z - 0.5f,		0.375, 1,		0.0, 0.0, -1.0,		textureID,
			position.x + 0.5f, position.y - 0.5f,	position.z - 0.5f,		0.375, 0,		0.0, 0.0, -1.0,		textureID,

			position.x + 0.5f, position.y + 0.5f,	position.z - 0.5f,		0.375, 1,		0.0, 0.0, -1.0,		textureID,
			position.x - 0.5f, position.y - 0.5f,	position.z - 0.5f,		0.625, 0,		0.0, 0.0, -1.0,		textureID,
			position.x - 0.5f, position.y + 0.5f,	position.z - 0.5f,		0.625, 1,		0.0, 0.0, -1.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &backFace[0], &backFace[sizeof(backFace) / sizeof(float)]);
	}
	
	//Right
	if (faceToRender[2])
	{
		float rightFace[]
		{
			position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,		0.375, 1,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,		0.625, 0,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,		0.625, 1,		1.0, 0.0, 0.0,		textureID,

			position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,		0.625, 0,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,		0.375, 1,		1.0, 0.0, 0.0,		textureID,
			position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,		0.375, 0,		1.0, 0.0, 0.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &rightFace[0], &rightFace[sizeof(rightFace) / sizeof(float)]);
	}
	
	//Left
	if (faceToRender[3])
	{
		float leftFace[]
		{
			position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,		0.625, 1,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,		0.375, 1,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,		0.375, 0,		-1.0, 0.0, 0.0,		textureID,

			position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,		0.375, 0,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,		0.625, 0,		-1.0, 0.0, 0.0,		textureID,
			position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,		0.625, 1,		-1.0, 0.0, 0.0,		textureID
		};
		chunkMesh.insert(chunkMesh.end(), &leftFace[0], &leftFace[sizeof(leftFace) / sizeof(float)]);
	}
	
	//Top
	if (faceToRender[4])
	{
		float topFace[]
		{
			position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,		0.0625, 0,		0.0, 1.0, 0.0,		textureID,
			position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,		0.3125, 1,		0.0, 1.0, 0.0,		textureID,
			position.x + 0.5f, position.y + 0.5f, position.z - 0.5f,		0.3125, 0,		0.0, 1.0, 0.0,		textureID,

			position.x + 0.5f, position.y + 0.5f, position.z + 0.5f,		0.3125, 1,		0.0, 1.0, 0.0,		textureID,
			position.x - 0.5f, position.y + 0.5f, position.z - 0.5f,		0.0625, 0,		0.0, 1.0, 0.0,		textureID,
			position.x - 0.5f, position.y + 0.5f, position.z + 0.5f,		0.0625, 1,		0.0, 1.0, 0.0,		textureID			
		};
		chunkMesh.insert(chunkMesh.end(), &topFace[0], &topFace[sizeof(topFace) / sizeof(float)]);
	}

	//Bot
	if (faceToRender[5])
	{
		float botFace[]
		{
			position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,		0.6875, 0,		0.0, -1.0, 0.0,		textureID,
			position.x + 0.5f, position.y - 0.5f, position.z - 0.5f,		0.9375, 0,		0.0, -1.0, 0.0,		textureID,
			position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,		0.9375, 1,		0.0, -1.0, 0.0,		textureID,

			position.x + 0.5f, position.y - 0.5f, position.z + 0.5f,		0.9375, 1,		0.0, -1.0, 0.0,		textureID,
			position.x - 0.5f, position.y - 0.5f, position.z + 0.5f,		0.6875, 1,		0.0, -1.0, 0.0,		textureID,
			position.x - 0.5f, position.y - 0.5f, position.z - 0.5f,		0.6875, 0,		0.0, -1.0, 0.0,		textureID	
		};
		chunkMesh.insert(chunkMesh.end(), &botFace[0], &botFace[sizeof(botFace) / sizeof(float)]);
	}
}

std::uint32_t Chunk::getVao() const noexcept
{
	return _vao;
}