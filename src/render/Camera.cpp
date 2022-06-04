#include "Camera.h"

Camera* sub_camera;
void mouse_callback(GLFWwindow* window, double x, double y);

Camera::Camera(GLFWwindow* window, float iWidth, float iHeight, float iFov, float iNear, float iFar, float iSensitivity, float iSpeed, glm::vec3 iPosition)
{	
	_width = iWidth;
	_height = iHeight;
	_fov = iFov;
	_near = iNear;
	_far = iFar;
	_sensitivity = iSensitivity;
	_speed = iSpeed;
	_position = iPosition;

	sub_camera = this;
	_canRotate = false;
	_mousePositionX = 0;
	_mousePositionY = 0;
		
	_offsetX = 0;
	_offsetY = 0;
	_pitch = 0;
	_yaw = 270;
	_lastX = iWidth / 2;
	_lastY = iHeight / 2;

	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glfwSetCursorPosCallback(window, mouse_callback);
	view = glm::lookAt(_position, _position - _front, _up);
	projection = glm::perspective(glm::radians(iFov), iWidth / iHeight, iNear, iFar);

	viewLocation = 0;
	projectionLocation = 0;
}

void Camera::ProcessMovement(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W))
		_position -= _front * _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A))
		_position += glm::normalize(glm::cross(_front, _up)) * _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_S))
		_position += _front * _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_D))
		_position -= glm::normalize(glm::cross(_front, _up)) * _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		_position.y += _speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		_position.y -= _speed * deltaTime;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		_canRotate = true;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwGetCursorPos(window, &_mousePositionX, &_mousePositionY);
		_lastX = _mousePositionX;
		_lastY = _mousePositionY;
		_canRotate = false;
	}

	view = glm::lookAt(_position, _position - _front, _up);
}

void Camera::ProcessMouseInput(double x, double y) 
{
	if (_canRotate)
	{
		_offsetX = x - _lastX;
		_offsetY = y - _lastY;

		_lastX = x;
		_lastY = y;

		_offsetX *= _sensitivity;
		_offsetY *= _sensitivity;

		_yaw += _offsetX;
		_pitch += _offsetY;

		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front.y = sin(glm::radians(_pitch));
		_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(_front);
	}
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
	sub_camera->ProcessMouseInput(x, y);
}