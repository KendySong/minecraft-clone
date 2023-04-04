#include "Gui.hpp"
#include "Timer.hpp"
#include "../Graphics/Render.hpp"
#include "Settings.hpp"

#pragma once
class Window
{
private :
	Window(std::uint32_t width, std::uint32_t height, const char* title);

public:
	static Window* instance();
	int run();

private :
	static Window* p_window;

	const char* p_title;
	std::uint32_t m_width;
	std::uint32_t m_height;

	GLFWwindow* p_glfwWindow;
	Render m_render;
};