#include "Block.hpp"

Block::Block(const glm::vec3& position, float textureID)
{
	_position = position;
	_textureID = textureID;
}

glm::vec3 Block::getPosition() const noexcept
{
	return _position;
}

float Block::getTextureID() const noexcept
{
	return _textureID;
}