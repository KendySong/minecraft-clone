#include "Chunk.h"

Chunk::Chunk(glm::vec3 position)
{
	cornerPosition = position;

	unsigned int chunkWidthMid = ChunkSize::Width / 2;
	unsigned int chunkDepthMid = ChunkSize::Depth / 2;
	midPosition.x = position.x + chunkWidthMid;
	midPosition.z = position.z + chunkDepthMid;

	//Create chunk mesh
	for (size_t x = 0; x < ChunkSize::Width; x++)
	{	
		for (size_t z = 0; z < ChunkSize::Depth; z++)
		{
			for (size_t y = 0; y < ChunkSize::Height; y++)
			{
				if (y == ChunkSize::Height - 1)
				{
					AddNewBlock(vertex, glm::vec3(x + position.x, y, z + position.z), 0);
				}
				else 
				{
					AddNewBlock(vertex, glm::vec3(x + position.x, y, z + position.z), 1);
				}
			}
		}
	}

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 6, (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(float) * 6, (const void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	verticesDraw = vertex.size() / 3;
}

void Chunk::AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position, float textureID)
{
	float blockVertex[]
	{
		//Front													//Texture map
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,  0.25, 0.333333,		textureID,
		position.x + 0.5, position.y - 0.5,  position.z + 0.5,  0.5,  0.333333,		textureID,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x - 0.5, position.y + 0.5,  position.z + 0.5,  0.25, 0.666666,		textureID,
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,  0.25, 0.333333,		textureID,

		//Back
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.333333,		textureID,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,	1.0,  0.666666,		textureID,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,	1.0,  0.333333,		textureID,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,	1.0,  0.666666,		textureID,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.333333,		textureID,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.75, 0.666666,		textureID,

		//Right
		position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.333333,		textureID,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,	0.75, 0.666666,		textureID,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.75, 0.333333,		textureID,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.5,  0.333333,		textureID,

		//Left
		position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.666666,		textureID,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.0,  0.666666,		textureID,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.0,  0.333333,		textureID,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.0,  0.333333,		textureID,
		position.x - 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.333333,		textureID,
		position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.666666,		textureID,
		
		//Top
		position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.25, 1.0,			textureID,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,	0.5,  1.0,			textureID,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,	0.5,  0.666666,		textureID,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,	0.25, 1.0,			textureID,
		position.x - 0.5, position.y + 0.5, position.z + 0.5,	0.25, 0.666666,		textureID,

		//Down
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.5,  0.333333,		textureID,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,	0.25, 0.333333,		textureID,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.0,			textureID,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,	0.25, 0.0,			textureID,
		position.x - 0.5, position.y - 0.5, position.z + 0.5,	0.5,  0.0,			textureID,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,	0.5,  0.333333,		textureID	
	};	

	chunkMesh.insert(chunkMesh.end(), &blockVertex[0], &blockVertex[std::size(blockVertex)]);
}

unsigned int Chunk::GetVao()
{
	return _vao;
}