#include "Gui.h"

Gui::Gui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	_wireframe = false;
	_faceCulling = true;

	//Opengl and Gpu data
	const GLubyte* gpuName = glGetString(GL_RENDERER);
	const GLubyte* versionName = glGetString(GL_VERSION);

	for (size_t i = 0; i < strlen((char*)gpuName); i++)
	{
		gpu += gpuName[i];	
	}	

	for (size_t i = 0; i < strlen((char*)versionName); i++)
	{
		version += versionName[i];
	}
}

void Gui::CreateFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::DisplayRenderData(float& renderDistance, unsigned int shaderID)
{
	_fps++;
	ImGui::Begin("Render");

	ImGui::Text(gpu.c_str());
	ImGui::Text(version.c_str());

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

	//Light
	const char* lightTypes[] = { "Fake", "Diffuse" };
	static const char* currentLight = lightTypes[0];

	if (ImGui::BeginCombo("Light", currentLight))
	{
		for (int i = 0; i < std::size(lightTypes); i++)
		{
			bool isSelected = (currentLight == lightTypes[i]);
			if (ImGui::Selectable(lightTypes[i], isSelected))
				currentLight = lightTypes[i];
		
			if (isSelected)
				ImGui::SetItemDefaultFocus();  		
		}
		ImGui::EndCombo();
	}

	//Render mode
	ImGui::Checkbox("Wireframe Render", &_wireframe);
	ImGui::Checkbox("Face culling", &_faceCulling);

	if (ImGui::Button("Apply"))
	{
		if (_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (_faceCulling)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		int lightModeLocation = glGetUniformLocation(shaderID, "diffuseLight");
		if (currentLight == "Diffuse")		
			glUniform1i(lightModeLocation, true);		
		else
			glUniform1i(lightModeLocation, false);
	}

	ImGui::End();
}

void Gui::ManageCamera(Camera* camera) const
{
	ImGui::Begin("Camera");
	float cameraPos[]{ camera->position.x, camera->position.y ,camera->position.z };
	ImGui::InputFloat3("Camera position", cameraPos);
	ImGui::SliderFloat("Speed", &camera->speed, 1, 100);
	ImGui::End();
}

void Gui::DisplayWorldData(size_t nbChunkRendering)
{
	ImGui::Begin("World");
	chunkRender = "Number of chunks in render " + std::to_string(nbChunkRendering);
	ImGui::Text(chunkRender.c_str());
	ImGui::End();
}

void Gui::Render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}