#include "application/Window.h"
#include "application/Config.h"

int main() 
{	
	Config config;
	Window window
	(
		config.GetJsonConfig()["Program"]["width"], 
		config.GetJsonConfig()["Program"]["height"], 
		"Minecraft clone"
	);
	window.Run();

	//Index buffer class
	//Vertex buffer class

	//Chunk with 1 draw call => transform block into single mesh
		//Set shader foreach chunk
		//GL_USAGE => GL_DYNAMIC | GL_STREAM
			//std::vector for vbo and method for add faces, => vao foreach chunks


	//Compress verticex
	//Ditch instancing
	//Frustrum culling
	//Occlusion culling
}