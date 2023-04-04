#include <array>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Gui.hpp"

Gui::Gui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
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

void Gui::displayWorldData(size_t nbChunkRendering, FastNoiseLite* fastNoise)
{
	//Add std::map for enum and string

	static int seed = fastNoise->GetSeed();
	static float frequency = fastNoise->GetFrequency();
	static float lacunarity = fastNoise->GetFractalLacunarity();
	static int octaves = fastNoise->GetFractalOctaves();
	static FastNoiseLite::NoiseType noiseType = fastNoise->GetNoiseType();
	static const char* noiseString[] = { "Open Simplex 2", "Open Simplex 2S", "Cellular", "Perlin", "Value Cubic", "Cubic" };
	static const char* currentNoiseType = "Open Simplex 2S";

	static FastNoiseLite::FractalType fractalType = fastNoise->GetFractalType();
	static const char* fractalString[] = { "None", "FBm", "Ridged", "PingPong", "Domain Warp Progressive", "Domain Warp Independent" };
	static const char* currentFractalType = "FBm";

	ImGui::Begin("World");
	m_chunkRender = "Number of chunks in render " + std::to_string(nbChunkRendering);
	ImGui::TextUnformatted(m_chunkRender.c_str());

	ImGui::Text("Seed : %i", seed);
	ImGui::DragFloat("Frequency", &frequency, 0.001f);
	ImGui::DragFloat("Lacunarity", &lacunarity, 0.001f);
	ImGui::DragInt("Octaves", &octaves, 0.01f);

	if (ImGui::BeginCombo("Noise Type", currentNoiseType))
	{
		for (int i = 0; i < IM_ARRAYSIZE(noiseString); i++)
		{
			bool isSelected = currentNoiseType == noiseString[i];
			if (ImGui::Selectable(noiseString[i], isSelected))
			{
				currentNoiseType = noiseString[i];
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	if (ImGui::BeginCombo("Fractal Type", currentFractalType))
	{
		for (int i = 0; i < IM_ARRAYSIZE(fractalString); i++)
		{
			bool isSelected = currentFractalType == fractalString[i];
			if (ImGui::Selectable(fractalString[i], isSelected))
			{
				currentFractalType = fractalString[i];
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}


	if (ImGui::Button("Apply"))
	{
		fastNoise->SetFrequency(frequency);
		fastNoise->SetFractalLacunarity(lacunarity);
		fastNoise->SetFractalOctaves(octaves);
	}

	ImGui::End();
}

void Gui::render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}