#include "application/Window.h"
#include "application/Config.h"

struct Person
{
	int age;
	int id;
	float strengh;
};


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

	//Getter setter with reference
	
	//Faces
	//Singleton
	//Chunk management
	//Procedural gen
	//Light

	//Vertex buffer class
	//Frustrum culling
	//Occlusion culling
}