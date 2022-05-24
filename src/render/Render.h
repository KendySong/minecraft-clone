#ifndef P_OPENGL
#define P_OPENGL
#include <glad/glad.h>
#endif

#ifndef P_GLFW
#define P_GLFW
#include <glfw/glfw3.h>
#endif

#ifndef P_GLM
#define P_GLM
#include <glm/glm.hpp>
#endif

#include "Shader.h"
#include "Camera.h"

#pragma once
class Render
{
public:
	Camera* camera;

	Render();
	void Load(GLFWwindow* window, glm::vec2 windowSize);
	void RenderFrame();
};