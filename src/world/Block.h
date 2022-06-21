///Author : Kendy Song
///Date : 20.06.2022
///Summary : Regroup block's data

#include <glm/glm.hpp>

#pragma once
class Block 
{
	//Attributes and properties
private :
	glm::vec3 _position;
	float _textureID;

public :
	Block(glm::vec3 position, float textureID);
	glm::vec3 GetPosition();
	float GetTextureID();
};