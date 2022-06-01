#include "Gui.h"

Gui::Gui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Gui::CreateFrame() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::DisplayData()
{
	_fps++;
	ImGui::Begin("Render");
	if (_timer.GetElapsedTime() > 1)
	{
		_framerate = std::to_string(_fps) + " fps";
		_fps = 0;
		_timer.Restart();
	}

	ImGui::Text(_framerate.c_str());
	ImGui::End();
}

void Gui::Render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}