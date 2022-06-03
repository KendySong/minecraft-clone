#include "Chunk.h"

Chunk::Chunk(glm::vec2 position)
{
	_vao = 0;
	_vbo = 0;
	_shader = 0;

	float vertices[]
	{
		//Front face
		-0.5, -0.5,  0.5,
		 0.5, -0.5,  0.5,
		 0.5,  0.5,  0.5,
		 0.5,  0.5,  0.5,
		-0.5,  0.5,  0.5,
		-0.5, -0.5,  0.5,

		//Back face
		-0.5, -0.5, -0.5,
		 0.5,  0.5, -0.5,
		 0.5, -0.5, -0.5,
		 0.5,  0.5, -0.5,
		-0.5, -0.5, -0.5,
		-0.5,  0.5, -0.5,

		//Right face
		 0.5,  0.5,  0.5,
		 0.5, -0.5, -0.5,
		 0.5,  0.5, -0.5,
		 0.5, -0.5, -0.5,
		 0.5,  0.5,  0.5,
		 0.5, -0.5,  0.5,

		 //Left face
		 -0.5,  0.5,  0.5,
		 -0.5,  0.5, -0.5,
		 -0.5, -0.5, -0.5,
		 -0.5, -0.5, -0.5,
		 -0.5, -0.5,  0.5,
		 -0.5,  0.5,  0.5,

		 //Top face
		 -0.5,  0.5, -0.5,
		  0.5,  0.5,  0.5,
		  0.5,  0.5, -0.5,
		  0.5,  0.5,  0.5,
		 -0.5,  0.5, -0.5,
		 -0.5,  0.5,  0.5,

		 //Bottom face
		 -0.5, -0.5, -0.5,
		  0.5, -0.5, -0.5,
		  0.5, -0.5,  0.5,
		  0.5, -0.5,  0.5,
		 -0.5, -0.5,  0.5,
		 -0.5, -0.5, -0.5
	};

	//Class mesh, index buffer, vertex buffer with block
		//Replace 0 with x y z position
		//Create vbo and vao
			//When create block add faces into vbo vector
		//Shader dont forget camera -> (Window and renderer) 
	
	//Bind vao and shader before draw
	
	





	/*
	for (int x = position.x; x < position.x + ChunkSize::Width; x++)
	{
		for (int y = 0; y < ChunkSize::Depth; y++)
		{
			for (int z = position.y; z < position.y + ChunkSize::Height; z++)
			{			
				Block block(glm::vec3(x, y, z));
				blocks.push_back(block);
			}
		}
	}
	*/


	//0		FRONT
	//6		BACK
	//12	RIGHT	
	//18	LEFT	
	//24	TOP		OK
	//30	BOT		OK
}

unsigned int Chunk::GetVao()
{
	return _vao;
}