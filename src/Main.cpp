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

	//Vertex buffer class
	//Faces
	//Singleton

	//Frustrum culling
	//Occlusion culling
}