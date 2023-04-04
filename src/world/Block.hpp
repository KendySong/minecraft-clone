#include <glm/glm.hpp>

#pragma once
class Block 
{
public :
	Block(const glm::vec3& position, float textureID);

	glm::vec3 getPosition() const noexcept;
	float getTextureID() const noexcept;

private :
	glm::vec3 _position;
	float _textureID;
};