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

	//Optimization
		//Faces
			//3D array represent chunk and block position for check faces
		//Greedy mesh

	//Chunk management
	//Procedural gen
	//Light
	
	//Config class
	//Vertex buffer class
	//Getter setter with reference

	//Frustrum culling
	//Occlusion culling

}