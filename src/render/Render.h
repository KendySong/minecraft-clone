///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Render the world and manage camera

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"

#pragma once
class Render
{
private :
	//Block _block;
public:
	Camera* camera;

	/// <summary>
	/// Constructor
	/// </summary>
	Render();

	/// <summary>
	/// Load opengl for the current glfw window
	/// </summary>
	/// <param name="window"></param>
	/// <param name="windowSize"></param>
	void Load(GLFWwindow* window, glm::vec2 windowSize);

	/// <summary>
	/// Make the render for the next frame
	/// </summary>
	void RenderFrame();
};