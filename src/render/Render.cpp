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
	glClearColor(0.5254, 0.6901, 1, 1);

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

	/*
		1) Instanciate textures with path and slot number
		2) Assign all new textures
		3) Add texture slots into uniform sampler
		4) Change sampler array size
	*/
	Texture grass("textures/grass.png", 0);
	Texture dirt("textures/dirt.png", 1);
	grass.AssignSlot();
	dirt.AssignSlot();

	int samplerLoc = glGetUniformLocation(shader.GetProgram(), "sampler");
	int texturesID[2] = {0, 1};
	glUniform1iv(samplerLoc, 2, texturesID);
}

void Render::Update() 
{
	//Manage camera
	_camera->ProcessMovement(_window, _deltaTimeTimer.GetElapsedTime());
	glUniformMatrix4fv(_camera->viewLocation, 1, false, glm::value_ptr(_camera->view));
	_deltaTimeTimer.Restart();

	//Manage world
	_world.ManageChunk(_camera->position);
}

void Render::RenderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_gui->CreateFrame();
	for (size_t i = 0; i < _world.displayChunks.size(); i++)
	{
		glBindVertexArray(_world.displayChunks[i].GetVao());
		glDrawArrays(GL_TRIANGLES, 0, _world.displayChunks[i].verticesDraw);
	}
	_gui->DisplayRenderData(_world.renderDistance);
	_gui->ManageCamera(_camera);
	_gui->Render();
}