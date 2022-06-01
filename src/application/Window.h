///Author : kndysong@gmail.com
///Date : 15.04.2022
///Summary : Manage window

#include "../render/Render.h"
#include "Timer.h"
#include "Gui.h"

#pragma once
class Window
{
	//Attributes and properties
private :
	const char* _title;
	unsigned int _width;
	unsigned int _height;

	Gui* _gui;
	Timer _timerDeltaTime;
	GLFWwindow* _window;
	Render _render;
	
public :

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="width">Width of the window</param>
	/// <param name="height">Height of thw window</param>
	/// <param name="title">Title of the window</param>
	Window(unsigned int width, unsigned int height, const char* title);

	/// <summary>
	/// Run the program
	/// </summary>
	void Run();
};