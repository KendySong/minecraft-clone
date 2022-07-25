#include "Block.h"

Block::Block(const glm::vec3& position, float textureID)
{
	_position = position;
	_textureID = textureID;
}

glm::vec3 Block::GetPosition() 
{
	return _position;
}

float Block::GetTextureID() 
{
	return _textureID;
}