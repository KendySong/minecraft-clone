#include "Camera.hpp"

Camera* sub_camera;
void mouse_callback(GLFWwindow* window, double x, double y);

Camera::Camera(GLFWwindow* window, float width, float height, float fov, float near, float far, float sensitivity, float speed, const glm::vec3& position)
{	
	m_width = width;
	m_height = height;
	this->fov = fov;
	m_near = near;
	m_far = far;
	this->sensitivity = sensitivity;
	this->speed = speed;
	this->position = position;

	sub_camera = this;
	m_canRotate = false;
	m_mousePositionX = 0;
	m_mousePositionY = 0;
		
	m_offsetX = 0;
	m_offsetY = 0;
	m_pitch = 0;
	m_yaw = 270;
	m_lastX = width / 2;
	m_lastY = height / 2;

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glfwSetCursorPosCallback(window, mouse_callback);
	view = glm::lookAt(position, position - m_front, m_up);
	projection = glm::perspective(glm::radians(fov), width / height, near, far);

	viewLocation = 0;
	projectionLocation = 0;
}

void Camera::processMovement(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W))
		position -= m_front * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A))
		position += glm::normalize(glm::cross(m_front, m_up)) * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_S))
		position += m_front * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_D))
		position -= glm::normalize(glm::cross(m_front, m_up)) * speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_SPACE))
		position.y += speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		position.y -= speed * deltaTime;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_canRotate = true;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwGetCursorPos(window, &m_mousePositionX, &m_mousePositionY);
		m_lastX = m_mousePositionX;
		m_lastY = m_mousePositionY;
		m_canRotate = false;
	}

	view = glm::lookAt(position, position - m_front, m_up);
}

void Camera::processMouseInput(double x, double y) 
{
	if (m_canRotate)
	{
		m_offsetX = x - m_lastX;
		m_offsetY = y - m_lastY;

		m_lastX = x;
		m_lastY = y;

		m_offsetX *= sensitivity;
		m_offsetY *= sensitivity;

		m_yaw += m_offsetX;
		m_pitch += m_offsetY;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(m_front);
	}
}

void Camera::reconstruct(std::uint32_t shaderID)
{
	projection = glm::perspective(glm::radians(fov), m_width / m_height, m_near, m_far);
	this->projectionLocation = glGetUniformLocation(shaderID, "projection");
	glUniformMatrix4fv(this->projectionLocation, 1, false, glm::value_ptr(this->projection));
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
	sub_camera->processMouseInput(x, y);
}