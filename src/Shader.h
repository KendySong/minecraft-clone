///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Load shader and compile them

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#pragma once
class Shader
{
	//Attributes and properties
private:
	unsigned int _vertexShader = 0;
	unsigned int _fragmentShader = 0;

	std::ifstream _shaderReader;
	std::stringstream _vertexStream;
	std::stringstream _fragmentStream;
	std::string _vertexString;
	std::string _fragmentString;
	const char* _vertexSource = "";
	const char* _fragmentSource = "";

public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="vertexPath">Path of the vertex shader</param>
	/// <param name="fragmentPath">Path of the fragment shader</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int CreateProgram();
};