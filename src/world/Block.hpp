#include <glm/glm.hpp>

#pragma once
class Block 
{
public :
	Block(const glm::vec3& position, float textureID);
	glm::vec3 getPosition() noexcept;
	float getTextureID() noexcept;

private :
	glm::vec3 m_position;
	float m_textureID;
};