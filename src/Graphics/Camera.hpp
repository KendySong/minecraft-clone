#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once
class Camera
{
public:
	glm::vec3 position;

	float sensitivity;
	float speed;
	float fov;

	glm::mat4 view;
	int viewLocation;

	glm::mat4 projection;
	int projectionLocation;

	Camera(GLFWwindow* window, float width, float height, float fov, float near, float far, float sensitivity, float speed, const glm::vec3& position);
	void processMovement(GLFWwindow* window, float deltaTime);
	void processMouseInput(double x, double y);
	void reconstruct(std::uint32_t shaderID);

private :	
	float m_width;
	float m_height;
	float m_near;
	float m_far;

	float m_yaw;
	float m_pitch;

	float m_lastX;
	float m_lastY;

	float m_offsetX;
	float m_offsetY;

	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_direction;
		
	bool m_canRotate;
	double m_mousePositionX;
	double m_mousePositionY;
};