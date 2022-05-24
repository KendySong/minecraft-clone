#include "../render/Render.h"
#include "Timer.h"

#pragma once
class Window
{
private :
	const char* _title;
	unsigned int _width;
	unsigned int _height;

	Render _render;
	GLFWwindow* _window;
	Timer _timerDeltaTime;

public :
	Window(unsigned int width, unsigned int height, const char* title);
	void Run();
};