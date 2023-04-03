#include <string>
#include <array>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Timer.hpp"
#include "../Graphics/Camera.hpp"

#pragma once
class Gui 
{
public:
	Gui(GLFWwindow* window);
	void createFrame() const;
	void displayRenderData(float& renderDistance, std::uint32_t shaderID);
	void manageWorldCamera(Camera* camera, std::uint32_t shaderID) const;
	void displayWorldData(size_t nbChunkRendering);
	void render();

private :
	std::string m_gpu;
	std::string m_version;
	std::string m_chunkRender;

	Timer m_timer;
	std::string m_framerate;
	std::uint32_t m_fps;
	bool m_wireframe;
	bool m_faceCulling;
};