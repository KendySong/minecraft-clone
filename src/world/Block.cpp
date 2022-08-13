#include "Block.h"

Block::Block(const glm::vec3& position, float textureID)
{
	_position = position;
	_textureID = textureID;
}

glm::vec3 Block::GetPosition() const noexcept
{
	return _position;
}

float Block::GetTextureID() const noexcept
{
	return _textureID;
}