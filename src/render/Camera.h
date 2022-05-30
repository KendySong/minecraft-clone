#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once
class Camera
{
public :
	float width;
	float height;
	float near;
	float far;

	float yaw;
	float pitch;

	float lastX;
	float lastY;

	float offsetX;
	float offsetY;

	float fov;
	float speed;
	float sensitivity;

	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 position;
	glm::vec3 direction;
	
	glm::mat4 view;
	glm::mat4 projection;

	int viewLocation;
	int projectionLocation;
	bool canRotate;

	double mousePositionX;
	double mousePositionY;

	Camera(GLFWwindow* window, float iWidth, float iHeight, float iFov, float iNear, float iFar, float iSensitivity, float iSpeed, glm::vec3 iPosition);
	void ProcessMovement(GLFWwindow* window, float deltaTime);
	void ProcessMouseInput(double x, double y);
};