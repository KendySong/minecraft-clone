#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//Read shaders and load it 
	_shaderReader.open(vertexPath);
	if (_shaderReader.is_open())
	{
		std::cout << "[INFO] Vertex shader is found\n";
		_vertexStream << _shaderReader.rdbuf();
		_vertexString = _vertexStream.str();
		_vertexSource = _vertexString.c_str();
		_shaderReader.close();
	}
	else
		std::cout << "[ERROR] Vertex shader is not found\n";

	_shaderReader.open(fragmentPath);
	if (_shaderReader.is_open())
	{
		std::cout << "[INFO] Fragment shader is found\n";
		_fragmentStream << _shaderReader.rdbuf();
		_fragmentString = _fragmentStream.str();
		_fragmentSource = _fragmentString.c_str();
		_shaderReader.close();
	}
	else
		std::cout << "[ERROR] Fragment shader is not found\n";

	_vertex = glCreateShader(GL_VERTEX_SHADER);
	_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_vertex, 1, &_vertexSource, NULL);
	glShaderSource(_fragment, 1, &_fragmentSource, NULL);
	glCompileShader(_vertex);
	glCompileShader(_fragment);

	//Check shader compilation
	int success = 0;
	char logError[512];
	glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
	if (success)
	{
		std::cout << "[INFO] Vertex shader compilation success\n";
	}
	else
	{
		std::cout << "[ERROR] Vertex shader compilation failed\n";
		glGetShaderInfoLog(_vertex, sizeof(logError), NULL, logError);
		std::cout << logError << "\n";
	}

	glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
	if (success)
	{
		std::cout << "[INFO] Fragment shader compilation success\n";
	}
	else
	{
		std::cout << "[ERROR] Fragment shader compilation failed\n";
		glGetShaderInfoLog(_fragment, sizeof(logError), NULL, logError);
		std::cout << logError << "\n";
	}

	_program = glCreateProgram();
	glAttachShader(_program, _vertex);
	glAttachShader(_program, _fragment);
	glLinkProgram(_program);
	glDetachShader(_program, _vertex);
	glDetachShader(_program, _fragment);
	glDeleteShader(_vertex);
	glDeleteShader(_fragment);
}

unsigned int Shader::GetProgram() 
{
	return _program;
}