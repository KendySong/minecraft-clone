#include <glm/glm.hpp>

#pragma once
class Block 
{
private :
	glm::vec3 _position;
	float _textureID;

public :
	Block(const glm::vec3& position, float textureID);

	glm::vec3 getPosition() const noexcept;
	float getTextureID() const noexcept;
};