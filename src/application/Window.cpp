#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	_width = width;
	_height = height;
	_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(_glfwWindow);
}

int Window::Run()
{
	_render.Load(this->_glfwWindow, glm::vec2(_width, _height));
	while (!glfwWindowShouldClose(_glfwWindow))
	{
		glfwPollEvents();
		_render.Update();

		//Render world and gui
		_render.RenderFrame();
		glfwSwapBuffers(_glfwWindow);
	}

	glfwDestroyWindow(_glfwWindow);
	ImGui::DestroyContext();

	return 0;
}