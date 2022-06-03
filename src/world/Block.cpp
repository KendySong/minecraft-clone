#include "Block.h"

Block::Block(glm::vec3 iPosition)
{
	position = iPosition;
}

float* Block::CreateMeshPosition(glm::vec3 position)
{
	float vertex[]
	{
		//Front face
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,
		position.x + 0.5, position.y - 0.5,  position.z + 0.5,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,
		position.x + 0.5, position.y + 0.5,  position.z + 0.5,
		position.x - 0.5, position.y + 0.5,  position.z + 0.5,
		position.x - 0.5, position.y - 0.5,  position.z + 0.5,

		//Back face
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x - 0.5, position.y - 0.5, position.z - 0.5,
		position.x - 0.5, position.y + 0.5, position.z - 0.5,

		//Right face
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z - 0.5,
		position.x + 0.5, position.y - 0.5, position.z - 0.5,
		position.x + 0.5, position.y + 0.5, position.z + 0.5,
		position.x + 0.5, position.y - 0.5, position.z + 0.5,

		 //Left face
		 position.x - 0.5, position.y + 0.5, position.z + 0.5,
		 position.x - 0.5, position.y + 0.5, position.z - 0.5,
		 position.x - 0.5, position.y - 0.5, position.z - 0.5,
		 position.x - 0.5, position.y - 0.5, position.z - 0.5,
		 position.x - 0.5, position.y - 0.5, position.z + 0.5,
		 position.x - 0.5, position.y + 0.5, position.z + 0.5,

		 //Top face
		 position.x - 0.5, position.y + 0.5, position.z - 0.5,
		 position.x + 0.5, position.y + 0.5, position.z + 0.5,
		 position.x + 0.5, position.y + 0.5, position.z - 0.5,
		 position.x + 0.5, position.y + 0.5, position.z + 0.5,
		 position.x - 0.5, position.y + 0.5, position.z - 0.5,
		 position.x - 0.5, position.y + 0.5, position.z + 0.5,

		 //Bottom face
		 position.x - 0.5, position.y - 0.5, position.x - 0.5,
		 position.x + 0.5, position.y - 0.5, position.x - 0.5,
		 position.x + 0.5, position.y - 0.5, position.x + 0.5,
		 position.x + 0.5, position.y - 0.5, position.x + 0.5,
		 position.x - 0.5, position.y - 0.5, position.x + 0.5,
		 position.x - 0.5, position.y - 0.5, position.x - 0.5
	};

	return vertex;
}
