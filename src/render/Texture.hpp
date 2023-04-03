///Author : kndysong@gmail.com
///Date : 07.06.2022
///Summary : Load texture and use it

#include <iostream>

#include <glad/glad.h>

#include <stb/stb_image.h>

#pragma once
class Texture
{
	//Attributes and properties
private :
	int _slot;
	int _width;
	int _height;
	int _channel;

public :	
	unsigned int textureID;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="texturePath">Path of the texture file</param>
	/// <param name="slot">Slot of the texture</param>
	Texture(const char* texturePath, int slot);

	/// <summary>
	/// Assign the texture at the slot given in constructor
	/// </summary>
	void AssignSlot() const;
};

