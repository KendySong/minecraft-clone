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

	//Chunk management
	//Add tree

	//Optimization
		//Faces
			//Remove border chunk faces
		//World chunk management size of display chunk vector

	//Frustrum culling
	//Occlusion culling
}