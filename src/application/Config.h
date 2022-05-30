///Author : kndysong@gmail.com
///Date : 15.04.2022
///Summary : Load json settings into the program

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#pragma once
class Config
{
private :
	nlohmann::json _config;

public :
	Config(const char* jsonPath = "config.json");
	~Config();
	nlohmann::json GetJsonConfig();
};