///Author : kndysong@gmail.com
///Date : 30.05.2022
///Summary : Camera matrix and manage camera input

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once
class Camera
{
	//Attributes and properties
private :	
	float _width;
	float _height;
	float _near;
	float _far;

	float _yaw;
	float _pitch;

	float _lastX;
	float _lastY;

	float _offsetX;
	float _offsetY;

	glm::vec3 _up;
	glm::vec3 _front;
	glm::vec3 _direction;
		
	bool _canRotate;
	double _mousePositionX;
	double _mousePositionY;

public:
	glm::vec3 position;

	float sensitivity;
	float speed;
	float fov;	

	glm::mat4 view;
	int viewLocation;

	glm::mat4 projection;
	int projectionLocation;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="window">Window to process the camera</param>
	/// <param name="iWidth">Width of the window</param>
	/// <param name="iHeight">Height of the window</param>
	/// <param name="iFov">Fov of the cam</param>
	/// <param name="iNear">Min distance to render</param>
	/// <param name="iFar">Max distance to render</param>
	/// <param name="iSensitivity">Sensitivity of the mouse for movements</param>
	/// <param name="iSpeed">Speed of the camera</param>
	/// <param name="iPosition">Start position of the camera</param>
	Camera(GLFWwindow* window, float iWidth, float iHeight, float iFov, float iNear, float iFar, float iSensitivity, float iSpeed, const glm::vec3& iPosition);

	/// <summary>
	/// Manage keyboard input for movements
	/// </summary>
	/// <param name="window">Window to manage input</param>
	/// <param name="deltaTime">Manage speed of the camera</param>
	void ProcessMovement(GLFWwindow* window, float deltaTime);

	/// <summary>
	/// Process the movements of the camera
	/// </summary>
	/// <param name="x">X position of the mouse</param>
	/// <param name="y">Y position of the mouse</param>
	void ProcessMouseInput(double x, double y);
};