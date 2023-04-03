#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#pragma once
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::uint32_t getProgram() const noexcept;

private :
	std::uint32_t _vertex;
	std::uint32_t _fragment;
	std::uint32_t _program;

	std::ifstream _shaderReader;
	std::stringstream _vertexStream;
	std::stringstream _fragmentStream;
	std::string _vertexString;
	std::string _fragmentString;
	const char* _vertexSource = "";
	const char* _fragmentSource = "";
};