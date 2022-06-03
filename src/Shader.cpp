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

	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_vertexShader, 1, &_vertexSource, NULL);
	glShaderSource(_fragmentShader, 1, &_fragmentSource, NULL);
	glCompileShader(_vertexShader);
	glCompileShader(_fragmentShader);

	//Check shader compilation
	int success = 0;
	char logError[512];
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
	if (success)
	{
		std::cout << "[INFO] Vertex shader compilation success\n";
	}
	else
	{
		std::cout << "[ERROR] Vertex shader compilation failed\n";
		glGetShaderInfoLog(_vertexShader, sizeof(logError), NULL, logError);
		std::cout << logError << "\n";
	}

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
	if (success)
	{
		std::cout << "[INFO] Fragment shader compilation success\n";
	}
	else
	{
		std::cout << "[ERROR] Fragment shader compilation failed\n";
		glGetShaderInfoLog(_fragmentShader, sizeof(logError), NULL, logError);
		std::cout << logError << "\n";
	}
}

unsigned int Shader::CreateProgram()
{
	unsigned int programShader = glCreateProgram();
	glAttachShader(programShader, _vertexShader);
	glAttachShader(programShader, _fragmentShader);
	glLinkProgram(programShader);
	return programShader;
}