#include "Render.h"

Render::Render() 
{

}

Camera* Render::GetCamera() 
{
	return _camera;
}

void Render::Load(GLFWwindow* window, glm::vec2 windowSize) 
{
	_window = window;
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, windowSize.x, windowSize.y);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0.41, 0.29, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Load shader
	Shader shader("shaders/cube.vert", "shaders/cube.frag");
	glUseProgram(shader.GetProgram());

	//Instanciate camera
	_camera = new Camera(window, windowSize.x, windowSize.y, 90, 0.1f, 1000.0f, 0.4f, 15.0f, glm::vec3(0, 0, 0));
	_camera->viewLocation = glGetUniformLocation(shader.GetProgram(), "view");
	_camera->projectionLocation = glGetUniformLocation(shader.GetProgram(), "projection");
	glUniformMatrix4fv(_camera->projectionLocation, 1, false, glm::value_ptr(_camera->projection));

	_gui = new Gui(window);
	_world.Load();
}

void Render::Update() 
{
	_camera->ProcessMovement(_window, _deltaTimeTimer.GetElapsedTime());	
	glUniformMatrix4fv(_camera->viewLocation, 1, false, glm::value_ptr(_camera->view));
	_deltaTimeTimer.Restart();
}

void Render::RenderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_gui->CreateFrame();
	for (size_t i = 0; i < _world.displayChunks.size(); i++)
	{
		glBindVertexArray(_world.displayChunks[i].GetVao());
		glDrawArrays(GL_TRIANGLES, 0, _world.displayChunks[i].vertex.size() / 3);
	}
	_gui->DisplayData();
	_gui->Render();
}