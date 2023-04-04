#pragma once
#include <string>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexPath, const char* fragmentPath);

	std::uint32_t getProgram() noexcept;

private:
	bool checkCompileStatus(std::uint32_t objectID, std::string name);
	std::pair<std::string, bool> loadShader(const char* shaderPath);

	std::uint32_t m_shaderID;
};