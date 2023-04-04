#include <glm/gtc/type_ptr.hpp>

#include "Render.hpp"
#include "Texture.hpp"

Camera* Render::getCamera() const noexcept
{
	return p_camera;
}

void Render::loadShader() 
{
	//Load shader
	p_shader = new Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
	glUseProgram(p_shader->getProgram());

	int lightPositionUniform = glGetUniformLocation(p_shader->getProgram(), "lightPosition");
	glUniform3f(lightPositionUniform, 0, 100, 0);
}

void Render::loadTextures(int shaderID) const
{
	/*
		1) Instanciate textures with path and slot number
		2) Assign all new textures
		3) Add texture slots into uniform sampler
		4) Change sampler array size
	*/
	Texture grass("../textures/grass.png", 0);
	Texture dirt ("../textures/dirt.png",  1);
	Texture sand ("../textures/sand.png",  2);

	Texture wood ("../textures/wood.png",  3);
	Texture leaf ("../textures/leaf.png",  4);
	Texture water("../textures/water.png", 5);

	grass.assignSlot();
	dirt.assignSlot();
	sand.assignSlot();

	wood.assignSlot();
	leaf.assignSlot();
	water.assignSlot();

	int samplerLoc = glGetUniformLocation(shaderID, "textureSampler");
	int texturesID[] = { 0, 1, 2, 3, 4, 5};
	glUniform1iv(samplerLoc, 6, texturesID);
}

void Render::load(GLFWwindow* window, glm::vec2 windowSize) 
{
	p_window = window;
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, (GLsizei)windowSize.x, (GLsizei)windowSize.y);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.5254, 0.6901, 1, 1);

	loadShader();
	loadTextures(p_shader->getProgram());

	//Instanciate camera
	p_camera = new Camera(window, windowSize.x, windowSize.y, 90, 0.1f, 1000.0f, 0.4f, 15.0f, glm::vec3(0, 10, 0));
	p_camera->viewLocation = glGetUniformLocation(p_shader->getProgram(), "view");
	p_camera->projectionLocation = glGetUniformLocation(p_shader->getProgram(), "projection");
	glUniformMatrix4fv(p_camera->projectionLocation, 1, false, glm::value_ptr(p_camera->projection));

	p_gui = new Gui(window);
	m_world.load();
}

void Render::update() 
{
	//Manage camera
	p_camera->processMovement(p_window, m_deltaTimeTimer.getElapsedTime());
	glUniformMatrix4fv(p_camera->viewLocation, 1, false, glm::value_ptr(p_camera->view));
	m_deltaTimeTimer.restart();

	//Manage world
	m_world.manageChunks(p_camera->position);
}

void Render::renderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	p_gui->createFrame();
	for (size_t i = 0; i < m_world.displayChunks.size(); i++)
	{
		glBindVertexArray(m_world.displayChunks[i].getVao());
		glDrawArrays(GL_TRIANGLES, 0, m_world.displayChunks[i].verticesDraw);
	}
	p_gui->displayRenderData(m_world.renderDistance, p_shader->getProgram());
	p_gui->manageWorldCamera(p_camera, p_shader->getProgram());
	p_gui->displayWorldData(m_world.displayChunks.size(), m_world.getFastNoise());
	p_gui->render();
}