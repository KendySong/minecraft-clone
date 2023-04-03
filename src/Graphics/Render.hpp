#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "../world/World.hpp"
#include "../application/Gui.hpp"
#include "../application/Timer.hpp"

#pragma once
class Render
{
public:
	Render() = default;

	Camera* getCamera() const noexcept;
	void loadShader();
	void loadTextures(int shaderID) const;
	void load(GLFWwindow* window, glm::vec2 windowSize);

	void update();
	void renderFrame();

private :
	Timer m_deltaTimeTimer;
	GLFWwindow* p_window;

	Gui* p_gui;

	World m_world;
	Shader* p_shader;
	Camera* p_camera;
};