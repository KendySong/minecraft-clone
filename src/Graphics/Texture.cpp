#include "Texture.hpp"

Texture::Texture(const char* texturePath, int slot)
{
	_slot = slot;

	stbi_set_flip_vertically_on_load(true);
	uint8_t* pixels = stbi_load(texturePath, &_width, &_height, &_channel, 0);

	if (pixels == NULL)
	{
		std::cout << "[ERROR] " << texturePath << " not found\n";
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	stbi_image_free(pixels);
}

void Texture::assignSlot() const
{	
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}