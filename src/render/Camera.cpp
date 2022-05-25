#include "Camera.h"

Camera* sub_camera;
void mouse_callback(GLFWwindow* window, double x, double y);

Camera::Camera(GLFWwindow* window, float iWidth, float iHeight, float iFov, float iNear, float iFar, float iSensitivity, float iSpeed, glm::vec3 iPosition)
{	
	width = iWidth;
	height = iHeight;
	fov = iFov;
	near = iNear;
	far = iFar;
	sensitivity = iSensitivity;
	speed = iSpeed;
	position = iPosition;

	sub_camera = this;
	canRotate = false;
	mousePositionX = 0;
	mousePositionY = 0;
		
	offsetX = 0;
	offsetY = 0;	
	pitch = 0;
	yaw = 270;
	lastX = iWidth / 2;
	lastY = iHeight / 2;

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glfwSetCursorPosCallback(window, mouse_callback);
	view = glm::lookAt(position, position - front, up);
	projection = glm::perspective(glm::radians(iFov), iWidth / iHeight, iNear, iFar);

	viewLocation = 0;
	projectionLocation = 0;
}

void Camera::ProcessMovement(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W))
		position -= front * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A))
		position += glm::normalize(glm::cross(front, up)) * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_S))
		position += front * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_D))
		position -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		position.y += speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		position.y -= speed * deltaTime;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		canRotate = true;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
		lastX = mousePositionX;
		lastY = mousePositionY;
		canRotate = false;
	}

	view = glm::lookAt(position, position - front, up);
	projection = glm::perspective(glm::radians(fov), width / height, near, far);
}

void Camera::ProcessMouseInput(double x, double y) 
{
	if (canRotate)
	{
		offsetX = x - lastX;
		offsetY = y - lastY;

		lastX = x;
		lastY = y;

		offsetX *= sensitivity;
		offsetY *= sensitivity;

		yaw += offsetX;
		pitch += offsetY;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
	}
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
	sub_camera->ProcessMouseInput(x, y);
}
