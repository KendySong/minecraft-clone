///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Render the world and manage camera

#include "Shader.h"
#include "Camera.h"
#include "../world/World.h"
#include "../application/Gui.h"

#pragma once
class Render
{
private :
	Gui* _gui;
	World _world;
	int _locModel;

public:
	Camera* camera;

	/// <summary>
	/// Constructor
	/// </summary>
	Render();

	/// <summary>
	/// Load opengl for the current glfw window
	/// </summary>
	/// <param name="window">Window to load opengl in</param>
	/// <param name="windowSize">Size of the window</param>
	void Load(GLFWwindow* window, glm::vec2 windowSize);

	/// <summary>
	/// Upload block vertex and configure
	/// </summary>
	void UploadVertex();

	/// <summary>
	/// Make the render for the next frame
	/// </summary>
	void RenderFrame();
};