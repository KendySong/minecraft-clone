#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	_width = width;
	_height = height;
	_title = title;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(_window);
}

void Window::Run()
{
	_render.Load(this->_window, glm::vec2(_width, _height));
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();

		_render.camera->ProcessMovement(_window, _timerDeltaTime.GetElapsedTime());
		glUniformMatrix4fv(_render.camera->viewLocation, 1, false, glm::value_ptr(_render.camera->view));
		glUniformMatrix4fv(_render.camera->projectionLocation, 1, false, glm::value_ptr(_render.camera->projection));
		_timerDeltaTime.Restart();

		_render.RenderFrame();
		glfwSwapBuffers(_window);
	}
}