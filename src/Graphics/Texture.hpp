#include <iostream>

#include <glad/glad.h>

#pragma once
class Texture
{
public:
	std::uint32_t textureID;
	Texture(const char* texturePath, int slot);
	void assignSlot() const;

private :
	int _slot;
	int _width;
	int _height;
	int _channel;
};