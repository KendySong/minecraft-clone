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
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="position">Position of the tree block</param>
	/// <param name="textureID">Texture of the block</param>
	Block(const glm::vec3& position, float textureID);

	/// <summary>
	/// Getter of the block position
	/// </summary>
	/// <returns>Block position</returns>
	glm::vec3 GetPosition();

	/// <summary>
	/// Getter of textureID
	/// </summary>
	/// <returns>ID of the texture</returns>
	float GetTextureID();
};