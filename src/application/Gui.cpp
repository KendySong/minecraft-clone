#include "Gui.hpp"

Gui::Gui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	m_wireframe = false;
	m_faceCulling = true;
	const GLubyte* gpuName = glGetString(GL_RENDERER);
	const GLubyte* versionName = glGetString(GL_VERSION);

	for (size_t i = 0; i < strlen((char*)gpuName); i++)
	{
		m_gpu += gpuName[i];	
	}	

	for (size_t i = 0; i < strlen((char*)versionName); i++)
	{
		m_version += versionName[i];
	}
}

void Gui::createFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::displayRenderData(float& renderDistance, std::uint32_t shaderID)
{
	m_fps++;
	ImGui::Begin("Render");

	ImGui::Text(m_gpu.c_str());
	ImGui::Text(m_version.c_str());

	//FPS
	if (m_timer.getElapsedTime() > 1)
	{
		m_framerate = std::to_string(m_fps) + " fps";
		m_fps = 0;
		m_timer.restart();
	}
	ImGui::Text(m_framerate.c_str());	

	//Render distance
	ImGui::SliderFloat("Render distance", &renderDistance, 10, 1000);

	//Light
	std::array<const char*, 2> lightTypes{ "Fake", "Diffuse" };
	static const char* currentLight = lightTypes[0];

	if (ImGui::BeginCombo("Light", currentLight))
	{
		for (int i = 0; i < lightTypes.size(); i++)
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
	ImGui::Checkbox("Wireframe Render", &m_wireframe);
	ImGui::Checkbox("Face culling", &m_faceCulling);

	if (ImGui::Button("Apply"))
	{
		if (m_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (m_faceCulling)
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

void Gui::manageWorldCamera(Camera* camera, std::uint32_t shaderID) const
{
	ImGui::Begin("Camera");
	ImGui::InputFloat3("Position", &camera->position.x);
	ImGui::SliderFloat("Speed", &camera->speed, 1, 100);
	ImGui::DragFloat("FOV", &camera->fov, 0.1f, 0, 180);
	if (ImGui::Button("Apply"))
	{
		camera->reconstruct(shaderID);
	}
	ImGui::End();
}

void Gui::displayWorldData(size_t nbChunkRendering)
{
	ImGui::Begin("World");
	m_chunkRender = "Number of chunks in render " + std::to_string(nbChunkRendering);
	ImGui::Text(m_chunkRender.c_str());
	ImGui::End();
}

void Gui::render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}