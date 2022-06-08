#include "Texture.h"

Texture::Texture(const char* texturePath, int slot)
{
	shaderSlot = slot;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	uint8_t* pixels = stbi_load(texturePath, &_width, &_height, &_channel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	stbi_image_free(pixels);

	//glActiveTexture(GL_TEXTURE0 + slot);
	//glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::AssignSlot() 
{
	glActiveTexture(GL_TEXTURE0 + shaderSlot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}