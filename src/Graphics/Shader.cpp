#include <sstream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

#include <iostream>
#include <filesystem>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	m_shaderID = 0;
	std::pair<std::string, bool> vertexSource = this->loadShader(vertexPath);
	std::pair<std::string, bool> fragmentSource = this->loadShader(fragmentPath);
	const char* vSrc = vertexSource.first.c_str();
	const char* fSrc = fragmentSource.first.c_str();
	if (!vertexSource.second || !fragmentSource.second)
	{
		return;
	}

	std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vSrc, 0);
	glShaderSource(fragmentShader, 1, &fSrc, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	if (!this->checkCompileStatus(vertexShader, "vertex shader") ||
		!this->checkCompileStatus(fragmentShader, "fragment shader"))
	{
		return;
	}

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	glLinkProgram(m_shaderID);

	int linkStatus = false;
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		int length = 0;
		std::string errorMsg = "";
		std::vector<char> errorMessage(length);

		glGetProgramiv(m_shaderID, GL_INFO_LOG_LENGTH, &length);
		glGetProgramInfoLog(m_shaderID, length, &length, errorMessage.data());
		for (size_t i = 0; i < errorMessage.size(); i++)
		{
			errorMsg += errorMessage[i];
		}

#ifdef DEBUG
		std::cerr << "[ERROR] link error : " + errorMsg + "\n";
#endif

		return;
	}

	glDetachShader(m_shaderID, vertexShader);
	glDetachShader(m_shaderID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::uint32_t Shader::getProgram() noexcept
{
	return m_shaderID;
}

bool Shader::checkCompileStatus(std::uint32_t shaderID, std::string name)
{
	int shaderCompileStatus = false;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileStatus);
	if (!shaderCompileStatus)
	{
		int length = 0;
		std::string finalErrorMsg;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> errorMessage(length);
		glGetShaderInfoLog(shaderID, length, &length, errorMessage.data());
		for (size_t i = 0; i < errorMessage.size(); i++)
		{
			finalErrorMsg += errorMessage[i];
		}
#ifdef DEBUG
		std::cerr << "[ERROR] Compilation failed (" + name + ") : " + finalErrorMsg + "\n";
#endif
		return false;
	}
	else
	{
		return true;
	}
}

std::pair<std::string, bool> Shader::loadShader(const char* shaderPath)
{
	std::pair<std::string, bool> result("", false);
	std::fstream fileReader(shaderPath);
	if (fileReader.is_open())
	{
		std::stringstream sStream;
		sStream << fileReader.rdbuf();
		std::string sShader = sStream.str();
		result.first = sShader;
		result.second = true;
		fileReader.close();
	}
	else
	{
#ifdef DEBUG
		std::cerr << "[ERROR] Fragment shader not found : " + std::string(shaderPath) + "\n";
#endif
	}

	return result;
}
