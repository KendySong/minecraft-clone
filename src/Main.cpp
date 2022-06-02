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
		//Try https://dev.to/superfola/lets-render-chunks-of-voxels-with-opengl--47g9 https://www.youtube.com/watch?v=Th4huqR77rI
		//GL_USAGE => GL_DYNAMIC | GL_STREAM
		//Generate 1 vbo and vao foreach chunk

	//Compress verticex
	//Ditch instancing
	//Frustrum culling
	//Occlusion culling
}