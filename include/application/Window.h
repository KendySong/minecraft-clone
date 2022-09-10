///Author : kndysong@gmail.com
///Date : 15.04.2022
///Summary : Manage window

#include "Settings.h"
#include "../render/Render.h"
#include "Timer.h"
#include "Gui.h"

#pragma once
class Window
{
	//Attributes and properties
private :
	static Window* _window;

	const char* _title;
	unsigned int _width;
	unsigned int _height;

	Gui* _gui;
	GLFWwindow* _glfwWindow;
	Render _render;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="width">Width of the window</param>
	/// <param name="height">Height of thw window</param>
	/// <param name="title">Title of the window</param>
	Window(unsigned int width, unsigned int height, const char* title);
	
public :
	/// <summary>
	/// Create and give pointer to instance
	/// </summary>
	/// <returns>Pointer to instance</returns>
	static Window* GetInstance();

	/// <summary>
	/// Run the program
	/// </summary>
	int Run();
};