#include "application/Window.h"
#include "application/Random.h"

int main() 
{	
	//Window window(1600, 900, "Minecraft clone");
	//return window.Run();

	Random random(0);
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << random.fastrand(1, 2) << " ";
	}
	std::cin.get();
}