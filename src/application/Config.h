///Author : kndysong@gmail.com
///Date : 15.04.2022
///Summary : Load json settings into the program

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#pragma once
class Config
{
	//Attributes and properties
private :
	nlohmann::json _config;

public :
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="jsonPath">Path of the json file</param>
	Config(const char* jsonPath = "config.json");

	/// <summary>
	/// Destructor
	/// </summary>
	~Config();

	/// <summary>
	/// Getter for json parameters
	/// </summary>
	/// <returns>Json object</returns>
	nlohmann::json GetJsonConfig();
};