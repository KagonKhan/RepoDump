#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




enum class Camera_Movement {
	FORWARD = 0, BACKWARD, LEFT, RIGHT
} ;

const GLfloat g_Yaw			= -90.f;
const GLfloat g_Pitch		=  0.f;
const GLfloat g_Speed		=  3.f;
const GLfloat g_Sensitivity =  0.15f;
const GLfloat g_Zoom		=  45.f;

class Camera {
public:
	glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp; // Attributes
	GLfloat m_Yaw, m_Pitch;								 	 // Euler angles
	GLfloat m_MovementSpeed, m_MouseSensitivity, m_Zoom;     // Options

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.f, 0.f), GLfloat yaw = g_Yaw, GLfloat m_Pitch = g_Pitch) 
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(g_Speed), m_MouseSensitivity(g_Sensitivity), m_Zoom(g_Zoom) {

		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = g_Pitch;
		UpdateCameraVectors();

	}

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(g_Speed), m_MouseSensitivity(g_Sensitivity), m_Zoom(g_Zoom){

		m_Position = glm::vec3(posX, posY, posZ);
		m_WorldUp = glm::vec3(upX, upY, upZ);
		m_Yaw = yaw;
		m_Pitch = pitch;
		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
		GLfloat camSpeed = 5 * deltaTime;

		if (direction == Camera_Movement::FORWARD)
			m_Position += m_Front * camSpeed;
		if (direction == Camera_Movement::BACKWARD)
			m_Position -= m_Front * camSpeed;
		if (direction == Camera_Movement::LEFT)
			m_Position -= m_Right * camSpeed;
		if (direction == Camera_Movement::RIGHT)
			m_Position += m_Right * camSpeed;

	}

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (constrainPitch) {
			if (m_Pitch > 89.f)
				m_Pitch = 89.f;
			if (m_Pitch < -89.f)
				m_Pitch = -89.f;
		}

		UpdateCameraVectors();
	}

	void ProcessMouseScroll(GLfloat yoffset) {
		if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
			m_Zoom -= yoffset;
		if (m_Zoom <= 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom >= 45.0f)
			m_Zoom = 45.0f;

	}

private:
	void UpdateCameraVectors() {
		glm::vec3 front;

		front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
		front.y = sin(glm::radians(m_Pitch));
		front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
	}
};
