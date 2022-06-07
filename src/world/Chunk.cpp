#include "Chunk.h"

Chunk::Chunk(glm::vec2 position)
{
	for (size_t x = 0; x < ChunkSize::Width; x++)
	{
		for (size_t y = 0; y < ChunkSize::Height; y++)
		{
			for (size_t z = 0; z < ChunkSize::Depth; z++)
			{
				AddNewBlock(vertex, glm::vec3(x + position.x, y, z + position.y));
			}
		}
	}

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	verticesDraw = vertex.size() / 3;
}

void Chunk::AddNewBlock(std::vector<float>& chunkMesh, glm::vec3 position)
{
	float blockVertex[]
	{
		//Front
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,
		position.x + 0.5, position.y - 0.5,  position.z + 0.5,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,
		position.x - 0.5, position.y + 0.5,  position.z + 0.5,
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,

		//Back
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,

		//Right
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,

		//Left
		position.x - 0.5, position.y + 0.5, position.z + 0.5,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x - 0.5, position.y - 0.5, position.z + 0.5,
		position.x - 0.5, position.y + 0.5, position.z + 0.5,

		//Top
		position.x - 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,
		position.x - 0.5, position.y + 0.5, position.z + 0.5,

		//Down
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,
		position.x - 0.5, position.y - 0.5, position.z + 0.5,
		position.x - 0.5, position.y - 0.5, position.z - 0.5
	};

	VertexBuffer cubeMesh[]
	{
		{glm::vec3(0, 0, 0), glm::vec2(0, 0)}
	};

	chunkMesh.insert(chunkMesh.end(), &blockVertex[0], &blockVertex[std::size(blockVertex)]);
}

unsigned int Chunk::GetVao()
{
	return _vao;
}