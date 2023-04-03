#include <string>
#include <array>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Timer.hpp"
#include "../render/Camera.hpp"

#pragma once
class Gui 
{
	//Attributes and properties
private :
	std::string gpu;
	std::string version;
	std::string chunkRender;

	Timer _timer;
	std::string _framerate;
	unsigned int _fps;
	bool _wireframe;
	bool _faceCulling;

public :
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="window">Window to display gui</param>
	Gui(GLFWwindow* window);

	/// <summary>
	/// Create new frame for gui
	/// </summary>
	void CreateFrame() const;

	/// <summary>
	/// Manage and display program data
	/// </summary>
	void DisplayRenderData(float& renderDistance, unsigned int shaderID);

	/// <summary>
	/// Display camera position and speed
	/// </summary>
	/// <param name="camera">Camera to display data</param>
	void ManageCamera(Camera* camera, std::uint32_t shaderID) const;

	/// <summary>
	/// Display number of chunks
	/// </summary>
	/// <param name="nbChunkRendering">Number of chunks to display</param>
	void DisplayWorldData(size_t nbChunkRendering);

	/// <summary>
	/// Render of gui window
	/// </summary>
	void Render();	
};