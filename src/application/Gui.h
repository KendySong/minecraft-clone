///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Display gui

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Timer.h"
#include "../render/Camera.h"

#pragma once
class Gui 
{
	//Attributes and properties
private :
	Timer _timer;
	std::string _framerate;
	unsigned int _fps;

public :
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="window">Window to display gui</param>
	Gui(GLFWwindow* window);

	/// <summary>
	/// Create new frame for gui
	/// </summary>
	void CreateFrame();

	/// <summary>
	/// Manage and display program data
	/// </summary>
	void DisplayRenderData();

	void ManageCamera(Camera* camera);

	/// <summary>
	/// Render of gui window
	/// </summary>
	void Render();	
};