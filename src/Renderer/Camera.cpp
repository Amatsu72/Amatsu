#include "../pch.h"
#include "Camera.h"

namespace Engine{

	Camera::Camera() :m_projection_matrix(1.0f)
	{
		update_camera_vectors();
		recaculate();
	}

	void Camera::set_position(const glm::vec3& position)
	{
		m_position = position;
		recaculate();
		//std::cout << "camera position:";
		//std::cout << m_position.x <<"\t"<< m_position.y << "\t" << m_position.z << "\t" << std::endl;
	}

	void Camera::set_projection(const glm::mat4& projection_matrix)
	{
		m_projection_matrix = projection_matrix;
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	}

	void Camera::set_yaw(float yaw)
	{
		m_yaw = yaw;
		update_camera_vectors();
		recaculate();
	}

	void Camera::set_pitch(float pitch)
	{
		m_pitch = pitch;
		update_camera_vectors();
		recaculate();
	}

	void Camera::recaculate()
	{
		m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
		m_view_projection_matrix = m_projection_matrix * m_view_matrix;
	}

	void Camera::update_camera_vectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);
		m_right = glm::normalize(glm::cross(m_front, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

}
