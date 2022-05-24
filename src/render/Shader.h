#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#ifndef P_OPENGL
#define P_OPENGL
#include <glad/glad.h>
#endif

#pragma once
class Shader
{
private :
	unsigned int _vertexShader = 0;
	unsigned int _fragmentShader = 0;
	unsigned int _programShader = 0;

	std::ifstream _shaderReader;
	std::stringstream _vertexStream;
	std::stringstream _fragmentStream;
	std::string _vertexString;
	std::string _fragmentString;
	const char* _vertexSource = "";
	const char* _fragmentSource = "";

public : 

	Shader(const char* vertexPath, const char* fragmentPath);
	unsigned int GetProgramShader();
	void Use();
};