///Author : kndysong@gmail.com
///Date : 07.06.2022
///Summary : Load texture and use it

#include <iostream>

#include <glad/glad.h>

#include "stb_image.h"

#pragma once
class Texture
{
	//Attributes and properties
private :
	unsigned int _textureID;


	int _width;
	int _height;
	int _channel;


public :
	Texture(const char* texturePath);

};

