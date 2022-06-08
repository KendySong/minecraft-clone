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

	//Faces
	//Chunk management
	//Procedural gen
	//Light
	
	//Config class
	//Vertex buffer class
	//Getter setter with reference

	//Frustrum culling
	//Occlusion culling

}