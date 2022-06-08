#include "Gui.h"

Gui::Gui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	_wireframe = false;
}

void Gui::CreateFrame() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::DisplayRenderData(float& renderDistance)
{
	_fps++;
	ImGui::Begin("Render");

	//FPS
	if (_timer.GetElapsedTime() > 1)
	{
		_framerate = std::to_string(_fps) + " fps";
		_fps = 0;
		_timer.Restart();
	}
	ImGui::Text(_framerate.c_str());	

	//Render distance
	ImGui::SliderFloat("Render distance", &renderDistance, 10, 1000);

	//Render mode
	ImGui::Checkbox("Wireframe Render", &_wireframe);
	if (ImGui::Button("Apply"))
	{
		if (_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	ImGui::End();
}

void Gui::ManageCamera(Camera* camera) 
{
	ImGui::Begin("Camera");
	float cameraPos[]{ camera->position.x, camera->position.y ,camera->position.z };
	ImGui::InputFloat3("Camera position", cameraPos);
	ImGui::SliderFloat("Speed", &camera->speed, 1, 100);
	ImGui::End();
}

void Gui::Render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}