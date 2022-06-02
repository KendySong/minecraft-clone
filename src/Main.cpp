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

	//Ditch instancing
	//Chunk with 1 draw call => transform block into single mesh
	//Frustrum culling
}