///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Render the world and manage camera

#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "../world/World.hpp"
#include "../application/Gui.hpp"
#include "../application/Timer.hpp"

#pragma once
class Render
{
private :
	Timer _deltaTimeTimer;
	GLFWwindow* _window;

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
	Camera* GetCamera() const noexcept;

	/// <summary>
	/// Load shaders into the program
	/// </summary>
	void LoadShader();

	/// <summary>
	/// Load texture for apply to voxels
	/// </summary>
	/// <param name="shaderID"></param>
	void LoadTextures(int shaderID) const;	

	/// <summary>
	/// Load opengl for the current glfw window
	/// </summary>
	/// <param name="window">Window to load opengl in</param>
	/// <param name="windowSize">Size of the window</param>
	void Load(GLFWwindow* window, glm::vec2 windowSize);

	/// <summary>
	/// Update for next frame
	/// </summary>
	void Update();

	/// <summary>
	/// Make the render for the next frame
	/// </summary>
	void RenderFrame();
};