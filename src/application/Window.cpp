#include "Window.hpp"

Window* Window::p_window = nullptr;

Window* Window::instance()
{
	if (p_window == nullptr)
	{
		p_window = new Window(Settings::WIDTH, Settings::HEIGHT, Settings::TITLE.c_str());
	}

	return p_window;
}

Window::Window(std::uint32_t width, std::uint32_t height, const char* title)
{
	m_width = width;
	m_height = height;
	p_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	p_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(p_glfwWindow);
}

int Window::run()
{
	m_render.load(this->p_glfwWindow, glm::vec2(m_width, m_height));

	while (!glfwWindowShouldClose(p_glfwWindow))
	{
		glfwPollEvents();
		m_render.update();

		m_render.renderFrame();
		glfwSwapBuffers(p_glfwWindow);
	}

	glfwDestroyWindow(p_glfwWindow);
	ImGui::DestroyContext();

	return 0;
}