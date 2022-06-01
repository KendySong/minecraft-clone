///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Display gui

#include <string>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Timer.h"

#pragma once
class Gui 
{
	//Attributes and properties
private :
	Timer _timer;
	std::string _framerate;
	unsigned int _fps;

public :
	Gui(GLFWwindow* window);
	void CreateFrame();
	void DisplayData();
	void Render();
	
};