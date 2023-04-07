#include "Block.hpp"

Block::Block(const glm::vec3& position, float textureID)
{
	m_position = position;
	m_textureID = textureID;
}

glm::vec3 Block::getPosition() noexcept
{
	return m_position;
}

float Block::getTextureID() noexcept
{
	return m_textureID;
}