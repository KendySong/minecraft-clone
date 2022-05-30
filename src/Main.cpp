#include "application/Window.h"
#include "application/Config.h"
#include <string>

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
}