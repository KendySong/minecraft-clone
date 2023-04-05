#include <array>
#include <map>

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
	ImGui::Begin("Settings");
	ImGui::TextUnformatted(m_gpu.c_str());
	ImGui::TextUnformatted(m_version.c_str());
	if (m_timer.getElapsedTime() > 1)
	{
		m_framerate = std::to_string(m_fps) + " fps";
		m_fps = 0;
		m_timer.restart();
	}
	ImGui::Text(m_framerate.c_str());	
	ImGui::SliderFloat("Render distance", &renderDistance, 10, 1000);

	static std::array<const char*, 2> lightTypes{ "Fake", "Diffuse" };
	static const char* currentLight = lightTypes[0];
	if (ImGui::BeginCombo("Light", currentLight))
	{
		for (size_t i = 0; i < lightTypes.size(); i++)
		{
			bool isSelected = (currentLight == lightTypes[i]);
			if (ImGui::Selectable(lightTypes[i], isSelected))
			{
				currentLight = lightTypes[i];
			}
		
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();  		
			}
		}
		ImGui::EndCombo();
	}

	ImGui::Checkbox("Wireframe Render", &m_wireframe);
	ImGui::Checkbox("Face culling", &m_faceCulling);
	if (ImGui::Button("Apply"))
	{
		if (m_wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (m_faceCulling)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		int lightModeLocation = glGetUniformLocation(shaderID, "diffuseLight");
		if (currentLight == "Diffuse")
		{
			glUniform1i(lightModeLocation, true);
		}
		else
		{
			glUniform1i(lightModeLocation, false);
		}
	}
	ImGui::Separator();
}

void Gui::manageWorldCamera(Camera* camera, std::uint32_t shaderID) const
{
	ImGui::TextUnformatted("Camera");
	ImGui::Separator();

	ImGui::InputFloat3("Position", &camera->position.x);
	ImGui::SliderFloat("Speed", &camera->speed, 1, 100);
	ImGui::DragFloat("FOV", &camera->fov, 0.1f, 0, 180);
	if (ImGui::Button("Apply"))
	{
		camera->reconstruct(shaderID);
	}
	ImGui::Separator();
}

void Gui::displayWorldData(size_t nbChunkRendering, FastNoiseLite* fastNoise)
{
	static int seed = fastNoise->GetSeed();
	static float frequency = fastNoise->GetFrequency();
	static float lacunarity = fastNoise->GetFractalLacunarity();
	static int octaves = fastNoise->GetFractalOctaves();
	static std::string noiseString[] = { "Open Simplex 2", "Open Simplex 2S", "Cellular", "Perlin", "Value Cubic", "Cubic" };
	static std::string currentNoiseType = "Open Simplex 2S";

	static std::string fractalString[] = { "None", "FBm", "Ridged", "PingPong", "Domain Warp Progressive", "Domain Warp Independent" };
	static std::string currentFractalType = "FBm";

	ImGui::TextUnformatted("World");
	ImGui::Separator();
	m_chunkRender = "Number of chunks in render " + std::to_string(nbChunkRendering);
	ImGui::TextUnformatted(m_chunkRender.c_str());

	ImGui::Text("Seed : %i", seed);
	ImGui::DragFloat("Frequency", &frequency, 0.001f);
	ImGui::DragFloat("Lacunarity", &lacunarity, 0.001f);
	ImGui::DragInt("Octaves", &octaves, 0.01f);

	if (ImGui::BeginCombo("Noise Type", currentNoiseType.c_str()))
	{
		for (int i = 0; i < IM_ARRAYSIZE(noiseString); i++)
		{
			bool isSelected = currentNoiseType == noiseString[i];
			if (ImGui::Selectable(noiseString[i].c_str(), isSelected))
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

	if (ImGui::BeginCombo("Fractal Type", currentFractalType.c_str()))
	{
		for (int i = 0; i < IM_ARRAYSIZE(fractalString); i++)
		{
			bool isSelected = currentFractalType == fractalString[i];
			if (ImGui::Selectable(fractalString[i].c_str(), isSelected))
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

		if (currentNoiseType == "Open Simplex 2")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		}
		else if (currentNoiseType == "Open Simplex 2S")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		}
		else if (currentNoiseType == "Cellular")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_Cellular);
		}
		else if (currentNoiseType == "Perlin")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		}
		else if (currentNoiseType == "Value Cubic")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
		}
		else if (currentNoiseType == "Cubic")
		{
			fastNoise->SetNoiseType(FastNoiseLite::NoiseType_Value);
		}

		if (currentNoiseType == "None")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_None);
		}
		else if (currentNoiseType == "FBm")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_FBm);
		}
		else if (currentNoiseType == "Ridged")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_Ridged);
		}
		else if (currentNoiseType == "PingPong")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_PingPong);
		}
		else if (currentNoiseType == "Domain Warp Progressive")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
		}
		else if (currentNoiseType == "Domain Warp Independent")
		{
			fastNoise->SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
		}
	}

	ImGui::End();
}

void Gui::render() 
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}