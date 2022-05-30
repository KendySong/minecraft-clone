#include "Config.h"

Config::Config(const char* jsonPath)
{
	std::ifstream fileReader(jsonPath);
	if (fileReader.is_open())
		fileReader >> _config;
	else
		std::cout << "[ERROR] json not found or opening failed";
	fileReader.close();
}

Config::~Config() 
{
	_config.clear();
}

nlohmann::json Config::GetJsonConfig() 
{
	return _config;
}