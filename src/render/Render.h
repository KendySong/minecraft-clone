///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Render the world and manage camera

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "../world/World.h"
#include "../application/Gui.h"
#include "../application/Timer.h"

#pragma once
class Render
{
private :
	Timer _deltaTimeTimer;
	GLFWwindow* _glfwWindow;

	Gui* _gui;

	World _world;
	Shader* _shader;
	Camera* _camera;
	
public:
	/// <summary>
	/// Constructor
	/// </summary>
	Render() = default;

	/// <summary>
	/// Getter of camera
	/// </summary>
	/// <returns>Pointer to camera</returns>
	Camera* GetCamera();

	void LoadShader();

	void LoadTextures(int shaderID);	

	/// <summary>
	/// Load opengl for the current glfw window
	/// </summary>
	/// <param name="window">Window to load opengl in</param>
	/// <param name="windowSize">Size of the window</param>
	void Load(GLFWwindow* glfwWindow, glm::vec2 windowSize);

	/// <summary>
	/// Update for next frame
	/// </summary>
	void Update();

	/// <summary>
	/// Make the render for the next frame
	/// </summary>
	void RenderFrame();
};