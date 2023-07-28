#include "../pch.h"
#include "CameraController.h"
#include "../Core/Input.h"
#include "../Core/Macro.h"

namespace Engine {

	CameraController::CameraController(float aspect_ratio, float z_near, float z_far)
		:m_aspect_ratio(aspect_ratio), m_z_near(z_near), m_z_far(z_far), m_camera()
	{
		glm::mat4 projection = get_projection();
		m_camera.set_projection(projection);
	}

	void CameraController::update(Timestep ts)
	{
		float velocity = m_movement_speed * ts;
		
		if (Input::is_key_pressed(KEY_A))
			m_camera_position -= m_camera.get_right() * velocity;
		else if (Input::is_key_pressed(KEY_D))
			m_camera_position += m_camera.get_right() * velocity;

		if (Input::is_key_pressed(KEY_W))
			m_camera_position += m_camera.get_front() * velocity;
		else if (Input::is_key_pressed(KEY_S))
			m_camera_position -= m_camera.get_front() * velocity;

		if(Input::is_key_pressed(KEY_UP))
			m_camera_position += m_camera.get_world_up() * velocity;
		else if(Input::is_key_pressed(KEY_DOWN))
			m_camera_position -= m_camera.get_world_up() * velocity;

		m_camera.set_position(m_camera_position);
	}

	void CameraController::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::on_mouse_scrolled));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::on_window_resized));
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(CameraController::on_mouse_button_pressed));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(CameraController::on_mouse_button_released));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(CameraController::on_mouse_moved));
	}

	void CameraController::set_camera_postion(glm::vec3& postion)
	{
		m_camera_position = postion;
		m_camera.set_position(m_camera_position);
	}

	glm::mat4 CameraController::get_projection()
	{
		return glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_z_near, m_z_far);
	}

	bool CameraController::on_mouse_scrolled(MouseScrolledEvent& e)
	{
		if (MOUSE_BUTTON_STATE)
		{
			m_fov -= e.get_Yoffset() * m_zoom_speed;
			m_fov = std::max(m_fov, 1.0f);
			m_fov = std::min(m_fov, 45.0f);
			glm::mat4 projection = get_projection();
			m_camera.set_projection(projection);		
		}
		return false;
	}

	bool CameraController::on_window_resized(WindowResizeEvent& e)
	{	
		m_aspect_ratio = (float)e.get_width() / (float)e.get_height();
		glm::mat4 projection = get_projection();
		m_camera.set_projection(projection);
		return false;
	}

	bool CameraController::on_mouse_button_pressed(MouseButtonPressedEvent& e)
	{
		if (MOUSE_BUTTON_STATE == false)
			MOUSE_BUTTON_STATE = true;
		return true;//?
	}

	bool CameraController::on_mouse_button_released(MouseButtonReleasedEvent& e)
	{
		if (MOUSE_BUTTON_STATE == true)
			MOUSE_BUTTON_STATE = false;
		return true;
	}

	bool CameraController::on_mouse_moved(MouseMovedEvent& e)
	{
		if (MOUSE_BUTTON_STATE)
		{
			float x = e.get_X();
			float y = e.get_Y();
			if (first_mouse)
			{
				m_mouse_lastX = x;
				m_mouse_lastY = y;
				first_mouse = false;
			}
			float Xoffset = (x - m_mouse_lastX) * m_mouse_speed;
			float Yoffset = (m_mouse_lastY - y) * m_mouse_speed;
			m_mouse_lastX = x;
			m_mouse_lastY = y;

			float yaw = m_camera.get_yaw() + Xoffset;
			float pitch = m_camera.get_pitch() + Yoffset;
			pitch = std::min(pitch, 89.0f);
			pitch = std::max(pitch, -89.0f);
			m_camera.set_yaw(yaw);
			m_camera.set_pitch(pitch);			
		}
		else
			first_mouse = true;
		
		return false;
	}

}