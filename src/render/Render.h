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

	Render();
	void Load(GLFWwindow* window, glm::vec2 windowSize);
	void RenderFrame();
};